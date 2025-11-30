#include "saunavm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const char* opcode_names[] = {
    "NOP", "SET", "MOV", "LOAD", "STORE", "LOADV",
    "ADD", "SUB", "CMP", "CMPI",
    "JMP", "JEQ", "JNE", "JLT", "JLE", "JGT", "JGE",
    "HEAT", "POW", "PRINT", "PRINTS", "PUSH", "POP", "HALT"
};

const char* svm_opcode_name(SVM_Opcode op) {
    if (op >= 0 && op <= OP_HALT) {
        return opcode_names[op];
    }
    return "???";
}

/* inicializa a VM */
void svm_init(SaunaVM* vm) {
    memset(vm, 0, sizeof(SaunaVM));
    vm->sensor_temp = 25;    /* temperatura ambiente inicial */
    vm->sensor_peso = 100;   /* 100g padrão */
    vm->potencia = 0;
    vm->sp = 0;
    vm->pc = 0;
    vm->halted = false;
    vm->steps = 0;
    vm->ticks = 0;
}

/* reset da VM (mantém programa) */
void svm_reset(SaunaVM* vm) {
    vm->regs[0] = 0;
    vm->regs[1] = 0;
    vm->sensor_temp = 25;
    vm->potencia = 0;
    vm->sp = 0;
    vm->pc = 0;
    vm->halted = false;
    vm->steps = 0;
    vm->ticks = 0;
    vm->flag_eq = false;
    vm->flag_lt = false;
    vm->flag_gt = false;
    
    /* zera variáveis */
    for (int i = 0; i < vm->var_count; i++) {
        vm->vars[i].value = 0;
    }
}

/* configura peso */
void svm_set_peso(SaunaVM* vm, int peso_gramas) {
    vm->sensor_peso = peso_gramas > 0 ? peso_gramas : 1;
}

/* configura temperatura inicial */
void svm_set_temp_inicial(SaunaVM* vm, int temp) {
    vm->sensor_temp = temp;
}

/* adiciona instrução ao programa */
int svm_add_instruction(SaunaVM* vm, SVM_Opcode op, int arg1, int arg2, int arg3) {
    if (vm->program_size >= SVM_MAX_PROGRAM) {
        fprintf(stderr, "[SaunaVM] Erro: programa muito grande\n");
        return -1;
    }
    
    SVM_Instruction* instr = &vm->program[vm->program_size];
    instr->op = op;
    instr->arg1 = arg1;
    instr->arg2 = arg2;
    instr->arg3 = arg3;
    
    return vm->program_size++;
}

/* adiciona label */
int svm_add_label(SaunaVM* vm, const char* name) {
    if (vm->label_count >= SVM_MAX_LABELS) {
        fprintf(stderr, "[SaunaVM] Erro: muitos labels\n");
        return -1;
    }
    
    /* verifica se já existe */
    for (int i = 0; i < vm->label_count; i++) {
        if (strcmp(vm->labels[i].name, name) == 0) {
            /* atualiza endereço */
            vm->labels[i].address = vm->program_size;
            return i;
        }
    }
    
    /* cria novo */
    SVM_Label* lbl = &vm->labels[vm->label_count];
    strncpy(lbl->name, name, 63);
    lbl->name[63] = '\0';
    lbl->address = vm->program_size;
    
    return vm->label_count++;
}

/* obtém endereço de um label */
int svm_get_label_addr(SaunaVM* vm, const char* name) {
    for (int i = 0; i < vm->label_count; i++) {
        if (strcmp(vm->labels[i].name, name) == 0) {
            return vm->labels[i].address;
        }
    }
    return -1; /* label não encontrado */
}

/* adiciona string ao pool */
int svm_add_string(SaunaVM* vm, const char* str) {
    if (vm->string_count >= SVM_MAX_STRINGS) {
        fprintf(stderr, "[SaunaVM] Erro: muitas strings\n");
        return -1;
    }
    
    /* remove aspas se presentes */
    const char* src = str;
    if (str[0] == '"') src++;
    
    char* dst = vm->strings[vm->string_count];
    int len = 0;
    while (*src && *src != '"' && len < SVM_MAX_STR_LEN - 1) {
        if (*src == '\\' && *(src+1)) {
            src++;
            switch (*src) {
                case 'n': *dst++ = '\n'; break;
                case 't': *dst++ = '\t'; break;
                case '\\': *dst++ = '\\'; break;
                case '"': *dst++ = '"'; break;
                default: *dst++ = *src; break;
            }
        } else {
            *dst++ = *src;
        }
        src++;
        len++;
    }
    *dst = '\0';
    
    return vm->string_count++;
}

/* adiciona variável */
int svm_add_variable(SaunaVM* vm, const char* name) {
    /* verifica se já existe */
    for (int i = 0; i < vm->var_count; i++) {
        if (strcmp(vm->vars[i].name, name) == 0) {
            return i;
        }
    }
    
    if (vm->var_count >= SVM_MAX_VARS) {
        fprintf(stderr, "[SaunaVM] Erro: muitas variáveis\n");
        return -1;
    }
    
    SVM_Variable* var = &vm->vars[vm->var_count];
    strncpy(var->name, name, 63);
    var->name[63] = '\0';
    var->value = 0;
    
    return vm->var_count++;
}

/* obtém índice de variável */
int svm_get_variable_idx(SaunaVM* vm, const char* name) {
    for (int i = 0; i < vm->var_count; i++) {
        if (strcmp(vm->vars[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/* modelo térmico: atualiza temperatura baseado na potência */
static void update_thermal_model(SaunaVM* vm) {
    /* 
     * modelo simplificado:
     * - aquecimento proporcional à potência
     * - resfriamento natural proporcional à temperatura
     * - peso afeta a taxa de aquecimento
     */
    double heating = vm->potencia * 0.15;
    double cooling = (vm->sensor_temp - 25) * 0.05;  /* 25°C = ambiente */
    double weight_factor = sqrt((double)vm->sensor_peso / 100.0);
    
    if (weight_factor < 0.5) weight_factor = 0.5;
    
    double delta = (heating - cooling) / weight_factor;
    vm->sensor_temp += (int)delta;
    
    /* limites físicos */
    if (vm->sensor_temp < 25) vm->sensor_temp = 25;   /* não abaixo do ambiente */
    if (vm->sensor_temp > 150) vm->sensor_temp = 150; /* limite da sauna */
}

/* executa uma instrução */
void svm_step(SaunaVM* vm) {
    if (vm->halted) return;
    if (vm->pc < 0 || vm->pc >= vm->program_size) {
        vm->halted = true;
        return;
    }
    
    SVM_Instruction* instr = &vm->program[vm->pc];
    vm->steps++;
    vm->ticks++;
    
    /* atualiza modelo térmico a cada tick */
    update_thermal_model(vm);
    
    switch (instr->op) {
        case OP_NOP:
            vm->pc++;
            break;
            
        case OP_SET:
            vm->regs[instr->arg1] = instr->arg2;
            vm->pc++;
            break;
            
        case OP_MOV:
            vm->regs[instr->arg1] = vm->regs[instr->arg2];
            vm->pc++;
            break;
            
        case OP_LOAD:
            if (instr->arg2 == SENSOR_TEMP) {
                vm->regs[instr->arg1] = vm->sensor_temp;
            } else if (instr->arg2 == SENSOR_PESO) {
                vm->regs[instr->arg1] = vm->sensor_peso;
            }
            vm->pc++;
            break;
            
        case OP_STORE:
            if (instr->arg1 >= 0 && instr->arg1 < vm->var_count) {
                vm->vars[instr->arg1].value = vm->regs[instr->arg2];
            }
            vm->pc++;
            break;
            
        case OP_LOADV:
            if (instr->arg2 >= 0 && instr->arg2 < vm->var_count) {
                vm->regs[instr->arg1] = vm->vars[instr->arg2].value;
            }
            vm->pc++;
            break;
            
        case OP_ADD:
            vm->regs[instr->arg1] += vm->regs[instr->arg2];
            vm->pc++;
            break;
            
        case OP_SUB:
            vm->regs[instr->arg1] -= vm->regs[instr->arg2];
            vm->pc++;
            break;
            
        case OP_CMP: {
            int a = vm->regs[instr->arg1];
            int b = vm->regs[instr->arg2];
            vm->flag_eq = (a == b);
            vm->flag_lt = (a < b);
            vm->flag_gt = (a > b);
            vm->pc++;
            break;
        }
        
        case OP_CMPI: {
            int a = vm->regs[instr->arg1];
            int b = instr->arg2;
            vm->flag_eq = (a == b);
            vm->flag_lt = (a < b);
            vm->flag_gt = (a > b);
            vm->pc++;
            break;
        }
        
        case OP_JMP:
            vm->pc = instr->arg1;
            break;
            
        case OP_JEQ:
            if (vm->flag_eq) vm->pc = instr->arg1;
            else vm->pc++;
            break;
            
        case OP_JNE:
            if (!vm->flag_eq) vm->pc = instr->arg1;
            else vm->pc++;
            break;
            
        case OP_JLT:
            if (vm->flag_lt) vm->pc = instr->arg1;
            else vm->pc++;
            break;
            
        case OP_JLE:
            if (vm->flag_lt || vm->flag_eq) vm->pc = instr->arg1;
            else vm->pc++;
            break;
            
        case OP_JGT:
            if (vm->flag_gt) vm->pc = instr->arg1;
            else vm->pc++;
            break;
            
        case OP_JGE:
            if (vm->flag_gt || vm->flag_eq) vm->pc = instr->arg1;
            else vm->pc++;
            break;
            
        case OP_HEAT: {
            /* simula aquecimento por n segundos */
            int segundos = instr->arg1;
            printf("[SAUNA] Aquecendo por %d segundos (potência: %d%%)\n", 
                   segundos, vm->potencia);
            
            /* simula passagem do tempo */
            for (int i = 0; i < segundos; i++) {
                vm->ticks++;
                update_thermal_model(vm);
            }
            printf("[SAUNA] Temperatura atual: %d°C\n", vm->sensor_temp);
            vm->pc++;
            break;
        }
        
        case OP_POW:
            vm->potencia = instr->arg1;
            if (vm->potencia < 0) vm->potencia = 0;
            if (vm->potencia > 100) vm->potencia = 100;
            printf("[SAUNA] Potência ajustada para %d%%\n", vm->potencia);
            vm->pc++;
            break;
            
        case OP_PRINT:
            printf("%d\n", vm->regs[instr->arg1]);
            vm->pc++;
            break;
            
        case OP_PRINTS:
            if (instr->arg1 >= 0 && instr->arg1 < vm->string_count) {
                printf("%s\n", vm->strings[instr->arg1]);
            }
            vm->pc++;
            break;
            
        case OP_PUSH:
            if (vm->sp >= SVM_MAX_STACK) {
                fprintf(stderr, "[SaunaVM] Erro: stack overflow\n");
                vm->halted = true;
            } else {
                vm->stack[vm->sp++] = vm->regs[instr->arg1];
            }
            vm->pc++;
            break;
            
        case OP_POP:
            if (vm->sp <= 0) {
                fprintf(stderr, "[SaunaVM] Erro: stack underflow\n");
                vm->halted = true;
            } else {
                vm->regs[instr->arg1] = vm->stack[--vm->sp];
            }
            vm->pc++;
            break;
            
        case OP_HALT:
            printf("[SAUNA] Sessão encerrada. Temperatura final: %d°C\n", vm->sensor_temp);
            vm->halted = true;
            break;
            
        default:
            fprintf(stderr, "[SaunaVM] Opcode desconhecido: %d\n", instr->op);
            vm->halted = true;
            break;
    }
}

/* executa o programa */
void svm_run(SaunaVM* vm, int max_steps) {
    while (!vm->halted) {
        if (max_steps > 0 && vm->steps >= max_steps) {
            fprintf(stderr, "[SaunaVM] Limite de passos atingido (%d)\n", max_steps);
            break;
        }
        svm_step(vm);
    }
}

/* imprime estado atual */
void svm_print_state(SaunaVM* vm) {
    printf("=== Estado da SaunaVM ===\n");
    printf("PC: %d, Passos: %d, Halted: %s\n", 
           vm->pc, vm->steps, vm->halted ? "sim" : "não");
    printf("R0: %d, R1: %d\n", vm->regs[0], vm->regs[1]);
    printf("TEMP: %d°C, PESO: %dg, POTÊNCIA: %d%%\n", 
           vm->sensor_temp, vm->sensor_peso, vm->potencia);
    printf("Flags: EQ=%d LT=%d GT=%d\n", 
           vm->flag_eq, vm->flag_lt, vm->flag_gt);
    printf("Stack (sp=%d):", vm->sp);
    for (int i = 0; i < vm->sp && i < 10; i++) {
        printf(" %d", vm->stack[i]);
    }
    printf("\n");
    
    if (vm->var_count > 0) {
        printf("Variáveis:\n");
        for (int i = 0; i < vm->var_count; i++) {
            printf("  %s = %d\n", vm->vars[i].name, vm->vars[i].value);
        }
    }
    printf("=========================\n");
}

/* desassembla o programa */
void svm_disassemble(SaunaVM* vm) {
    printf("=== Disassembly ===\n");
    
    for (int i = 0; i < vm->program_size; i++) {
        /* verifica se há label aqui */
        for (int j = 0; j < vm->label_count; j++) {
            if (vm->labels[j].address == i) {
                printf("%s:\n", vm->labels[j].name);
            }
        }
        
        SVM_Instruction* instr = &vm->program[i];
        printf("  %04d: %-8s", i, svm_opcode_name(instr->op));
        
        switch (instr->op) {
            case OP_SET:
                printf("R%d, %d", instr->arg1, instr->arg2);
                break;
            case OP_MOV:
            case OP_ADD:
            case OP_SUB:
            case OP_CMP:
                printf("R%d, R%d", instr->arg1, instr->arg2);
                break;
            case OP_CMPI:
                printf("R%d, %d", instr->arg1, instr->arg2);
                break;
            case OP_LOAD:
                printf("R%d, %s", instr->arg1, 
                       instr->arg2 == SENSOR_TEMP ? "TEMP" : "PESO");
                break;
            case OP_STORE:
                if (instr->arg1 >= 0 && instr->arg1 < vm->var_count) {
                    printf("%s, R%d", vm->vars[instr->arg1].name, instr->arg2);
                } else {
                    printf("var[%d], R%d", instr->arg1, instr->arg2);
                }
                break;
            case OP_LOADV:
                if (instr->arg2 >= 0 && instr->arg2 < vm->var_count) {
                    printf("R%d, %s", instr->arg1, vm->vars[instr->arg2].name);
                } else {
                    printf("R%d, var[%d]", instr->arg1, instr->arg2);
                }
                break;
            case OP_JMP:
            case OP_JEQ:
            case OP_JNE:
            case OP_JLT:
            case OP_JLE:
            case OP_JGT:
            case OP_JGE:
                /* tenta encontrar nome do label */
                {
                    const char* lbl_name = NULL;
                    for (int j = 0; j < vm->label_count; j++) {
                        if (vm->labels[j].address == instr->arg1) {
                            lbl_name = vm->labels[j].name;
                            break;
                        }
                    }
                    if (lbl_name) printf("%s", lbl_name);
                    else printf("%d", instr->arg1);
                }
                break;
            case OP_HEAT:
            case OP_POW:
                printf("%d", instr->arg1);
                break;
            case OP_PRINT:
            case OP_PUSH:
            case OP_POP:
                printf("R%d", instr->arg1);
                break;
            case OP_PRINTS:
                if (instr->arg1 >= 0 && instr->arg1 < vm->string_count) {
                    printf("\"%s\"", vm->strings[instr->arg1]);
                } else {
                    printf("str[%d]", instr->arg1);
                }
                break;
            default:
                break;
        }
        printf("\n");
    }
    printf("===================\n");
}

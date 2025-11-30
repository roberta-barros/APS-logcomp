/*
 * SaunaVM - Máquina Virtual para Controle de Sauna
 * 
 * Uma VM minimalista e Turing-completa com:
 * - 2 registradores de propósito geral (R0, R1)
 * - 2 sensores readonly (TEMP, PESO)
 * - Stack para variáveis e operações
 * - Modelo térmico simulado
 * 
 * Instruções:
 *   SET Rx n       - Rx := n
 *   MOV Rx Ry      - Rx := Ry  
 *   LOAD Rx S      - Rx := sensor S (TEMP ou PESO)
 *   STORE var Rx   - variavel[var] := Rx
 *   LOADV Rx var   - Rx := variavel[var]
 *   ADD Rx Ry      - Rx := Rx + Ry
 *   SUB Rx Ry      - Rx := Rx - Ry
 *   CMP Rx Ry      - compara Rx com Ry, seta flags
 *   CMPI Rx n      - compara Rx com imediato n
 *   JMP label      - PC := label
 *   JEQ label      - jump if equal
 *   JNE label      - jump if not equal
 *   JLT label      - jump if less than
 *   JLE label      - jump if less or equal
 *   JGT label      - jump if greater than
 *   JGE label      - jump if greater or equal
 *   HEAT n         - simula aquecimento por n segundos
 *   POW n          - define potência (0-100)
 *   PRINT Rx       - imprime valor de Rx
 *   PRINTS idx     - imprime string do pool de strings
 *   PUSH Rx        - empilha Rx
 *   POP Rx         - desempilha em Rx
 *   HALT           - para execução
 *   NOP            - no operation
 */

#ifndef SAUNAVM_H
#define SAUNAVM_H

#include <stdint.h>
#include <stdbool.h>

/* limites da VM */
#define SVM_MAX_PROGRAM    1024    /* máximo de instruções */
#define SVM_MAX_LABELS     256     /* máximo de labels */
#define SVM_MAX_VARS       64      /* máximo de variáveis */
#define SVM_MAX_STACK      256     /* tamanho da pilha */
#define SVM_MAX_STRINGS    64      /* pool de strings */
#define SVM_MAX_STR_LEN    256     /* tamanho máximo de string */

/* opcodes da SaunaVM */
typedef enum {
    OP_NOP = 0,
    OP_SET,       /* SET Rx n */
    OP_MOV,       /* MOV Rx Ry */
    OP_LOAD,      /* LOAD Rx sensor */
    OP_STORE,     /* STORE var_idx Rx */
    OP_LOADV,     /* LOADV Rx var_idx */
    OP_ADD,       /* ADD Rx Ry */
    OP_SUB,       /* SUB Rx Ry */
    OP_CMP,       /* CMP Rx Ry */
    OP_CMPI,      /* CMPI Rx n */
    OP_JMP,       /* JMP addr */
    OP_JEQ,       /* JEQ addr */
    OP_JNE,       /* JNE addr */
    OP_JLT,       /* JLT addr */
    OP_JLE,       /* JLE addr */
    OP_JGT,       /* JGT addr */
    OP_JGE,       /* JGE addr */
    OP_HEAT,      /* HEAT n (segundos) */
    OP_POW,       /* POW n (potência 0-100) */
    OP_PRINT,     /* PRINT Rx */
    OP_PRINTS,    /* PRINTS str_idx */
    OP_PUSH,      /* PUSH Rx */
    OP_POP,       /* POP Rx */
    OP_HALT       /* HALT */
} SVM_Opcode;

/* registradores */
typedef enum {
    REG_R0 = 0,
    REG_R1 = 1
} SVM_Register;

/* sensores */
typedef enum {
    SENSOR_TEMP = 0,
    SENSOR_PESO = 1
} SVM_Sensor;

/* instrução da VM */
typedef struct {
    SVM_Opcode op;
    int arg1;      /* primeiro argumento (registrador, valor, índice) */
    int arg2;      /* segundo argumento */
    int arg3;      /* terceiro argumento (para alguns ops) */
} SVM_Instruction;

/* label para saltos */
typedef struct {
    char name[64];
    int address;
} SVM_Label;

/* variável */
typedef struct {
    char name[64];
    int value;
} SVM_Variable;

/* estado da VM */
typedef struct {
    /* registradores de propósito geral */
    int regs[2];           /* R0, R1 */
    
    /* sensores (readonly) */
    int sensor_temp;       /* temperatura atual (°C) */
    int sensor_peso;       /* peso do item (gramas) */
    
    /* flags de comparação */
    bool flag_eq;          /* equal */
    bool flag_lt;          /* less than */
    bool flag_gt;          /* greater than */
    
    /* potência atual */
    int potencia;          /* 0-100 */
    
    /* programa */
    SVM_Instruction program[SVM_MAX_PROGRAM];
    int program_size;
    
    /* labels */
    SVM_Label labels[SVM_MAX_LABELS];
    int label_count;
    
    /* variáveis */
    SVM_Variable vars[SVM_MAX_VARS];
    int var_count;
    
    /* pool de strings */
    char strings[SVM_MAX_STRINGS][SVM_MAX_STR_LEN];
    int string_count;
    
    /* pilha */
    int stack[SVM_MAX_STACK];
    int sp;                /* stack pointer */
    
    /* controle de execução */
    int pc;                /* program counter */
    bool halted;
    int steps;
    
    /* modelo térmico */
    int ticks;
    
} SaunaVM;

/* funções da API */

/* inicialização */
void svm_init(SaunaVM* vm);
void svm_reset(SaunaVM* vm);

/* configuração de sensores */
void svm_set_peso(SaunaVM* vm, int peso_gramas);
void svm_set_temp_inicial(SaunaVM* vm, int temp);

/* geração de código */
int svm_add_instruction(SaunaVM* vm, SVM_Opcode op, int arg1, int arg2, int arg3);
int svm_add_label(SaunaVM* vm, const char* name);
int svm_get_label_addr(SaunaVM* vm, const char* name);
int svm_add_string(SaunaVM* vm, const char* str);
int svm_add_variable(SaunaVM* vm, const char* name);
int svm_get_variable_idx(SaunaVM* vm, const char* name);

/* resolução de labels (segunda passagem) */
void svm_resolve_labels(SaunaVM* vm);

/* execução */
void svm_step(SaunaVM* vm);
void svm_run(SaunaVM* vm, int max_steps);

/* debug */
void svm_print_state(SaunaVM* vm);
void svm_disassemble(SaunaVM* vm);

/* utilitário: nome do opcode */
const char* svm_opcode_name(SVM_Opcode op);

#endif /* SAUNAVM_H */

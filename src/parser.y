%define parse.error verbose
%code top {
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "saunavm.h"
  
  extern int yylex(void);
  void yyerror(const char *s);
  extern int yylineno;
  extern FILE *yyin;
  
  /* VM global */
  SaunaVM vm;
  
  /* Contadores para labels únicos */
  static int label_counter = 0;
  
  /* Gera nome de label único */
  static char* new_label(const char* prefix) {
    static char buf[64];
    snprintf(buf, sizeof(buf), "%s_%d", prefix, label_counter++);
    return buf;
  }
  
  /* Pilha de contexto para loops e ifs */
  #define MAX_CONTEXT 64
  static char loop_start[MAX_CONTEXT][64];
  static char loop_end[MAX_CONTEXT][64];
  static char if_else[MAX_CONTEXT][64];
  static char if_end[MAX_CONTEXT][64];
  static int loop_depth = 0;
  static int if_depth = 0;
}

/* Valores semânticos */
%union {
  int   ival;
  char* sval;
  int   cmp_op;  /* Operador de comparação */
}

/* Tokens com valor */
%token <ival> T_NUM
%token <ival> T_TIME
%token <sval> T_STR
%token <sval> T_IDENT

/* Palavras-chave / operadores */
%token T_SE T_SENAO T_ENQUANTO T_SEMPRE
%token T_SET T_AQUECER T_POTENCIA T_IMPRIMIR
%token T_TEMP T_PESO
%token T_E T_OU
%token T_EQ T_NE T_LT T_LE T_GT T_GE
%token T_ERROR

/* Precedência lógica (ou mais baixo) */
%left T_OU
%left T_E

/* Tipos auxiliares */
%type  <ival> numero tempo expr
%type  <ival> sensor
%type  <cmp_op> comparador

%start programa

%%

programa
  : %empty
  | programa declaracao
  ;

declaracao
  : acao ';'
  | atribuicao ';'
  | if_stmt
  | while_stmt
  ;

acao
  : T_AQUECER tempo
    {
      /* Gera instrução HEAT */
      svm_add_instruction(&vm, OP_HEAT, $2, 0, 0);
    }
  | T_POTENCIA numero
    {
      /* Gera instrução POW */
      svm_add_instruction(&vm, OP_POW, $2, 0, 0);
    }
  | T_IMPRIMIR saida
  ;

saida
  : T_STR
    {
      /* Adiciona string ao pool e gera PRINTS */
      int idx = svm_add_string(&vm, $1);
      svm_add_instruction(&vm, OP_PRINTS, idx, 0, 0);
      free($1);
    }
  | T_IDENT
    {
      /* Carrega variável em R0 e imprime */
      int var_idx = svm_get_variable_idx(&vm, $1);
      if (var_idx < 0) {
        fprintf(stderr, "[parser] Variável não definida: %s\n", $1);
        var_idx = svm_add_variable(&vm, $1);
      }
      svm_add_instruction(&vm, OP_LOADV, REG_R0, var_idx, 0);
      svm_add_instruction(&vm, OP_PRINT, REG_R0, 0, 0);
      free($1);
    }
  | T_TEMP
    {
      /* Carrega sensor TEMP em R0 e imprime */
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_TEMP, 0);
      svm_add_instruction(&vm, OP_PRINT, REG_R0, 0, 0);
    }
  | T_PESO
    {
      /* Carrega sensor PESO em R0 e imprime */
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_PESO, 0);
      svm_add_instruction(&vm, OP_PRINT, REG_R0, 0, 0);
    }
  ;

atribuicao
  : T_SET T_IDENT '=' expr
    {
      /* Cria variável se não existe e armazena valor de R0 */
      int var_idx = svm_get_variable_idx(&vm, $2);
      if (var_idx < 0) {
        var_idx = svm_add_variable(&vm, $2);
      }
      /* expr já deixou resultado em R0 */
      svm_add_instruction(&vm, OP_STORE, var_idx, REG_R0, 0);
      free($2);
    }
  ;

if_stmt
  : T_SE if_start cond ':' bloco if_end_simple
  | T_SE if_start cond ':' bloco T_SENAO if_else_mark ':' bloco if_end_else
  ;

if_start
  : /* vazio */
    {
      /* Prepara labels para if */
      char* else_lbl = new_label("else");
      char* end_lbl = new_label("endif");
      strcpy(if_else[if_depth], else_lbl);
      strcpy(if_end[if_depth], end_lbl);
      if_depth++;
    }
  ;

if_end_simple
  : /* vazio */
    {
      /* Marca fim do if (sem else) - else e endif são o mesmo ponto */
      if_depth--;
      int addr = vm.program_size;
      svm_add_label(&vm, if_else[if_depth]);
      
      /* Resolve saltos pendentes que apontam para este if */
      for (int i = 0; i < vm.program_size; i++) {
        if (vm.program[i].arg1 == -2) {
          switch (vm.program[i].op) {
            case OP_JEQ: case OP_JNE: case OP_JLT: 
            case OP_JLE: case OP_JGT: case OP_JGE:
              vm.program[i].arg1 = addr;
              break;
            default:
              break;
          }
        }
      }
    }
  ;

if_else_mark
  : /* vazio */
    {
      /* Primeiro, resolve os saltos da condição para apontar ao else */
      int else_addr = vm.program_size + 1;  /* +1 porque vamos adicionar JMP antes */
      
      /* Salta para endif após bloco then */
      svm_add_instruction(&vm, OP_JMP, -3, 0, 0);  /* -3 = marcador para endif */
      
      /* Marca label else */
      svm_add_label(&vm, if_else[if_depth - 1]);
      
      /* Resolve saltos pendentes da condição para apontar aqui */
      for (int i = 0; i < vm.program_size; i++) {
        if (vm.program[i].arg1 == -2) {
          switch (vm.program[i].op) {
            case OP_JEQ: case OP_JNE: case OP_JLT: 
            case OP_JLE: case OP_JGT: case OP_JGE:
              vm.program[i].arg1 = else_addr;
              break;
            default:
              break;
          }
        }
      }
    }
  ;

if_end_else
  : /* vazio */
    {
      if_depth--;
      /* Marca endif */
      int endif_addr = vm.program_size;
      svm_add_label(&vm, if_end[if_depth]);
      
      /* Resolve o JMP -3 pendente (salto do then para endif) */
      for (int i = vm.program_size - 1; i >= 0; i--) {
        if (vm.program[i].op == OP_JMP && vm.program[i].arg1 == -3) {
          vm.program[i].arg1 = endif_addr;
          break;
        }
      }
    }
  ;

while_stmt
  : T_ENQUANTO while_start loop_cond ':' bloco while_end
  ;

while_start
  : /* vazio */
    {
      /* Prepara labels para while */
      char* start_lbl = new_label("while");
      char* end_lbl = new_label("endwhile");
      strcpy(loop_start[loop_depth], start_lbl);
      strcpy(loop_end[loop_depth], end_lbl);
      loop_depth++;
      
      /* Marca início do loop */
      svm_add_label(&vm, start_lbl);
    }
  ;

while_end
  : /* vazio */
    {
      loop_depth--;
      /* Salta de volta para o início */
      int start_addr = svm_get_label_addr(&vm, loop_start[loop_depth]);
      svm_add_instruction(&vm, OP_JMP, start_addr, 0, 0);
      
      /* Marca fim do loop */
      int end_addr = vm.program_size;
      svm_add_label(&vm, loop_end[loop_depth]);
      
      /* Resolve saltos pendentes da condição (marcador -4) para apontar para endwhile */
      for (int i = 0; i < vm.program_size; i++) {
        if (vm.program[i].arg1 == -4) {
          switch (vm.program[i].op) {
            case OP_JEQ: case OP_JNE: case OP_JLT: 
            case OP_JLE: case OP_JGT: case OP_JGE:
              vm.program[i].arg1 = end_addr;
              break;
            default:
              break;
          }
        }
      }
    }
  ;

bloco
  : '{' lista_declaracoes '}'
  ;

lista_declaracoes
  : %empty
  | lista_declaracoes declaracao
  ;

/* ---------- Condições ---------- */
loop_cond
  : T_SEMPRE
    {
      /* Loop infinito - não gera condição de saída */
    }
  | cond
  ;

cond
  : cond T_OU cond_or_marker cond
    {
      /* OR: se o primeiro foi verdadeiro, pula para o corpo */
      /* Implementação simplificada: avalia ambos */
    }
  | cond T_E cond
    {
      /* AND: ambas condições devem ser verdadeiras */
      /* As condições já geraram os saltos apropriados */
    }
  | comparacao
  | '(' cond ')'
  ;

cond_or_marker
  : /* vazio para OR */
  ;

comparacao
  : lado_esq comparador lado_dir
    {
      /* lado_esq está em R0, lado_dir em R1 */
      /* Gera CMP e salto condicional */
      svm_add_instruction(&vm, OP_CMP, REG_R0, REG_R1, 0);
      
      /* Usa marcador diferente para while (-4) vs if (-2) */
      int marker;
      if (loop_depth > 0 && if_depth == 0) {
        marker = -4;  /* while */
      } else {
        marker = -2;  /* if */
      }
      
      switch ($2) {
        case T_EQ:  /* == : salta se NE (não igual) */
          svm_add_instruction(&vm, OP_JNE, marker, 0, 0);
          break;
        case T_NE:  /* != : salta se EQ */
          svm_add_instruction(&vm, OP_JEQ, marker, 0, 0);
          break;
        case T_LT:  /* < : salta se GE */
          svm_add_instruction(&vm, OP_JGE, marker, 0, 0);
          break;
        case T_LE:  /* <= : salta se GT */
          svm_add_instruction(&vm, OP_JGT, marker, 0, 0);
          break;
        case T_GT:  /* > : salta se LE */
          svm_add_instruction(&vm, OP_JLE, marker, 0, 0);
          break;
        case T_GE:  /* >= : salta se LT */
          svm_add_instruction(&vm, OP_JLT, marker, 0, 0);
          break;
      }
    }
  ;

comparador
  : T_EQ { $$ = T_EQ; }
  | T_NE { $$ = T_NE; }
  | T_LT { $$ = T_LT; }
  | T_LE { $$ = T_LE; }
  | T_GT { $$ = T_GT; }
  | T_GE { $$ = T_GE; }
  ;

lado_esq
  : T_IDENT
    {
      /* Carrega variável em R0 */
      int var_idx = svm_get_variable_idx(&vm, $1);
      if (var_idx < 0) {
        fprintf(stderr, "[parser] Variável não definida: %s\n", $1);
        var_idx = svm_add_variable(&vm, $1);
      }
      svm_add_instruction(&vm, OP_LOADV, REG_R0, var_idx, 0);
      free($1);
    }
  | T_TEMP
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_TEMP, 0);
    }
  | T_PESO
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_PESO, 0);
    }
  ;

lado_dir
  : T_IDENT
    {
      /* Carrega variável em R1 */
      int var_idx = svm_get_variable_idx(&vm, $1);
      if (var_idx < 0) {
        fprintf(stderr, "[parser] Variável não definida: %s\n", $1);
        var_idx = svm_add_variable(&vm, $1);
      }
      svm_add_instruction(&vm, OP_LOADV, REG_R1, var_idx, 0);
      free($1);
    }
  | T_TEMP
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R1, SENSOR_TEMP, 0);
    }
  | T_PESO
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R1, SENSOR_PESO, 0);
    }
  | numero
    {
      svm_add_instruction(&vm, OP_SET, REG_R1, $1, 0);
    }
  ;

/* ---------- Expressões simples ---------- */
expr
  : numero
    {
      svm_add_instruction(&vm, OP_SET, REG_R0, $1, 0);
      $$ = $1;
    }
  | T_IDENT
    {
      int var_idx = svm_get_variable_idx(&vm, $1);
      if (var_idx < 0) {
        fprintf(stderr, "[parser] Variável não definida: %s\n", $1);
        var_idx = svm_add_variable(&vm, $1);
      }
      svm_add_instruction(&vm, OP_LOADV, REG_R0, var_idx, 0);
      $$ = 0;
      free($1);
    }
  | T_TEMP
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_TEMP, 0);
      $$ = 0;
    }
  | T_PESO
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_PESO, 0);
      $$ = 0;
    }
  ;

sensor
  : T_TEMP { $$ = SENSOR_TEMP; }
  | T_PESO { $$ = SENSOR_PESO; }
  ;

numero
  : T_NUM
  ;

tempo
  : T_TIME
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "[parser] erro de sintaxe na linha %d: %s\n", yylineno, s);
}

/* Resolve saltos pendentes */
static void resolve_jumps(SaunaVM* vm) {
  for (int i = 0; i < vm->program_size; i++) {
    SVM_Instruction* instr = &vm->program[i];
    
    /* Saltos com endereço -2 apontam para o label else/endif mais próximo */
    if (instr->arg1 == -2) {
      switch (instr->op) {
        case OP_JMP:
        case OP_JEQ:
        case OP_JNE:
        case OP_JLT:
        case OP_JLE:
        case OP_JGT:
        case OP_JGE:
          /* Procura o próximo label após esta instrução */
          for (int j = 0; j < vm->label_count; j++) {
            if (vm->labels[j].address > i) {
              instr->arg1 = vm->labels[j].address;
              break;
            }
          }
          /* Se não encontrou, aponta para o fim do programa */
          if (instr->arg1 == -2) {
            instr->arg1 = vm->program_size;
          }
          break;
        default:
          break;
      }
    }
  }
}

/* Driver */
int main(int argc, char** argv) {
  int show_asm = 0;
  int show_state = 0;
  char* filename = NULL;
  
  /* Parse argumentos */
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
      show_asm = 1;
      show_state = 1;
    } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--asm") == 0) {
      show_asm = 1;
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf("Uso: %s [opções] <arquivo.snl>\n", argv[0]);
      printf("Opções:\n");
      printf("  -d, --debug   Mostra assembly gerado e estado final\n");
      printf("  -a, --asm     Mostra apenas assembly gerado\n");
      printf("  -h, --help    Mostra esta ajuda\n");
      return 0;
    } else {
      filename = argv[i];
    }
  }
  
  if (!filename) {
    fprintf(stderr, "Uso: %s [opções] <arquivo.snl>\n", argv[0]);
    return 1;
  }
  
  FILE* f = fopen(filename, "r");
  if (!f) { 
    perror("Erro ao abrir arquivo"); 
    return 1; 
  }
  
  /* Inicializa VM */
  svm_init(&vm);
  
  /* Parse e geração de código */
  yyin = f;
  int ret = yyparse();
  fclose(f);
  
  if (ret != 0) {
    printf("Falha: erros de sintaxe encontrados.\n");
    return ret;
  }
  
  /* Adiciona HALT no final se não existe */
  if (vm.program_size == 0 || vm.program[vm.program_size - 1].op != OP_HALT) {
    svm_add_instruction(&vm, OP_HALT, 0, 0, 0);
  }
  
  /* Resolve saltos pendentes */
  resolve_jumps(&vm);
  
  printf("OK: análise léxica e sintática concluída.\n");
  printf("Programa compilado: %d instruções\n\n", vm.program_size);
  
  /* Mostra assembly se solicitado */
  if (show_asm) {
    svm_disassemble(&vm);
    printf("\n");
  }
  
  /* Executa */
  printf("=== Executando na SaunaVM ===\n\n");
  svm_run(&vm, 100000);  /* Limite de 100k passos */
  
  /* Mostra estado final se solicitado */
  if (show_state) {
    printf("\n");
    svm_print_state(&vm);
  }
  
  return 0;
}

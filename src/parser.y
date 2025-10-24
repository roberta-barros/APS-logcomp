%define parse.error verbose
%code top {
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  extern int yylex(void);
  void yyerror(const char *s);
  extern int yylineno;
  extern FILE *yyin;
}

/* Valores semânticos */
%union {
  int   ival;
  char* sval;
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
  | T_POTENCIA numero
  | T_IMPRIMIR saida
  ;

saida
  : T_STR
  | T_IDENT
  | T_TEMP
  | T_PESO
  ;

atribuicao
  : T_SET T_IDENT '=' expr
  ;

if_stmt
  : T_SE cond ':' bloco
  | T_SE cond ':' bloco T_SENAO ':' bloco
  ;

while_stmt
  : T_ENQUANTO loop_cond ':' bloco
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
  | cond
  ;

cond
  : cond T_OU cond
  | cond T_E  cond
  | comparacao
  | '(' cond ')'
  ;

comparacao
  : lado_esq T_EQ lado_dir
  | lado_esq T_NE lado_dir
  | lado_esq T_LT lado_dir
  | lado_esq T_LE lado_dir
  | lado_esq T_GT lado_dir
  | lado_esq T_GE lado_dir
  ;

lado_esq
  : T_IDENT
  | T_TEMP
  | T_PESO
  ;

lado_dir
  : T_IDENT
  | T_TEMP
  | T_PESO
  | numero
  ;

/* ---------- Expressões simples ---------- */
/* Damos valor explícito a $$ para evitar a ação-padrão (que causava o type clash) */
expr
  : numero               { $$ = $1; }
  | T_IDENT              { $$ = 0; }
  | T_TEMP               { $$ = 0; }
  | T_PESO               { $$ = 0; }
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

/* Driver */
int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Uso: %s <arquivo.snl>\n", argv[0]);
    return 1;
  }
  FILE* f = fopen(argv[1], "r");
  if (!f) { perror("Erro ao abrir arquivo"); return 1; }
  yyin = f;
  int ret = yyparse();
  if (ret == 0) {
    printf("OK: análise léxica e sintática concluída.\n");
  } else {
    printf("Falha: erros de sintaxe encontrados.\n");
  }
  fclose(f);
  return ret;
}

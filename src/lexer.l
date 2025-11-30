%option noyywrap nodefault yylineno noinput nounput
%{
  #if defined(_WIN32)
    #include <io.h>
    #define isatty  _isatty
    #define fileno  _fileno
  #else
    #include <unistd.h>
  #endif
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "parser.tab.h"

  static char* dupstr(const char* s) {
    size_t n = strlen(s);
    char* p = (char*)malloc(n+1);
    memcpy(p, s, n+1);
    return p;
  }
%}

%%
[ \t\r]+                ;
\n                      ;

"//".*                  ;
"#".*                   ;

"se"                    { return T_SE; }
"senao"                 { return T_SENAO; }
"enquanto"              { return T_ENQUANTO; }
"sempre"                { return T_SEMPRE; }

"set"                   { return T_SET; }
"aquecer"               { return T_AQUECER; }
"potencia"              { return T_POTENCIA; }
"imprimir"              { return T_IMPRIMIR; }

"temp"                  { return T_TEMP; }
"peso"                  { return T_PESO; }

"e"                     { return T_E; }
"ou"                    { return T_OU; }

"=="                    { return T_EQ; }
"!="                    { return T_NE; }
"<="                    { return T_LE; }
">="                    { return T_GE; }
"<"                     { return T_LT; }
">"                     { return T_GT; }

";"                     { return ';'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
":"                     { return ':'; }
"="                     { return '='; }
"("                     { return '('; }  
")"                     { return ')'; }

[+-]?[0-9]+[sS]         {
                          int val = 0;
                          char* buf = (char*)malloc(yyleng);
                          memcpy(buf, yytext, yyleng-1); /* remove 's' final */
                          buf[yyleng-1] = '\0';
                          val = atoi(buf);
                          free(buf);
                          yylval.ival = val;
                          return T_TIME;
                        }

[+-]?[0-9]+             { yylval.ival = atoi(yytext); return T_NUM; }

\"([^\\\"]|\\.)*\"      { yylval.sval = dupstr(yytext); return T_STR; }

[A-Za-z_][A-Za-z0-9_]*  { yylval.sval = dupstr(yytext); return T_IDENT; }

.                       {
                          fprintf(stderr, "[lex] caractere inválido '%s' na linha %d\n", yytext, yylineno);
                          return T_ERROR;
                        }
%%

/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 2 "parser.y"

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

#line 102 "parser.tab.c"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_NUM = 3,                      /* T_NUM  */
  YYSYMBOL_T_TIME = 4,                     /* T_TIME  */
  YYSYMBOL_T_STR = 5,                      /* T_STR  */
  YYSYMBOL_T_IDENT = 6,                    /* T_IDENT  */
  YYSYMBOL_T_SE = 7,                       /* T_SE  */
  YYSYMBOL_T_SENAO = 8,                    /* T_SENAO  */
  YYSYMBOL_T_ENQUANTO = 9,                 /* T_ENQUANTO  */
  YYSYMBOL_T_SEMPRE = 10,                  /* T_SEMPRE  */
  YYSYMBOL_T_SET = 11,                     /* T_SET  */
  YYSYMBOL_T_AQUECER = 12,                 /* T_AQUECER  */
  YYSYMBOL_T_POTENCIA = 13,                /* T_POTENCIA  */
  YYSYMBOL_T_IMPRIMIR = 14,                /* T_IMPRIMIR  */
  YYSYMBOL_T_TEMP = 15,                    /* T_TEMP  */
  YYSYMBOL_T_PESO = 16,                    /* T_PESO  */
  YYSYMBOL_T_E = 17,                       /* T_E  */
  YYSYMBOL_T_OU = 18,                      /* T_OU  */
  YYSYMBOL_T_EQ = 19,                      /* T_EQ  */
  YYSYMBOL_T_NE = 20,                      /* T_NE  */
  YYSYMBOL_T_LT = 21,                      /* T_LT  */
  YYSYMBOL_T_LE = 22,                      /* T_LE  */
  YYSYMBOL_T_GT = 23,                      /* T_GT  */
  YYSYMBOL_T_GE = 24,                      /* T_GE  */
  YYSYMBOL_T_ERROR = 25,                   /* T_ERROR  */
  YYSYMBOL_26_ = 26,                       /* ';'  */
  YYSYMBOL_27_ = 27,                       /* '='  */
  YYSYMBOL_28_ = 28,                       /* ':'  */
  YYSYMBOL_29_ = 29,                       /* '{'  */
  YYSYMBOL_30_ = 30,                       /* '}'  */
  YYSYMBOL_31_ = 31,                       /* '('  */
  YYSYMBOL_32_ = 32,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_programa = 34,                  /* programa  */
  YYSYMBOL_declaracao = 35,                /* declaracao  */
  YYSYMBOL_acao = 36,                      /* acao  */
  YYSYMBOL_saida = 37,                     /* saida  */
  YYSYMBOL_atribuicao = 38,                /* atribuicao  */
  YYSYMBOL_if_stmt = 39,                   /* if_stmt  */
  YYSYMBOL_if_start = 40,                  /* if_start  */
  YYSYMBOL_if_end_simple = 41,             /* if_end_simple  */
  YYSYMBOL_if_else_mark = 42,              /* if_else_mark  */
  YYSYMBOL_if_end_else = 43,               /* if_end_else  */
  YYSYMBOL_while_stmt = 44,                /* while_stmt  */
  YYSYMBOL_while_start = 45,               /* while_start  */
  YYSYMBOL_while_end = 46,                 /* while_end  */
  YYSYMBOL_bloco = 47,                     /* bloco  */
  YYSYMBOL_lista_declaracoes = 48,         /* lista_declaracoes  */
  YYSYMBOL_loop_cond = 49,                 /* loop_cond  */
  YYSYMBOL_cond = 50,                      /* cond  */
  YYSYMBOL_cond_or_marker = 51,            /* cond_or_marker  */
  YYSYMBOL_comparacao = 52,                /* comparacao  */
  YYSYMBOL_comparador = 53,                /* comparador  */
  YYSYMBOL_lado_esq = 54,                  /* lado_esq  */
  YYSYMBOL_lado_dir = 55,                  /* lado_dir  */
  YYSYMBOL_expr = 56,                      /* expr  */
  YYSYMBOL_numero = 57,                    /* numero  */
  YYSYMBOL_tempo = 58                      /* tempo  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   72

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  78

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   280


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      31,    32,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    28,    26,
       2,    27,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    72,    76,    77,    78,    79,    83,    88,
      93,    97,   104,   116,   122,   131,   145,   146,   151,   163,
     187,   215,   232,   237,   252,   279,   283,   284,   289,   293,
     297,   302,   307,   308,   312,   316,   354,   355,   356,   357,
     358,   359,   363,   374,   378,   385,   396,   400,   404,   412,
     417,   428,   433,   446,   450
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_NUM", "T_TIME",
  "T_STR", "T_IDENT", "T_SE", "T_SENAO", "T_ENQUANTO", "T_SEMPRE", "T_SET",
  "T_AQUECER", "T_POTENCIA", "T_IMPRIMIR", "T_TEMP", "T_PESO", "T_E",
  "T_OU", "T_EQ", "T_NE", "T_LT", "T_LE", "T_GT", "T_GE", "T_ERROR", "';'",
  "'='", "':'", "'{'", "'}'", "'('", "')'", "$accept", "programa",
  "declaracao", "acao", "saida", "atribuicao", "if_stmt", "if_start",
  "if_end_simple", "if_else_mark", "if_end_else", "while_stmt",
  "while_start", "while_end", "bloco", "lista_declaracoes", "loop_cond",
  "cond", "cond_or_marker", "comparacao", "comparador", "lado_esq",
  "lado_dir", "expr", "numero", "tempo", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-49)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -49,    33,   -49,   -49,   -49,    -2,     2,    11,    49,   -49,
       3,     6,   -49,   -49,    -3,    -5,     9,   -49,   -49,   -49,
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,    -3,    13,   -49,    48,   -49,    -4,    17,    45,    -9,
      -3,   -49,    10,   -49,   -49,   -49,   -49,   -49,   -49,    47,
      10,   -49,   -49,   -49,   -49,   -49,   -49,   -49,    -3,   -49,
      29,   -49,   -49,   -49,   -49,   -49,   -49,    32,     8,   -49,
     -49,   -49,   -49,   -49,    24,    10,   -49,   -49
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    18,    23,     0,     0,     0,     0,     3,
       0,     0,     6,     7,     0,     0,     0,    54,     8,    53,
       9,    11,    12,    13,    14,    10,     4,     5,    42,    43,
      44,     0,     0,    32,     0,    28,     0,    29,     0,     0,
       0,    34,     0,    36,    37,    38,    39,    40,    41,     0,
       0,    50,    51,    52,    15,    49,    33,    31,     0,    26,
      19,    45,    46,    47,    35,    48,    24,    30,     0,    20,
      16,    22,    25,    27,     0,     0,    21,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -49,   -49,   -12,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -49,   -49,   -48,   -49,   -49,   -15,   -49,   -49,
     -49,   -49,   -49,   -49,   -31,   -49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     9,    10,    25,    11,    12,    14,    70,    74,
      77,    13,    15,    71,    60,    68,    36,    32,    58,    33,
      49,    34,    64,    54,    20,    18
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      37,    28,    66,    28,    16,    35,    17,    55,    40,    41,
      29,    30,    29,    30,    19,     3,    39,     4,    65,     5,
       6,     7,     8,    56,    50,    57,    31,    76,    31,    26,
      40,    41,    27,     2,    40,    41,    38,    69,    72,    59,
       3,    42,     4,    67,     5,     6,     7,     8,    19,    40,
      19,    51,    75,    61,    21,    22,    73,     0,     0,     0,
      52,    53,    62,    63,    23,    24,     0,    43,    44,    45,
      46,    47,    48
};

static const yytype_int8 yycheck[] =
{
      15,     6,    50,     6,     6,    10,     4,    38,    17,    18,
      15,    16,    15,    16,     3,     7,    31,     9,    49,    11,
      12,    13,    14,    32,    28,    40,    31,    75,    31,    26,
      17,    18,    26,     0,    17,    18,    27,     8,    30,    29,
       7,    28,     9,    58,    11,    12,    13,    14,     3,    17,
       3,     6,    28,     6,     5,     6,    68,    -1,    -1,    -1,
      15,    16,    15,    16,    15,    16,    -1,    19,    20,    21,
      22,    23,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    34,     0,     7,     9,    11,    12,    13,    14,    35,
      36,    38,    39,    44,    40,    45,     6,     4,    58,     3,
      57,     5,     6,    15,    16,    37,    26,    26,     6,    15,
      16,    31,    50,    52,    54,    10,    49,    50,    27,    50,
      17,    18,    28,    19,    20,    21,    22,    23,    24,    53,
      28,     6,    15,    16,    56,    57,    32,    50,    51,    29,
      47,     6,    15,    16,    55,    57,    47,    50,    48,     8,
      41,    46,    30,    35,    42,    28,    47,    43
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    34,    35,    35,    35,    35,    36,    36,
      36,    37,    37,    37,    37,    38,    39,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    48,    49,    49,
      50,    50,    50,    50,    51,    52,    53,    53,    53,    53,
      53,    53,    54,    54,    54,    55,    55,    55,    55,    56,
      56,    56,    56,    57,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     1,     1,     2,     2,
       2,     1,     1,     1,     1,     4,     6,    10,     0,     0,
       0,     0,     6,     0,     0,     3,     0,     2,     1,     1,
       4,     3,     1,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* acao: T_AQUECER tempo  */
#line 84 "parser.y"
    {
      /* Gera instrução HEAT */
      svm_add_instruction(&vm, OP_HEAT, (yyvsp[0].ival), 0, 0);
    }
#line 1474 "parser.tab.c"
    break;

  case 9: /* acao: T_POTENCIA numero  */
#line 89 "parser.y"
    {
      /* Gera instrução POW */
      svm_add_instruction(&vm, OP_POW, (yyvsp[0].ival), 0, 0);
    }
#line 1483 "parser.tab.c"
    break;

  case 11: /* saida: T_STR  */
#line 98 "parser.y"
    {
      /* Adiciona string ao pool e gera PRINTS */
      int idx = svm_add_string(&vm, (yyvsp[0].sval));
      svm_add_instruction(&vm, OP_PRINTS, idx, 0, 0);
      free((yyvsp[0].sval));
    }
#line 1494 "parser.tab.c"
    break;

  case 12: /* saida: T_IDENT  */
#line 105 "parser.y"
    {
      /* Carrega variável em R0 e imprime */
      int var_idx = svm_get_variable_idx(&vm, (yyvsp[0].sval));
      if (var_idx < 0) {
        fprintf(stderr, "[parser] Variável não definida: %s\n", (yyvsp[0].sval));
        var_idx = svm_add_variable(&vm, (yyvsp[0].sval));
      }
      svm_add_instruction(&vm, OP_LOADV, REG_R0, var_idx, 0);
      svm_add_instruction(&vm, OP_PRINT, REG_R0, 0, 0);
      free((yyvsp[0].sval));
    }
#line 1510 "parser.tab.c"
    break;

  case 13: /* saida: T_TEMP  */
#line 117 "parser.y"
    {
      /* Carrega sensor TEMP em R0 e imprime */
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_TEMP, 0);
      svm_add_instruction(&vm, OP_PRINT, REG_R0, 0, 0);
    }
#line 1520 "parser.tab.c"
    break;

  case 14: /* saida: T_PESO  */
#line 123 "parser.y"
    {
      /* Carrega sensor PESO em R0 e imprime */
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_PESO, 0);
      svm_add_instruction(&vm, OP_PRINT, REG_R0, 0, 0);
    }
#line 1530 "parser.tab.c"
    break;

  case 15: /* atribuicao: T_SET T_IDENT '=' expr  */
#line 132 "parser.y"
    {
      /* Cria variável se não existe e armazena valor de R0 */
      int var_idx = svm_get_variable_idx(&vm, (yyvsp[-2].sval));
      if (var_idx < 0) {
        var_idx = svm_add_variable(&vm, (yyvsp[-2].sval));
      }
      /* expr já deixou resultado em R0 */
      svm_add_instruction(&vm, OP_STORE, var_idx, REG_R0, 0);
      free((yyvsp[-2].sval));
    }
#line 1545 "parser.tab.c"
    break;

  case 18: /* if_start: %empty  */
#line 151 "parser.y"
    {
      /* Prepara labels para if */
      char* else_lbl = new_label("else");
      char* end_lbl = new_label("endif");
      strcpy(if_else[if_depth], else_lbl);
      strcpy(if_end[if_depth], end_lbl);
      if_depth++;
    }
#line 1558 "parser.tab.c"
    break;

  case 19: /* if_end_simple: %empty  */
#line 163 "parser.y"
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
#line 1583 "parser.tab.c"
    break;

  case 20: /* if_else_mark: %empty  */
#line 187 "parser.y"
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
#line 1612 "parser.tab.c"
    break;

  case 21: /* if_end_else: %empty  */
#line 215 "parser.y"
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
#line 1631 "parser.tab.c"
    break;

  case 23: /* while_start: %empty  */
#line 237 "parser.y"
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
#line 1647 "parser.tab.c"
    break;

  case 24: /* while_end: %empty  */
#line 252 "parser.y"
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
#line 1676 "parser.tab.c"
    break;

  case 28: /* loop_cond: T_SEMPRE  */
#line 290 "parser.y"
    {
      /* Loop infinito - não gera condição de saída */
    }
#line 1684 "parser.tab.c"
    break;

  case 30: /* cond: cond T_OU cond_or_marker cond  */
#line 298 "parser.y"
    {
      /* OR: se o primeiro foi verdadeiro, pula para o corpo */
      /* Implementação simplificada: avalia ambos */
    }
#line 1693 "parser.tab.c"
    break;

  case 31: /* cond: cond T_E cond  */
#line 303 "parser.y"
    {
      /* AND: ambas condições devem ser verdadeiras */
      /* As condições já geraram os saltos apropriados */
    }
#line 1702 "parser.tab.c"
    break;

  case 35: /* comparacao: lado_esq comparador lado_dir  */
#line 317 "parser.y"
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
      
      switch ((yyvsp[-1].cmp_op)) {
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
#line 1741 "parser.tab.c"
    break;

  case 36: /* comparador: T_EQ  */
#line 354 "parser.y"
         { (yyval.cmp_op) = T_EQ; }
#line 1747 "parser.tab.c"
    break;

  case 37: /* comparador: T_NE  */
#line 355 "parser.y"
         { (yyval.cmp_op) = T_NE; }
#line 1753 "parser.tab.c"
    break;

  case 38: /* comparador: T_LT  */
#line 356 "parser.y"
         { (yyval.cmp_op) = T_LT; }
#line 1759 "parser.tab.c"
    break;

  case 39: /* comparador: T_LE  */
#line 357 "parser.y"
         { (yyval.cmp_op) = T_LE; }
#line 1765 "parser.tab.c"
    break;

  case 40: /* comparador: T_GT  */
#line 358 "parser.y"
         { (yyval.cmp_op) = T_GT; }
#line 1771 "parser.tab.c"
    break;

  case 41: /* comparador: T_GE  */
#line 359 "parser.y"
         { (yyval.cmp_op) = T_GE; }
#line 1777 "parser.tab.c"
    break;

  case 42: /* lado_esq: T_IDENT  */
#line 364 "parser.y"
    {
      /* Carrega variável em R0 */
      int var_idx = svm_get_variable_idx(&vm, (yyvsp[0].sval));
      if (var_idx < 0) {
        fprintf(stderr, "[parser] Variável não definida: %s\n", (yyvsp[0].sval));
        var_idx = svm_add_variable(&vm, (yyvsp[0].sval));
      }
      svm_add_instruction(&vm, OP_LOADV, REG_R0, var_idx, 0);
      free((yyvsp[0].sval));
    }
#line 1792 "parser.tab.c"
    break;

  case 43: /* lado_esq: T_TEMP  */
#line 375 "parser.y"
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_TEMP, 0);
    }
#line 1800 "parser.tab.c"
    break;

  case 44: /* lado_esq: T_PESO  */
#line 379 "parser.y"
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_PESO, 0);
    }
#line 1808 "parser.tab.c"
    break;

  case 45: /* lado_dir: T_IDENT  */
#line 386 "parser.y"
    {
      /* Carrega variável em R1 */
      int var_idx = svm_get_variable_idx(&vm, (yyvsp[0].sval));
      if (var_idx < 0) {
        fprintf(stderr, "[parser] Variável não definida: %s\n", (yyvsp[0].sval));
        var_idx = svm_add_variable(&vm, (yyvsp[0].sval));
      }
      svm_add_instruction(&vm, OP_LOADV, REG_R1, var_idx, 0);
      free((yyvsp[0].sval));
    }
#line 1823 "parser.tab.c"
    break;

  case 46: /* lado_dir: T_TEMP  */
#line 397 "parser.y"
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R1, SENSOR_TEMP, 0);
    }
#line 1831 "parser.tab.c"
    break;

  case 47: /* lado_dir: T_PESO  */
#line 401 "parser.y"
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R1, SENSOR_PESO, 0);
    }
#line 1839 "parser.tab.c"
    break;

  case 48: /* lado_dir: numero  */
#line 405 "parser.y"
    {
      svm_add_instruction(&vm, OP_SET, REG_R1, (yyvsp[0].ival), 0);
    }
#line 1847 "parser.tab.c"
    break;

  case 49: /* expr: numero  */
#line 413 "parser.y"
    {
      svm_add_instruction(&vm, OP_SET, REG_R0, (yyvsp[0].ival), 0);
      (yyval.ival) = (yyvsp[0].ival);
    }
#line 1856 "parser.tab.c"
    break;

  case 50: /* expr: T_IDENT  */
#line 418 "parser.y"
    {
      int var_idx = svm_get_variable_idx(&vm, (yyvsp[0].sval));
      if (var_idx < 0) {
        fprintf(stderr, "[parser] Variável não definida: %s\n", (yyvsp[0].sval));
        var_idx = svm_add_variable(&vm, (yyvsp[0].sval));
      }
      svm_add_instruction(&vm, OP_LOADV, REG_R0, var_idx, 0);
      (yyval.ival) = 0;
      free((yyvsp[0].sval));
    }
#line 1871 "parser.tab.c"
    break;

  case 51: /* expr: T_TEMP  */
#line 429 "parser.y"
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_TEMP, 0);
      (yyval.ival) = 0;
    }
#line 1880 "parser.tab.c"
    break;

  case 52: /* expr: T_PESO  */
#line 434 "parser.y"
    {
      svm_add_instruction(&vm, OP_LOAD, REG_R0, SENSOR_PESO, 0);
      (yyval.ival) = 0;
    }
#line 1889 "parser.tab.c"
    break;


#line 1893 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 453 "parser.y"


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

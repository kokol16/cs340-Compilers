/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include "bison_functions/bison_functions.h"
#include <stdio.h>
extern FILE * yyin;
extern int yylineno; 
int func_line=0;
SymbolTable *  symbolTable;
FILE *output_file;
int yylex(void);
short is_local_id=0;
int yyerror( char * msg );
unsigned int  scope=0;
unsigned int need_check=0;
unsigned int iam_in_function=0;
unsigned int iam_in_loop=0;
function_stack * functions_stack=NULL;



#line 86 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTEGER = 259,
    FLOAT = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    FOR = 264,
    FUNCTION = 265,
    RETURN = 266,
    BREAK = 267,
    CONTINUE = 268,
    AND = 269,
    NOT = 270,
    OR = 271,
    LOCALL = 272,
    TRUE = 273,
    FALSE = 274,
    NIL = 275,
    STRING = 276,
    EQUALS = 277,
    PLUS = 278,
    ASSIGN = 279,
    MINUS = 280,
    UMINUS = 281,
    ASTERISK = 282,
    DIVISION = 283,
    PERCENT = 284,
    DIFFERENT = 285,
    PLUS_PLUS = 286,
    MINUS_MINUS = 287,
    GREATER = 288,
    LESS = 289,
    GREATER_EQUALS = 290,
    LESS_EQUALS = 291,
    SEMICOLON = 292,
    COMMA = 293,
    COLON = 294,
    DOUBLE_COLON = 295,
    DOT = 296,
    Diaeresis = 297,
    LEFT_BRACE = 298,
    RIGHT_BRACE = 299,
    LEFT_SQUARE = 300,
    RIGHT_SQUARE = 301,
    LEFT_BRACKETS = 302,
    RIGHT_BRACKETS = 303
  };
#endif
/* Tokens.  */
#define ID 258
#define INTEGER 259
#define FLOAT 260
#define IF 261
#define ELSE 262
#define WHILE 263
#define FOR 264
#define FUNCTION 265
#define RETURN 266
#define BREAK 267
#define CONTINUE 268
#define AND 269
#define NOT 270
#define OR 271
#define LOCALL 272
#define TRUE 273
#define FALSE 274
#define NIL 275
#define STRING 276
#define EQUALS 277
#define PLUS 278
#define ASSIGN 279
#define MINUS 280
#define UMINUS 281
#define ASTERISK 282
#define DIVISION 283
#define PERCENT 284
#define DIFFERENT 285
#define PLUS_PLUS 286
#define MINUS_MINUS 287
#define GREATER 288
#define LESS 289
#define GREATER_EQUALS 290
#define LESS_EQUALS 291
#define SEMICOLON 292
#define COMMA 293
#define COLON 294
#define DOUBLE_COLON 295
#define DOT 296
#define Diaeresis 297
#define LEFT_BRACE 298
#define RIGHT_BRACE 299
#define LEFT_SQUARE 300
#define RIGHT_SQUARE 301
#define LEFT_BRACKETS 302
#define RIGHT_BRACKETS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "parser.y" /* yacc.c:355  */

    struct SymbolTableEntry * exprNode;
	float floatVal;
    int intigerVal;
    //float real;
	char * str;

#line 230 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 247 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  70
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   856

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    51,    51,    52,    53,    54,    55,    56,    57,    65,
      72,    73,    74,    76,    77,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      97,    98,   101,   104,   110,   114,   120,   125,   127,   137,
     138,   139,   140,   141,   143,   144,   145,   146,   148,   149,
     150,   151,   153,   154,   159,   160,   161,   163,   164,   166,
     167,   168,   169,   170,   171,   174,   175,   176,   178,   179,
     182,   184,   184,   185,   185,   187,   187,   189,   189,   193,
     195,   193,   197,   200,   197,   203,   204,   205,   206,   207,
     208,   210,   214,   214,   217,   219,   220,   221,   221,   223,
     223,   224,   224,   227,   235
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTEGER", "FLOAT", "IF", "ELSE",
  "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT",
  "OR", "LOCALL", "TRUE", "FALSE", "NIL", "STRING", "EQUALS", "PLUS",
  "ASSIGN", "MINUS", "UMINUS", "ASTERISK", "DIVISION", "PERCENT",
  "DIFFERENT", "PLUS_PLUS", "MINUS_MINUS", "GREATER", "LESS",
  "GREATER_EQUALS", "LESS_EQUALS", "SEMICOLON", "COMMA", "COLON",
  "DOUBLE_COLON", "DOT", "Diaeresis", "LEFT_BRACE", "RIGHT_BRACE",
  "LEFT_SQUARE", "RIGHT_SQUARE", "LEFT_BRACKETS", "RIGHT_BRACKETS",
  "$accept", "program", "stmt", "statements", "expr", "term", "assignexpr",
  "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elist", "objectdef", "indexed", "indexedelem", "block",
  "$@1", "$@2", "block_func", "$@3", "$@4", "funcdef", "$@5", "$@6", "$@7",
  "$@8", "const", "idlist", "$@9", "ifstmt", "whilestmt", "$@10",
  "forstmt", "$@11", "$@12", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -159

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-159)))

#define YYTABLE_NINF -102

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-102)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     362,  -159,  -159,  -159,   -39,   -36,   -11,    36,   426,    10,
      18,   488,    37,  -159,  -159,  -159,  -159,   488,     2,     2,
    -159,    53,    13,   393,   457,    58,  -159,   362,   677,  -159,
    -159,  -159,    72,  -159,    -4,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,   488,  -159,    22,  -159,    14,  -159,   701,
    -159,  -159,  -159,  -159,  -159,    50,     3,    -4,     3,  -159,
      33,   362,   488,  -159,   654,    34,    35,    41,    -2,    38,
    -159,  -159,   488,   488,   488,   488,   488,   488,   488,   488,
     488,   488,   488,   488,   488,  -159,   488,  -159,  -159,    79,
      82,   488,   106,  -159,  -159,  -159,    85,   488,   158,   509,
     488,   488,    57,    48,  -159,  -159,    49,  -159,   272,   630,
     488,  -159,  -159,    55,  -159,    52,   805,   790,   820,    24,
      24,  -159,  -159,  -159,   820,   227,   227,   227,   227,   773,
    -159,    54,   557,  -159,    59,  -159,   582,  -159,    60,   362,
     533,    63,   488,  -159,   102,    52,  -159,   488,  -159,  -159,
     192,   226,  -159,  -159,  -159,  -159,    99,   362,   488,   725,
     102,    74,    67,   607,  -159,    68,  -159,    80,   362,  -159,
     749,    81,    84,    95,    77,  -159,  -159,  -159,  -159,   488,
     362,    77,   102,    78,  -159,    87,  -159,  -159,  -159,    96,
     362,   362,  -159,   317,  -159,  -159
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    44,    85,    86,     0,     0,     0,    82,     0,     0,
       0,     0,     0,    89,    90,    88,    87,     0,     0,     0,
      12,     0,    73,     0,     0,     0,    14,     2,     0,    29,
      15,    37,    39,    47,    40,    41,    10,    11,    43,     4,
       5,     6,     7,     0,    97,    99,    79,     0,   104,     0,
       8,     9,    32,    45,    31,     0,    33,     0,    35,    46,
       0,     0,     0,    67,    63,     0,     0,    68,     0,     0,
       1,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     0,    34,    36,     0,
       0,     0,     0,    53,    57,    58,     0,     0,     0,     0,
       0,     0,     0,     0,    83,   103,     0,    72,     0,     0,
       0,    65,    66,     0,    30,    42,    27,    28,    25,    16,
      17,    18,    19,    20,    26,    21,    23,    22,    24,    38,
      48,     0,     0,    60,     0,    50,     0,    56,     0,     0,
       0,     0,     0,    80,    94,     0,    74,     0,    64,    69,
       0,     0,    49,    59,    51,    52,    96,     0,     0,     0,
      94,    91,     0,     0,    55,     0,    62,     0,     0,    98,
       0,     0,     0,     0,     0,    70,    54,    61,    95,     0,
       0,     0,    94,    77,    84,     0,   102,    81,    93,     0,
       0,     0,    76,     0,   100,    78
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,  -159,   -21,   -60,    -8,  -159,  -159,  -159,    -1,  -159,
      11,  -159,  -159,  -159,   -88,  -159,    28,  -159,  -159,  -159,
    -159,   -37,  -159,  -159,   -17,  -159,  -159,  -159,  -159,  -159,
    -158,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    93,    94,    95,    65,    35,    66,    67,    36,    60,
      61,   184,   189,   190,    37,   103,   160,    47,   144,    38,
     162,   173,    39,    40,   100,    41,   101,   102,    42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,   108,   172,    52,   134,     1,    71,    69,    43,    54,
     138,    44,    72,   141,    73,    64,    68,    56,    58,    12,
      74,    75,   148,    76,   188,    77,    78,    79,    80,    57,
      57,    81,    82,    83,    84,    99,    45,    96,   106,    46,
      53,    97,    21,    98,    89,    90,   114,    50,    91,    55,
      92,    77,    78,    79,   109,    51,    59,   -71,    70,  -101,
       7,   104,   165,   167,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   107,   129,   113,
     111,   112,   130,   132,    64,   131,   115,    71,   135,   136,
      64,   185,   140,    64,   142,   143,    86,   145,    62,   150,
     158,   151,    64,    87,    88,   161,   168,   153,   155,     1,
       2,     3,   -92,    89,    90,   174,   176,    91,   156,    92,
     183,    11,   -75,    12,    13,    14,    15,    16,   177,   180,
     193,    17,   181,   182,   159,   191,   169,    18,    19,   163,
     192,   149,    64,    64,   187,     0,    21,   178,     0,     0,
     170,    23,     0,    24,   133,     0,     0,     0,     0,   186,
       0,     1,     2,     3,     0,     0,     0,     0,     0,     0,
     194,    64,    71,    11,     0,    12,    13,    14,    15,    16,
       0,     0,     0,    17,     0,     0,     0,     0,     0,    18,
      19,     0,     0,     0,     0,     1,     2,     3,    21,     0,
       0,     0,     0,    23,     0,    24,   137,    11,     0,    12,
      13,    14,    15,    16,     0,     0,     0,    17,     0,     0,
       0,     0,     0,    18,    19,     0,     0,     0,     0,     1,
       2,     3,    21,     0,     0,     0,     0,    23,     0,    24,
     164,    11,     0,    12,    13,    14,    15,    16,     0,     0,
      75,    17,    76,     0,    77,    78,    79,    18,    19,     0,
    -102,  -102,  -102,  -102,     0,     0,    21,     0,     0,     0,
       0,    23,     0,    24,   166,     1,     2,     3,     4,     0,
       5,     6,     7,     8,     9,    10,     0,    11,     0,    12,
      13,    14,    15,    16,     0,     0,     0,    17,     0,     0,
       0,     0,     0,    18,    19,     0,     0,     0,     0,    20,
       0,     0,    21,     0,     0,    22,   146,    23,     0,    24,
       1,     2,     3,     4,     0,     5,     6,     7,     8,     9,
      10,     0,    11,     0,    12,    13,    14,    15,    16,     0,
       0,     0,    17,     0,     0,     0,     0,     0,    18,    19,
       0,     0,     0,     0,    20,     0,     0,    21,     0,     0,
      22,   195,    23,     0,    24,     1,     2,     3,     4,     0,
       5,     6,     7,     8,     9,    10,     0,    11,     0,    12,
      13,    14,    15,    16,     0,     0,     0,    17,     0,     0,
       0,     0,     0,    18,    19,     0,     1,     2,     3,    20,
       0,     0,    21,     0,     0,    22,     0,    23,    11,    24,
      12,    13,    14,    15,    16,     0,     0,     0,    17,     0,
       0,     0,     0,     0,    18,    19,     0,     0,     0,     1,
       2,     3,     0,    21,     0,     0,    62,     0,    23,    63,
      24,    11,     0,    12,    13,    14,    15,    16,     0,     0,
       0,    17,     0,     0,     0,     0,     0,    18,    19,     0,
       1,     2,     3,    48,     0,     0,    21,     7,     0,     0,
       0,    23,    11,    24,    12,    13,    14,    15,    16,     0,
       0,     0,    17,     0,     0,     0,     0,     0,    18,    19,
       0,     1,     2,     3,     0,     0,     0,    21,     0,     0,
       0,     0,    23,    11,    24,    12,    13,    14,    15,    16,
       0,     0,     0,    17,     0,     0,     0,     0,     0,    18,
      19,     0,     0,    72,     0,    73,     0,     0,    21,     0,
       0,    74,    75,    23,    76,    24,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,     0,    72,     0,    73,
       0,     0,     0,     0,     0,    74,    75,   139,    76,     0,
      77,    78,    79,    80,     0,     0,    81,    82,    83,    84,
       0,    72,     0,    73,     0,     0,     0,     0,     0,    74,
      75,   157,    76,     0,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,     0,     0,    72,     0,    73,     0,
       0,     0,     0,   152,    74,    75,     0,    76,     0,    77,
      78,    79,    80,     0,     0,    81,    82,    83,    84,     0,
       0,    72,     0,    73,     0,     0,     0,     0,   154,    74,
      75,     0,    76,     0,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,    72,     0,    73,     0,     0,     0,
       0,   175,    74,    75,     0,    76,     0,    77,    78,    79,
      80,     0,     0,    81,    82,    83,    84,     0,    72,   147,
      73,     0,     0,     0,     0,     0,    74,    75,     0,    76,
       0,    77,    78,    79,    80,     0,     0,    81,    82,    83,
      84,    72,   110,    73,     0,     0,     0,     0,     0,    74,
      75,     0,    76,     0,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,    85,    72,     0,    73,     0,     0,
       0,     0,     0,    74,    75,     0,    76,     0,    77,    78,
      79,    80,     0,     0,    81,    82,    83,    84,   105,    72,
       0,    73,     0,     0,     0,     0,     0,    74,    75,     0,
      76,     0,    77,    78,    79,    80,     0,     0,    81,    82,
      83,    84,   171,    72,     0,    73,     0,     0,     0,     0,
       0,    74,    75,     0,    76,     0,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,   179,    72,     0,    73,
       0,     0,     0,     0,     0,    74,    75,     0,    76,     0,
      77,    78,    79,    80,    72,     0,    81,    82,    83,    84,
       0,     0,    74,    75,     0,    76,     0,    77,    78,    79,
      80,     0,     0,    81,    82,    83,    84,    74,    75,     0,
      76,     0,    77,    78,    79,    80,     0,     0,    81,    82,
      83,    84,  -102,    75,     0,    76,     0,    77,    78,    79,
    -102,     0,     0,    81,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
       8,    61,   160,    11,    92,     3,    27,    24,    47,    17,
      98,    47,    14,   101,    16,    23,    24,    18,    19,    17,
      22,    23,   110,    25,   182,    27,    28,    29,    30,    18,
      19,    33,    34,    35,    36,    43,    47,    41,    55,     3,
       3,    45,    40,    47,    41,    42,    48,    37,    45,    47,
      47,    27,    28,    29,    62,    37,     3,    44,     0,    37,
      10,    47,   150,   151,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    44,    86,    38,
      46,    46,     3,    91,    92,     3,    48,   108,     3,    97,
      98,   179,   100,   101,    37,    47,    24,    48,    43,    47,
      37,    47,   110,    31,    32,     3,     7,    48,    48,     3,
       4,     5,    38,    41,    42,    48,    48,    45,   139,    47,
      43,    15,    44,    17,    18,    19,    20,    21,    48,    48,
     190,    25,    48,    38,   142,    48,   157,    31,    32,   147,
      44,   113,   150,   151,   181,    -1,    40,   168,    -1,    -1,
     158,    45,    -1,    47,    48,    -1,    -1,    -1,    -1,   180,
      -1,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,    -1,
     191,   179,   193,    15,    -1,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,     3,     4,     5,    40,    -1,
      -1,    -1,    -1,    45,    -1,    47,    48,    15,    -1,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,     3,
       4,     5,    40,    -1,    -1,    -1,    -1,    45,    -1,    47,
      48,    15,    -1,    17,    18,    19,    20,    21,    -1,    -1,
      23,    25,    25,    -1,    27,    28,    29,    31,    32,    -1,
      33,    34,    35,    36,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    45,    -1,    47,    48,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    12,    13,    -1,    15,    -1,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    40,    -1,    -1,    43,    44,    45,    -1,    47,
       3,     4,     5,     6,    -1,     8,     9,    10,    11,    12,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    40,    -1,    -1,
      43,    44,    45,    -1,    47,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    12,    13,    -1,    15,    -1,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    32,    -1,     3,     4,     5,    37,
      -1,    -1,    40,    -1,    -1,    43,    -1,    45,    15,    47,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    -1,     3,
       4,     5,    -1,    40,    -1,    -1,    43,    -1,    45,    46,
      47,    15,    -1,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,
       3,     4,     5,    37,    -1,    -1,    40,    10,    -1,    -1,
      -1,    45,    15,    47,    17,    18,    19,    20,    21,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,
      -1,     3,     4,     5,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    45,    15,    47,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,
      32,    -1,    -1,    14,    -1,    16,    -1,    -1,    40,    -1,
      -1,    22,    23,    45,    25,    47,    27,    28,    29,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    14,    -1,    16,
      -1,    -1,    -1,    -1,    -1,    22,    23,    48,    25,    -1,
      27,    28,    29,    30,    -1,    -1,    33,    34,    35,    36,
      -1,    14,    -1,    16,    -1,    -1,    -1,    -1,    -1,    22,
      23,    48,    25,    -1,    27,    28,    29,    30,    -1,    -1,
      33,    34,    35,    36,    -1,    -1,    14,    -1,    16,    -1,
      -1,    -1,    -1,    46,    22,    23,    -1,    25,    -1,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    -1,
      -1,    14,    -1,    16,    -1,    -1,    -1,    -1,    46,    22,
      23,    -1,    25,    -1,    27,    28,    29,    30,    -1,    -1,
      33,    34,    35,    36,    14,    -1,    16,    -1,    -1,    -1,
      -1,    44,    22,    23,    -1,    25,    -1,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    14,    39,
      16,    -1,    -1,    -1,    -1,    -1,    22,    23,    -1,    25,
      -1,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    14,    38,    16,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    25,    -1,    27,    28,    29,    30,    -1,    -1,
      33,    34,    35,    36,    37,    14,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,
      29,    30,    -1,    -1,    33,    34,    35,    36,    37,    14,
      -1,    16,    -1,    -1,    -1,    -1,    -1,    22,    23,    -1,
      25,    -1,    27,    28,    29,    30,    -1,    -1,    33,    34,
      35,    36,    37,    14,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    22,    23,    -1,    25,    -1,    27,    28,    29,    30,
      -1,    -1,    33,    34,    35,    36,    37,    14,    -1,    16,
      -1,    -1,    -1,    -1,    -1,    22,    23,    -1,    25,    -1,
      27,    28,    29,    30,    14,    -1,    33,    34,    35,    36,
      -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    22,    23,    -1,
      25,    -1,    27,    28,    29,    30,    -1,    -1,    33,    34,
      35,    36,    22,    23,    -1,    25,    -1,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      13,    15,    17,    18,    19,    20,    21,    25,    31,    32,
      37,    40,    43,    45,    47,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    64,    67,    73,    78,    81,
      82,    84,    87,    47,    47,    47,     3,    76,    37,    53,
      37,    37,    53,     3,    53,    47,    57,    59,    57,     3,
      68,    69,    43,    46,    53,    63,    65,    66,    53,    73,
       0,    51,    14,    16,    22,    23,    25,    27,    28,    29,
      30,    33,    34,    35,    36,    37,    24,    31,    32,    41,
      42,    45,    47,    60,    61,    62,    41,    45,    47,    53,
      83,    85,    86,    74,    47,    37,    73,    44,    52,    53,
      38,    46,    46,    38,    48,    48,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
       3,     3,    53,    48,    63,     3,    53,    48,    63,    48,
      53,    63,    37,    47,    77,    48,    44,    39,    63,    65,
      47,    47,    46,    48,    46,    48,    51,    48,    37,    53,
      75,     3,    79,    53,    48,    63,    48,    63,     7,    51,
      53,    37,    79,    80,    48,    44,    48,    48,    51,    37,
      48,    48,    38,    43,    70,    63,    51,    70,    79,    71,
      72,    48,    44,    52,    51,    44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    56,
      56,    56,    56,    56,    57,    57,    57,    57,    58,    58,
      58,    58,    59,    59,    59,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    63,    64,    64,    64,    65,    65,
      66,    68,    67,    69,    67,    71,    70,    72,    70,    74,
      75,    73,    76,    77,    73,    78,    78,    78,    78,    78,
      78,    79,    80,    79,    79,    81,    81,    83,    82,    85,
      84,    86,    84,    87,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     2,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       3,     4,     4,     2,     6,     5,     3,     1,     1,     3,
       2,     5,     4,     1,     3,     3,     3,     2,     1,     3,
       5,     0,     3,     0,     4,     0,     3,     0,     4,     0,
       0,     8,     0,     0,     7,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     7,     5,     0,     6,     0,
      10,     0,     8,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 51 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Program");}
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 52 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Statement");}
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 53 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Statement");}
#line 1608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 54 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Statement");}
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 55 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Statement");}
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 56 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Statement");}
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 57 "parser.y" /* yacc.c:1646  */
    {      {print_to_stream("Statement");}  
                                   if(iam_in_loop==0)
                                    {
                                        print_error(NULL,yylineno, "ERROR : use BREAK not in a loop");
                                    } 
                                    
        
                            }
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 65 "parser.y" /* yacc.c:1646  */
    {     {print_to_stream("Statement");}  
                                    if(iam_in_loop==0)
                                    {
                                       print_error(NULL,yylineno, "ERROR : use CONTINUE not in a loop");
                                    } 
                                    
                            }
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 72 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Statement");}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 73 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Statement");}
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 74 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Statement");}
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 79 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Expression");}
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 80 "parser.y" /* yacc.c:1646  */
    {print_to_stream("+ expression");}
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 81 "parser.y" /* yacc.c:1646  */
    {print_to_stream("- expression");}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 82 "parser.y" /* yacc.c:1646  */
    {print_to_stream("* expression");}
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 83 "parser.y" /* yacc.c:1646  */
    {print_to_stream("/ expression");}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 84 "parser.y" /* yacc.c:1646  */
    {print_to_stream("% expression");}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 85 "parser.y" /* yacc.c:1646  */
    {print_to_stream("> expression");}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 86 "parser.y" /* yacc.c:1646  */
    {print_to_stream(">= expression");}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 87 "parser.y" /* yacc.c:1646  */
    {print_to_stream("< expression");}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 88 "parser.y" /* yacc.c:1646  */
    {print_to_stream("<= expression");}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 89 "parser.y" /* yacc.c:1646  */
    {print_to_stream("== expression");}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 90 "parser.y" /* yacc.c:1646  */
    {print_to_stream("!= expression");}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 91 "parser.y" /* yacc.c:1646  */
    {print_to_stream("and expression");}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 92 "parser.y" /* yacc.c:1646  */
    {print_to_stream("or expression");}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 93 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Expression");}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 97 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Term");}
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 98 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Term");}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 101 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Term");}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 104 "parser.y" /* yacc.c:1646  */
    {               {print_to_stream("Term");}
                                          process_plus_plus(symbolTable, scope, yylineno,
                                        iam_in_function, &functions_stack, &(yyvsp[0].exprNode));
                                           
                                            
                            }
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 110 "parser.y" /* yacc.c:1646  */
    {                {print_to_stream("Term");}
                                            process_plus_plus(symbolTable, scope, yylineno,
                                        iam_in_function, &functions_stack, &(yyvsp[-1].exprNode));
                            }
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 114 "parser.y" /* yacc.c:1646  */
    {              {print_to_stream("Term");
                                          process_minus_minus(symbolTable, scope, yylineno,
                                        iam_in_function, &functions_stack, &(yyvsp[0].exprNode));
                                        }
                                          
        }
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 120 "parser.y" /* yacc.c:1646  */
    {               print_to_stream("Term");
                                                process_minus_minus(symbolTable, scope, yylineno,
                                                iam_in_function, &functions_stack, &(yyvsp[-1].exprNode));}
#line 1816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 125 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Term");}
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 127 "parser.y" /* yacc.c:1646  */
    { 
                                        print_to_stream("Assign expression");
                                         
                                        process_assign(symbolTable, scope, yylineno,
                                        iam_in_function, &functions_stack, &(yyvsp[-2].exprNode));
                                    }
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 137 "parser.y" /* yacc.c:1646  */
    { print_to_stream("Primary");  process_primary(symbolTable, scope, yylineno,iam_in_function, &functions_stack, &(yyvsp[0].exprNode));   }
#line 1839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 138 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Primary");}
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 139 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Primary");}
#line 1851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 140 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Primary");}
#line 1857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 141 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Primary");}
#line 1863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 143 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Lvalue"); process_id(symbolTable,scope,yylineno,(yyvsp[0].str),iam_in_function,&functions_stack,&(yyval.exprNode)); }
#line 1869 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 144 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Lvalue"); process_local_id(symbolTable,  scope,  yylineno, (yyvsp[0].str),  iam_in_function,  &(yyval.exprNode));}
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 145 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Lvalue"); process_double_colon_id(symbolTable,(yyvsp[0].str),yylineno,&(yyval.exprNode)); }
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 146 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Lvalue"); (yyval.exprNode)=NULL;}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 148 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Member");}
#line 1893 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 149 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Member");}
#line 1899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 150 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Member");}
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 151 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Member");}
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 153 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Call");}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 154 "parser.y" /* yacc.c:1646  */
    { print_to_stream("Call");
                process_callsuffix(symbolTable, scope,  yylineno,  iam_in_function, 
                &functions_stack, &(yyvsp[-1].exprNode));

                                }
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 159 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Call");}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 160 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Call");}
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 163 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Call Suffix");}
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 164 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Call Suffix");}
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 166 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Normal Call");}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 167 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Normal Call");}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 168 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Method Call");}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 169 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Method Call");}
#line 1975 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 170 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Expression List");}
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 171 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Expression List");}
#line 1987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 174 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Object Definition");}
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 175 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Object Definition");}
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 176 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Object Definition");}
#line 2005 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 178 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Indexed");}
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 179 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Indexed");}
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 182 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Index Element");}
#line 2023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 184 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 2029 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 184 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Block"); symbolTable_hide(symbolTable, scope); scope--;}
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 185 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 2041 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 185 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Block"); symbolTable_hide(symbolTable, scope); scope--;}
#line 2047 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 187 "parser.y" /* yacc.c:1646  */
    {iam_in_function++;}
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 187 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Function Block");  symbolTable_hide(symbolTable, scope); scope--; iam_in_function--; 
        pop(&functions_stack);}
#line 2060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 189 "parser.y" /* yacc.c:1646  */
    {iam_in_function++;}
#line 2066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 189 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Function Block");  symbolTable_hide(symbolTable, scope); scope--;  iam_in_function--;
     pop(&functions_stack);  }
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 193 "parser.y" /* yacc.c:1646  */
    { process_function_id(symbolTable,  scope,  yylineno, (yyvsp[0].str),  &iam_in_function, &functions_stack  );

                        }
#line 2081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 195 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 2087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 195 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Function Definition");}
#line 2093 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 197 "parser.y" /* yacc.c:1646  */
    {   process_anonymous_function(symbolTable,  scope,  yylineno, &functions_stack); 

                            }
#line 2101 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 200 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 2107 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 200 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Function Definition");}
#line 2113 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 203 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Integer");}
#line 2119 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 204 "parser.y" /* yacc.c:1646  */
    {print_to_stream("Float");}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 205 "parser.y" /* yacc.c:1646  */
    {print_to_stream("String");}
#line 2131 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 206 "parser.y" /* yacc.c:1646  */
    {print_to_stream("NIL");}
#line 2137 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 207 "parser.y" /* yacc.c:1646  */
    {print_to_stream("TRUE");}
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 208 "parser.y" /* yacc.c:1646  */
    {print_to_stream("FALSE");}
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 210 "parser.y" /* yacc.c:1646  */
    { print_to_stream("ID List");  process_function_arguments(symbolTable,scope,yylineno,(yyvsp[0].str));                     

                                           
            }
#line 2158 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 214 "parser.y" /* yacc.c:1646  */
    { process_function_arguments(symbolTable,scope,yylineno,(yyvsp[0].str)); 
            }
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 215 "parser.y" /* yacc.c:1646  */
    {print_to_stream("ID List");}
#line 2171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 217 "parser.y" /* yacc.c:1646  */
    {print_to_stream("ID List");}
#line 2177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 219 "parser.y" /* yacc.c:1646  */
    {print_to_stream("If Statement");}
#line 2183 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 220 "parser.y" /* yacc.c:1646  */
    {print_to_stream("If Statement");}
#line 2189 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 221 "parser.y" /* yacc.c:1646  */
    {iam_in_loop++;}
#line 2195 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 221 "parser.y" /* yacc.c:1646  */
    {print_to_stream("While Statement"); iam_in_loop--;}
#line 2201 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 223 "parser.y" /* yacc.c:1646  */
    {iam_in_loop++;}
#line 2207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 223 "parser.y" /* yacc.c:1646  */
    { print_to_stream("For Statement"); iam_in_loop--;}
#line 2213 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 224 "parser.y" /* yacc.c:1646  */
    {iam_in_loop++;}
#line 2219 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 224 "parser.y" /* yacc.c:1646  */
    {print_to_stream("For Statement"); iam_in_loop--;}
#line 2225 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 227 "parser.y" /* yacc.c:1646  */
    {   print_to_stream("Return Statement");
                                    if(iam_in_function==0)
                                    {
                                       print_error(NULL,yylineno, "ERROR : return out of function");
                                    } 
                                    
                                 }
#line 2237 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 235 "parser.y" /* yacc.c:1646  */
    {    print_to_stream("Return Statement");
                                        if(iam_in_function==0)
                                        {
                                           print_error(NULL,yylineno, "ERROR : return out of function");
                                        } 
                                        
                                        
                                     }
#line 2250 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2254 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 245 "parser.y" /* yacc.c:1906  */


int yyerror( char * msg )
{
    print_Red();
    fprintf(stderr ,"%s in line : %d \n", msg,yylineno);
    reset_Red();

}
int main(int argc , char * argv[])
{
    if(argc==2)
    {
        if(!( yyin=fopen(argv[1],"r") )  )
        {
            fprintf(stderr,"Error: can't read file\n");
            return -1;
        }   
        output_file=stdout;
        
    }
    else if (argc>2)
    {
        if(!( yyin=fopen(argv[1],"r") )  )
        {
            fprintf(stderr,"Error: can't read file\n");
            return -1;
        } 
        output_file=fopen(argv[2],"w");
        if(output_file==NULL)
        {
            fprintf(stderr,"Error: can't open write file\n");
            return -1;
        }
    }
    else
    {
        output_file=stdout;
        yyin=stdin;
    }
  
    symbolTable = symbolTable_create();
    //yylex();
    //yyin=stdin;
    yyparse() ;
    //symbolTable_print(symbolTable);
    //symbolTable_print_scope_list(symbolTable, 1);
    symbolTable_print_scopes(symbolTable,100);
    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}


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

#include"symbolTable.h"
#include <stdio.h>
#include "lib.h"
extern FILE * yyin;
extern int yylineno; 
int func_line=0;
SymbolTable *  symbolTable;
FILE *output_file;
int yylex(void);
short is_local_id=0;
int yyerror( char * msg );
unsigned int  scope=0;


#line 82 "y.tab.c" /* yacc.c:339  */

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
    NUMBER = 258,
    ID = 259,
    IF = 260,
    ELSE = 261,
    WHILE = 262,
    FOR = 263,
    FUNCTION = 264,
    RETURN = 265,
    BREAK = 266,
    CONTINUE = 267,
    AND = 268,
    NOT = 269,
    OR = 270,
    LOCALL = 271,
    TRUE = 272,
    FALSE = 273,
    NIL = 274,
    STRING = 275,
    EQUALS = 276,
    PLUS = 277,
    ASSIGN = 278,
    MINUS = 279,
    UMINUS = 280,
    ASTERISK = 281,
    DIVISION = 282,
    PERCENT = 283,
    DIFFERENT = 284,
    PLUS_PLUS = 285,
    MINUS_MINUS = 286,
    GREATER = 287,
    LESS = 288,
    GREATER_EQUALS = 289,
    LESS_EQUALS = 290,
    SEMICOLON = 291,
    COMMA = 292,
    COLON = 293,
    DOUBLE_COLON = 294,
    DOT = 295,
    Diaeresis = 296,
    LEFT_BRACE = 297,
    RIGHT_BRACE = 298,
    LEFT_SQUARE = 299,
    RIGHT_SQUARE = 300,
    LEFT_BRACKETS = 301,
    RIGHT_BRACKETS = 302
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define ID 259
#define IF 260
#define ELSE 261
#define WHILE 262
#define FOR 263
#define FUNCTION 264
#define RETURN 265
#define BREAK 266
#define CONTINUE 267
#define AND 268
#define NOT 269
#define OR 270
#define LOCALL 271
#define TRUE 272
#define FALSE 273
#define NIL 274
#define STRING 275
#define EQUALS 276
#define PLUS 277
#define ASSIGN 278
#define MINUS 279
#define UMINUS 280
#define ASTERISK 281
#define DIVISION 282
#define PERCENT 283
#define DIFFERENT 284
#define PLUS_PLUS 285
#define MINUS_MINUS 286
#define GREATER 287
#define LESS 288
#define GREATER_EQUALS 289
#define LESS_EQUALS 290
#define SEMICOLON 291
#define COMMA 292
#define COLON 293
#define DOUBLE_COLON 294
#define DOT 295
#define Diaeresis 296
#define LEFT_BRACE 297
#define RIGHT_BRACE 298
#define LEFT_SQUARE 299
#define RIGHT_SQUARE 300
#define LEFT_BRACKETS 301
#define RIGHT_BRACKETS 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "parser.y" /* yacc.c:355  */

    
	float num;
    //float real;
	char * str;

#line 223 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 240 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   722

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  184

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

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
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    47,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    59,    60,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      80,    81,    82,    83,    84,    85,    86,    87,    89,    89,
     103,   104,   105,   106,   107,   109,   169,   196,   203,   205,
     206,   207,   208,   210,   211,   212,   214,   215,   217,   219,
     221,   222,   223,   225,   226,   227,   229,   230,   231,   233,
     235,   235,   236,   236,   238,   239,   242,   275,   275,   242,
     282,   288,   288,   282,   294,   294,   294,   294,   294,   296,
     317,   317,   337,   339,   340,   341,   343,   345,   346
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "ID", "IF", "ELSE", "WHILE",
  "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR",
  "LOCALL", "TRUE", "FALSE", "NIL", "STRING", "EQUALS", "PLUS", "ASSIGN",
  "MINUS", "UMINUS", "ASTERISK", "DIVISION", "PERCENT", "DIFFERENT",
  "PLUS_PLUS", "MINUS_MINUS", "GREATER", "LESS", "GREATER_EQUALS",
  "LESS_EQUALS", "SEMICOLON", "COMMA", "COLON", "DOUBLE_COLON", "DOT",
  "Diaeresis", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_SQUARE", "RIGHT_SQUARE",
  "LEFT_BRACKETS", "RIGHT_BRACKETS", "$accept", "program", "stmt",
  "statements", "expr", "term", "assignexpr", "$@1", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "objectdef", "indexed", "indexedelem", "block", "$@2", "$@3",
  "block_func", "funcdef", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9",
  "const", "idlist", "$@10", "ifstmt", "whilestmt", "forstmt",
  "returnstmt", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

#define YYPACT_NINF -142

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-142)))

#define YYTABLE_NINF -91

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-91)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     245,  -142,  -142,   -40,   -38,   -36,     9,   309,   -14,    -7,
     358,    38,  -142,  -142,  -142,  -142,   358,    47,    47,  -142,
      41,     6,   276,   340,    57,  -142,   245,   571,  -142,  -142,
    -142,    58,  -142,     4,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,   358,   358,   358,  -142,    15,  -142,   595,  -142,
    -142,  -142,  -142,  -142,    55,   -37,     4,   -37,  -142,    22,
     245,   358,  -142,   548,    34,    37,    46,   379,    43,  -142,
    -142,   358,   358,   358,   358,   358,   358,   358,   358,   358,
     358,   358,   358,   358,  -142,  -142,  -142,    96,    97,   358,
     358,    83,  -142,  -142,  -142,   103,   358,   358,   403,   427,
      75,    66,  -142,  -142,    67,  -142,    16,   524,   358,  -142,
    -142,    71,  -142,    74,   658,    95,   673,    69,    69,  -142,
    -142,  -142,   673,   687,   687,   687,   687,  -142,    79,   451,
      68,   358,  -142,   476,    84,   245,   245,   358,  -142,   129,
      74,  -142,   358,  -142,  -142,   358,   358,  -142,  -142,   643,
    -142,  -142,   128,  -142,   619,   129,    99,  -142,   501,    91,
      92,   245,   358,  -142,   107,    98,  -142,  -142,  -142,  -142,
     100,   102,   129,   104,   245,   104,  -142,   157,  -142,  -142,
    -142,  -142,   201,  -142
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    84,    45,     0,     0,     0,    80,     0,     0,     0,
       0,     0,    87,    88,    86,    85,     0,     0,     0,    12,
       0,    72,     0,     0,     0,    14,     2,     0,    29,    15,
      37,    40,    48,    41,    42,    10,    11,    44,     4,     5,
       6,     7,     0,     0,    62,    76,     0,    98,     0,     8,
       9,    32,    46,    31,     0,    33,     0,    35,    47,     0,
       0,     0,    65,    60,     0,     0,    66,     0,     0,     1,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,    34,    36,     0,     0,     0,
      62,     0,    54,    56,    57,     0,     0,    62,     0,     0,
       0,     0,    81,    97,     0,    71,     0,     0,    62,    63,
      64,    68,    30,    43,    27,    28,    25,    16,    17,    18,
      19,    20,    26,    21,    23,    22,    24,    49,     0,     0,
       0,     0,    51,     0,     0,     0,     0,     0,    77,    92,
       0,    73,     0,    61,    67,    62,    62,    50,    58,    39,
      52,    53,    94,    95,     0,    92,    89,    82,     0,     0,
       0,     0,    62,    78,     0,     0,    69,    55,    59,    93,
       0,     0,    92,     0,     0,     0,    91,     0,    83,    96,
      79,    74,     0,    75
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,   -26,   -59,    -5,  -142,  -142,  -142,  -142,    -2,
    -142,    36,  -142,  -142,  -142,    -3,  -142,    39,  -142,  -142,
    -142,  -142,   -24,   -11,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -141,  -142,  -142,  -142,  -142,  -142
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    27,    28,    29,    91,    30,    31,
      32,    33,    92,    93,    94,    64,    34,    65,    66,    35,
      59,    60,   178,    36,   101,   155,   171,    46,   139,   165,
      37,   157,   164,    38,    39,    40,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   106,    48,    87,    88,    51,    42,    89,    43,    90,
      44,    53,    68,    45,   163,    55,    57,    63,    67,     1,
       2,     3,    49,     4,     5,     6,     7,     8,     9,    50,
      10,   176,    11,    12,    13,    14,    15,    98,    99,    63,
      16,   100,    52,   104,    95,    58,    17,    18,    96,   -70,
      97,     2,    19,    56,    56,    20,   107,    69,    21,   141,
      22,   102,    23,    11,     6,   105,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   109,
      70,   -38,   110,   111,   129,    63,    20,   130,    85,    86,
     113,   133,    63,    54,   134,    76,    77,    78,    87,    88,
     127,   128,    89,    63,    90,   143,   131,   132,    71,   152,
     153,   137,   138,    61,   140,   148,    73,    74,   182,    75,
     145,    76,    77,    78,    79,   146,   149,    80,    81,    82,
      83,   151,   154,   156,   161,   169,   -90,   158,   167,   168,
      63,    63,   159,   160,   172,   173,   177,   174,   179,   175,
     144,   180,     0,     0,     0,     0,    70,    63,     0,   170,
       1,     2,     3,     0,     4,     5,     6,     7,     8,     9,
       0,    10,     0,    11,    12,    13,    14,    15,     0,     0,
       0,    16,     0,     0,     0,     0,     0,    17,    18,     0,
       0,     0,     0,    19,     0,     0,    20,     0,     0,    21,
     181,    22,     0,    23,     1,     2,     3,     0,     4,     5,
       6,     7,     8,     9,     0,    10,     0,    11,    12,    13,
      14,    15,     0,     0,     0,    16,     0,     0,     0,     0,
       0,    17,    18,     0,     0,     0,     0,    19,     0,     0,
      20,     0,     0,    21,   183,    22,     0,    23,     1,     2,
       3,     0,     4,     5,     6,     7,     8,     9,     0,    10,
       0,    11,    12,    13,    14,    15,     0,     0,     0,    16,
       0,     0,     0,     0,     0,    17,    18,     0,     0,     1,
       2,    19,     0,     0,    20,     0,     0,    21,     0,    22,
      10,    23,    11,    12,    13,    14,    15,     0,     0,     0,
      16,     0,     0,     0,     0,     0,    17,    18,     0,     0,
       0,     0,     1,     2,     0,    20,     0,     0,    61,     0,
      22,    62,    23,    10,     0,    11,    12,    13,    14,    15,
       0,     0,     0,    16,     0,     0,     0,     0,     0,    17,
      18,     0,     0,     1,     2,    47,     0,     0,    20,     6,
       0,     0,     0,    22,    10,    23,    11,    12,    13,    14,
      15,     1,     2,     0,    16,     0,     0,     0,     0,     0,
      17,    18,    10,     0,    11,    12,    13,    14,    15,    20,
       0,     0,    16,     0,    22,     0,    23,     0,    17,    18,
       0,     0,    71,     0,    72,     0,     0,    20,     0,     0,
      73,    74,    22,    75,    23,    76,    77,    78,    79,     0,
       0,    80,    81,    82,    83,     0,    71,     0,    72,     0,
       0,     0,     0,     0,    73,    74,   112,    75,     0,    76,
      77,    78,    79,     0,     0,    80,    81,    82,    83,     0,
      71,     0,    72,     0,     0,     0,     0,     0,    73,    74,
     135,    75,     0,    76,    77,    78,    79,     0,     0,    80,
      81,    82,    83,     0,    71,     0,    72,     0,     0,     0,
       0,     0,    73,    74,   136,    75,     0,    76,    77,    78,
      79,     0,     0,    80,    81,    82,    83,     0,     0,    71,
       0,    72,     0,     0,     0,     0,   147,    73,    74,     0,
      75,     0,    76,    77,    78,    79,     0,     0,    80,    81,
      82,    83,     0,     0,    71,     0,    72,     0,     0,     0,
       0,   150,    73,    74,     0,    75,     0,    76,    77,    78,
      79,     0,     0,    80,    81,    82,    83,    71,     0,    72,
       0,     0,     0,     0,   166,    73,    74,     0,    75,     0,
      76,    77,    78,    79,     0,     0,    80,    81,    82,    83,
       0,    71,   142,    72,     0,     0,     0,     0,     0,    73,
      74,     0,    75,     0,    76,    77,    78,    79,     0,     0,
      80,    81,    82,    83,    71,   108,    72,     0,     0,     0,
       0,     0,    73,    74,     0,    75,     0,    76,    77,    78,
      79,     0,     0,    80,    81,    82,    83,    84,    71,     0,
      72,     0,     0,     0,     0,     0,    73,    74,     0,    75,
       0,    76,    77,    78,    79,     0,     0,    80,    81,    82,
      83,   103,    71,     0,    72,     0,     0,     0,     0,     0,
      73,    74,     0,    75,     0,    76,    77,    78,    79,     0,
       0,    80,    81,    82,    83,   162,    71,     0,    72,     0,
       0,     0,     0,     0,    73,    74,     0,    75,     0,    76,
      77,    78,    79,     0,     0,    80,    81,    82,    83,    73,
      74,     0,    75,     0,    76,    77,    78,    79,     0,     0,
      80,    81,    82,    83,   -91,    74,     0,    75,     0,    76,
      77,    78,   -91,     0,     0,    80,    81,    82,    83,    74,
       0,    75,     0,    76,    77,    78,     0,     0,     0,   -91,
     -91,   -91,   -91
};

static const yytype_int16 yycheck[] =
{
      26,    60,     7,    40,    41,    10,    46,    44,    46,    46,
      46,    16,    23,     4,   155,    17,    18,    22,    23,     3,
       4,     5,    36,     7,     8,     9,    10,    11,    12,    36,
      14,   172,    16,    17,    18,    19,    20,    42,    43,    44,
      24,    44,     4,    54,    40,     4,    30,    31,    44,    43,
      46,     4,    36,    17,    18,    39,    61,     0,    42,    43,
      44,    46,    46,    16,     9,    43,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    45,
     106,    23,    45,    37,    89,    90,    39,    90,    30,    31,
      47,    96,    97,    46,    97,    26,    27,    28,    40,    41,
       4,     4,    44,   108,    46,   108,    23,     4,    13,   135,
     136,    36,    46,    42,    47,    47,    21,    22,   177,    24,
      46,    26,    27,    28,    29,    46,   131,    32,    33,    34,
      35,    47,   137,     4,     6,   161,    37,   142,    47,    47,
     145,   146,   145,   146,    37,    47,    42,    47,   174,    47,
     111,   175,    -1,    -1,    -1,    -1,   182,   162,    -1,   162,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    39,    -1,    -1,    42,
      43,    44,    -1,    46,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      39,    -1,    -1,    42,    43,    44,    -1,    46,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,     3,
       4,    36,    -1,    -1,    39,    -1,    -1,    42,    -1,    44,
      14,    46,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,
      -1,    -1,     3,     4,    -1,    39,    -1,    -1,    42,    -1,
      44,    45,    46,    14,    -1,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    -1,     3,     4,    36,    -1,    -1,    39,     9,
      -1,    -1,    -1,    44,    14,    46,    16,    17,    18,    19,
      20,     3,     4,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    14,    -1,    16,    17,    18,    19,    20,    39,
      -1,    -1,    24,    -1,    44,    -1,    46,    -1,    30,    31,
      -1,    -1,    13,    -1,    15,    -1,    -1,    39,    -1,    -1,
      21,    22,    44,    24,    46,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    -1,    13,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    21,    22,    47,    24,    -1,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    -1,
      13,    -1,    15,    -1,    -1,    -1,    -1,    -1,    21,    22,
      47,    24,    -1,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    -1,    13,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    21,    22,    47,    24,    -1,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    -1,    -1,    13,
      -1,    15,    -1,    -1,    -1,    -1,    45,    21,    22,    -1,
      24,    -1,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,    -1,    -1,    13,    -1,    15,    -1,    -1,    -1,
      -1,    45,    21,    22,    -1,    24,    -1,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    13,    -1,    15,
      -1,    -1,    -1,    -1,    43,    21,    22,    -1,    24,    -1,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      -1,    13,    38,    15,    -1,    -1,    -1,    -1,    -1,    21,
      22,    -1,    24,    -1,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    13,    37,    15,    -1,    -1,    -1,
      -1,    -1,    21,    22,    -1,    24,    -1,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    36,    13,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    21,    22,    -1,    24,
      -1,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    36,    13,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      21,    22,    -1,    24,    -1,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    36,    13,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    21,    22,    -1,    24,    -1,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    21,
      22,    -1,    24,    -1,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    21,    22,    -1,    24,    -1,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    22,
      -1,    24,    -1,    26,    27,    28,    -1,    -1,    -1,    32,
      33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    11,    12,
      14,    16,    17,    18,    19,    20,    24,    30,    31,    36,
      39,    42,    44,    46,    49,    50,    51,    52,    53,    54,
      56,    57,    58,    59,    64,    67,    71,    78,    81,    82,
      83,    84,    46,    46,    46,     4,    75,    36,    52,    36,
      36,    52,     4,    52,    46,    57,    59,    57,     4,    68,
      69,    42,    45,    52,    63,    65,    66,    52,    71,     0,
      50,    13,    15,    21,    22,    24,    26,    27,    28,    29,
      32,    33,    34,    35,    36,    30,    31,    40,    41,    44,
      46,    55,    60,    61,    62,    40,    44,    46,    52,    52,
      63,    72,    46,    36,    71,    43,    51,    52,    37,    45,
      45,    37,    47,    47,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,     4,     4,    52,
      63,    23,     4,    52,    63,    47,    47,    36,    46,    76,
      47,    43,    38,    63,    65,    46,    46,    45,    47,    52,
      45,    47,    50,    50,    52,    73,     4,    79,    52,    63,
      63,     6,    36,    79,    80,    77,    43,    47,    47,    50,
      63,    74,    37,    47,    47,    47,    79,    42,    70,    50,
      70,    43,    51,    43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    53,    53,    53,    53,    53,    53,    53,    55,    54,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    58,
      58,    58,    58,    59,    59,    59,    60,    60,    61,    62,
      63,    63,    63,    64,    64,    64,    65,    65,    65,    66,
      68,    67,    69,    67,    70,    70,    72,    73,    74,    71,
      75,    76,    77,    71,    78,    78,    78,    78,    78,    79,
      80,    79,    79,    81,    81,    82,    83,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     2,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     0,     4,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       1,     3,     0,     3,     3,     2,     1,     3,     0,     5,
       0,     3,     0,     4,     2,     3,     0,     0,     0,     9,
       0,     0,     0,     8,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     7,     5,     5,     9,     3,     2
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
        case 3:
#line 48 "parser.y" /* yacc.c:1646  */
    {}
#line 1557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 89 "parser.y" /* yacc.c:1646  */
    {               
                                    short status = symbolTable_lookup_exists(symbolTable,scope,yylval.str);
                                    if(status == ERROR_FUNC) {
                                         if(is_local_id){
                                           print_Red();
                                           fprintf(stderr, "error assign to function in line %d\n",yylineno);
                                           reset_Red();
                                         }
                                    }
                                    }
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 98 "parser.y" /* yacc.c:1646  */
    {is_local_id=0;}
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 109 "parser.y" /* yacc.c:1646  */
    {
                                     fprintf(stderr, "ID \n");  
                                    SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                  
                                    var = create_var((yyvsp[0].str),scope,yylineno);
                                    if(scope!=0) bucket=create_bucket_var( 1 ,  var  ,LOCAL );
                                    else bucket=create_bucket_var( 1 ,  var  ,GLOBAL );
                                
                                    if(symbolTable_lookup_exists(symbolTable,scope,(char * )(yyvsp[0].str))==0)
                                    {

                                            symbolTable_insert(symbolTable ,bucket );   
                                    }
                                    else
                                    {
                                        /*if (symbolTable_lookup_exists_exact_scope(symbolTable,0,$1)==0  && symbolTable_lookup_function(symbolTable , scope-1) 
                                        && symbolTable_lookup_exists_exact_scope(symbolTable,scope,$1)==0  )*/
                                        unsigned int tmp_scope=1,func_scope=-1,id_scope;
                                        short  is_function_blocking=1;
                                        while(tmp_scope<scope)
                                        {
                                            if (symbolTable_lookup_function(symbolTable , tmp_scope) )
                                            {
                                                func_scope=tmp_scope;

                                            }
                                            tmp_scope++;
                                        }
                                        //fprintf(stderr, "fun scope : %d\n",func_scope);
                                        if(func_scope==-1) is_function_blocking=0;
                                        else
                                        {
                                            id_scope =find_bucket_scope(symbolTable,(yyvsp[0].str));
                                            //fprintf(stderr, "id scope : %d\n",id_scope);

                                            if(id_scope==-1) { fprintf(stderr,"lalalala\n"); is_function_blocking=1;}
                                            else if(id_scope <= func_scope) {is_function_blocking=1;}
                                            else is_function_blocking=0;
                                        }   


                                        if (symbolTable_lookup_exists_exact_scope(symbolTable,0,(yyvsp[0].str))==0 || symbolTable_lookup_exists_exact_scope(symbolTable,0,(yyvsp[0].str))==ERROR_FUNC
                                         && is_function_blocking )
                                        {
                                                if ( !is_library_func(symbolTable,(yyvsp[0].str)) )
                                                {
                                                    print_Red(); 
                                                    fprintf(stderr,"error no access to this variable  %s in line :%d \n",(yyvsp[0].str),yylineno); 
                                                    reset_Red();

                                                }
                                        }
                                        //eisai prosbasimos?
                                        
                                    }

                                
                                
                                }
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 169 "parser.y" /* yacc.c:1646  */
    {  
                                    short is_local_id=1;
                                    
                                    SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    //printf("%s\n",$2);               

                                    var = create_var((yyvsp[0].str),scope,yylineno);
                                    if(scope!=0) bucket=create_bucket_var( 1 ,  var  ,LOCAL );
                                    else bucket=create_bucket_var( 1 ,  var  ,GLOBAL );
                                    if (symbolTable_lookup_exists_exact_scope(symbolTable,  scope,(const char*)(yyvsp[0].str))==0    )                               
                                    {
                                        if(is_library_func(symbolTable,(const char*)(yyvsp[0].str)) ) 
                                        {
                                            print_Red(); fprintf(stderr,"error conflict with library function in line :%d \n",yylineno); reset_Red();
                                        }
                                        else
                                        {
                                            symbolTable_insert(symbolTable, bucket);

                                        }
                                    }
                                   
                                        //error 


                                }
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 196 "parser.y" /* yacc.c:1646  */
    {   
                                    if(symbolTable_lookup_exists_exact_scope(symbolTable,0,(char*)(yyvsp[0].str))==0 ) {
                                    print_Red(); 
                                    fprintf(stderr,"global variable doesnt exist in line %u \n",yylineno); 
                                    reset_Red();
                                    }
                                }
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 211 "parser.y" /* yacc.c:1646  */
    {   fprintf(stderr, "lvalue call suffix \n");              }
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 235 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 235 "parser.y" /* yacc.c:1646  */
    {symbolTable_hide(symbolTable, scope); scope--;}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 236 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 236 "parser.y" /* yacc.c:1646  */
    {symbolTable_hide(symbolTable, scope); scope--;}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 238 "parser.y" /* yacc.c:1646  */
    {symbolTable_hide(symbolTable, scope); scope--;}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 239 "parser.y" /* yacc.c:1646  */
    {symbolTable_hide(symbolTable, scope); scope--;}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 242 "parser.y" /* yacc.c:1646  */
    {
                            Function * func;
                            SymbolTableEntry * bucket;
                            func=create_func((yyvsp[0].str) , scope , yylineno);
                            bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                            short status = symbolTable_lookup_exists_exact_scope(symbolTable,scope,(yyvsp[0].str));
                            if(is_library_func(symbolTable,(yyvsp[0].str)))
                            {
                                    print_Red(); 
                                    fprintf(stderr,"error:formal shadows libfunc in line : %d\n",yylineno); 
                                    reset_Red();
                            }
                            else if (status==ERROR_FUNC )
                            {
                                    print_Red(); 
                                    fprintf(stderr,"error:function %s exists line : %d\n",(yyvsp[0].str),yylineno); 
                                    reset_Red();
                            }
                            else if(status==ERROR_VAR)
                            {
                                print_Red(); 
                                fprintf(stderr,"%s is variable line : %d \n",(yyvsp[0].str) ,yylineno); 
                                reset_Red();

                            }
                            else 
                            {
                                //fprintf(stderr,"staus : %d\n",status);
                                symbolTable_insert(symbolTable, bucket);
                            }
                            


                        }
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 275 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 275 "parser.y" /* yacc.c:1646  */
    {  create_arguments(symbolTable,(yyvsp[-2].str),scope);      }
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 275 "parser.y" /* yacc.c:1646  */
    {

                                                                 


                                                                    }
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 282 "parser.y" /* yacc.c:1646  */
    {Function * func;
                            SymbolTableEntry * bucket;
                            func=create_func(NULL , scope , yylineno);
                            bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                            symbolTable_insert(symbolTable, bucket);
                                                }
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 288 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 288 "parser.y" /* yacc.c:1646  */
    {  create_arguments(symbolTable,(yyvsp[-2].str),scope);    }
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 289 "parser.y" /* yacc.c:1646  */
    {
                                                                    
                                                                    }
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 296 "parser.y" /* yacc.c:1646  */
    { SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    var = create_var((yyvsp[0].str),scope,yylineno);
                                    bucket=create_bucket_var( 1 ,  var  ,FORMAL );
                                    if(is_library_func(symbolTable,(yyvsp[0].str))){
                                        print_Red(); 

                                        fprintf(stderr,"error:formal shadows libfunc in line %d\n",yylineno); 
                                       reset_Red();
                                    }
                                    else  if(symbolTable_lookup_exists_exact_scope(symbolTable,scope,(yyvsp[0].str))!=0){
                                        print_Red(); 

                                       fprintf(stderr,"error:formal redeclaration in line %d\n",yylineno); 
                                       reset_Red();

                                     } 
                                     else{
                                       symbolTable_insert(symbolTable,bucket);
                                     }          
            }
#line 1848 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 317 "parser.y" /* yacc.c:1646  */
    {                      SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    var = create_var((yyvsp[0].str),scope,yylineno);
                                    bucket=create_bucket_var( 1 ,  var  ,FORMAL );
                                     if(symbolTable_lookup_exists_exact_scope(symbolTable,scope,(yyvsp[0].str))!=0){
                                        print_Red(); 
                                       fprintf(stderr,"error:formal redeclaration in line : %d\n",yylineno); 
                                       reset_Red();
                                     }else if(is_library_func(symbolTable,(yyvsp[0].str))){
                                        print_Red(); 

                                        fprintf(stderr,"error:formal shadows libfunc in line %d\n",yylineno); 
                                       reset_Red();

                                     }else{
                                       symbolTable_insert(symbolTable,bucket);
                                     }          
                                   
                                    }
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 335 "parser.y" /* yacc.c:1646  */
    { /*printf("lineee : %d\n",yylineno);*/ }
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 339 "parser.y" /* yacc.c:1646  */
    { /*printf("if statement\n");*/ }
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 345 "parser.y" /* yacc.c:1646  */
    {/*printf("return\n");*/}
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1894 "y.tab.c" /* yacc.c:1646  */
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
#line 349 "parser.y" /* yacc.c:1906  */


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
            fprintf(stderr,"error can't read file\n");
            return -1;
        }   
        
    }
    else if (argc>2)
    {
        if(!( yyin=fopen(argv[1],"r") )  )
        {
            fprintf(stderr,"error can't read file\n");
            return -1;
        } 
        output_file=fopen(argv[2],"w");
        if(output_file==NULL)
        {
            fprintf(stderr,"error can't open write file\n");
            return -1;
        }
    }
    else
    {
        yyin=stdin;
    }
  
    symbolTable = symbolTable_create();
    //yylex();
    //yyin=stdin;
    yyparse() ;
    //symbolTable_print(symbolTable);
    //symbolTable_print_scope_list(symbolTable, 1);
    symbolTable_print_scopes(symbolTable,4);
    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}


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
int yyerror( char * msg );
unsigned int  scope=0;


#line 81 "y.tab.c" /* yacc.c:339  */

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
    REAL = 259,
    ID = 260,
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
#define NUMBER 258
#define REAL 259
#define ID 260
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
#line 15 "parser.y" /* yacc.c:355  */

    
	int num;
    float real;
	char * str;

#line 224 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 241 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   732

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

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
static const yytype_uint16 yyrline[] =
{
       0,    47,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    59,    60,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      80,    81,    82,    83,    84,    85,    86,    87,    89,    89,
     102,   103,   104,   105,   106,   108,   136,   163,   170,   172,
     173,   174,   175,   177,   178,   179,   181,   182,   184,   186,
     188,   189,   190,   192,   193,   194,   196,   197,   198,   200,
     202,   202,   203,   203,   205,   206,   209,   242,   209,   271,
     271,   297,   297,   297,   297,   297,   299,   320,   320,   340,
     342,   343,   344,   346,   348,   349
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "REAL", "ID", "IF", "ELSE",
  "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT",
  "OR", "LOCALL", "TRUE", "FALSE", "NIL", "STRING", "EQUALS", "PLUS",
  "ASSIGN", "MINUS", "UMINUS", "ASTERISK", "DIVISION", "PERCENT",
  "DIFFERENT", "PLUS_PLUS", "MINUS_MINUS", "GREATER", "LESS",
  "GREATER_EQUALS", "LESS_EQUALS", "SEMICOLON", "COMMA", "COLON",
  "DOUBLE_COLON", "DOT", "Diaeresis", "LEFT_BRACE", "RIGHT_BRACE",
  "LEFT_SQUARE", "RIGHT_SQUARE", "LEFT_BRACKETS", "RIGHT_BRACKETS",
  "$accept", "program", "stmt", "statements", "expr", "term", "assignexpr",
  "$@1", "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elist", "objectdef", "indexed", "indexedelem", "block",
  "$@2", "$@3", "block_func", "funcdef", "$@4", "$@5", "$@6", "const",
  "idlist", "$@7", "ifstmt", "whilestmt", "forstmt", "returnstmt", YY_NULLPTR
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

#define YYPACT_NINF -128

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-128)))

#define YYTABLE_NINF -88

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-88)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     281,  -128,  -128,   -36,   -19,     3,    -1,   312,    -5,     6,
     374,    39,  -128,  -128,  -128,  -128,   374,    13,    13,  -128,
      51,    14,     2,   343,    59,  -128,   281,   563,  -128,  -128,
    -128,    55,  -128,   -35,  -128,  -128,  -128,  -128,  -128,  -128,
    -128,  -128,   374,   374,   374,  -128,  -128,  -128,   587,  -128,
    -128,  -128,  -128,  -128,    52,    10,   -35,    10,  -128,    17,
     281,   374,  -128,   540,    32,    34,    25,    93,    37,  -128,
    -128,   374,   374,   374,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,  -128,  -128,  -128,    83,    86,   374,
     374,    68,  -128,  -128,  -128,    88,   374,   374,   395,   419,
      57,    56,    94,  -128,    50,  -128,   152,   516,   374,  -128,
    -128,    61,  -128,    58,   667,   652,   682,    -3,    -3,  -128,
    -128,  -128,   682,   696,   696,   696,   696,  -128,    65,   443,
      66,   374,  -128,   468,    69,   281,   281,   374,  -128,    75,
      71,    58,  -128,   374,  -128,  -128,   374,   374,  -128,  -128,
     635,  -128,  -128,    99,  -128,   611,    94,    87,    89,   493,
      90,    95,   281,   374,    96,    94,   195,  -128,  -128,  -128,
    -128,  -128,    97,    89,  -128,  -128,   238,   281,  -128,  -128,
    -128
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    81,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    84,    85,    83,    82,     0,     0,     0,    12,
       0,    72,     0,     0,     0,    14,     2,     0,    29,    15,
      37,    40,    48,    41,    42,    10,    11,    44,     4,     5,
       6,     7,     0,     0,    62,    76,    79,    95,     0,     8,
       9,    32,    46,    31,     0,    33,     0,    35,    47,     0,
       0,     0,    65,    60,     0,     0,    66,     0,     0,     1,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,    34,    36,     0,     0,     0,
      62,     0,    54,    56,    57,     0,     0,    62,     0,     0,
       0,     0,    89,    94,     0,    71,     0,     0,    62,    63,
      64,    68,    30,    43,    27,    28,    25,    16,    17,    18,
      19,    20,    26,    21,    23,    22,    24,    49,     0,     0,
       0,     0,    51,     0,     0,     0,     0,     0,    77,    86,
       0,     0,    73,     0,    61,    67,    62,    62,    50,    58,
      39,    52,    53,    91,    92,     0,    89,     0,     0,     0,
       0,     0,     0,    62,     0,    89,     0,    80,    69,    55,
      59,    90,     0,     0,    88,    74,     0,     0,    78,    75,
      93
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -128,  -128,   -25,   -58,    -7,  -128,  -128,  -128,  -128,    -4,
    -128,    23,  -128,  -128,  -128,   -13,  -128,    20,  -128,  -128,
    -128,  -128,   -38,   -15,  -128,  -128,  -128,  -128,  -127,  -128,
    -128,  -128,  -128,  -128
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    27,    28,    29,    91,    30,    31,
      32,    33,    92,    93,    94,    64,    34,    65,    66,    35,
      59,    60,   167,    36,   101,   156,   102,    37,   140,   157,
      38,    39,    40,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,    70,   106,    51,    45,     1,    95,     2,    68,    53,
      96,    42,    97,    55,    57,    63,    67,    10,     2,    11,
      12,    13,    14,    15,    76,    77,    78,    16,    43,   164,
      11,   100,    49,    17,    18,    98,    99,    63,   174,   104,
      56,    56,    20,    50,    52,    61,    46,    22,    62,    23,
      44,    87,    88,    20,   107,    89,    58,    90,   -70,    69,
      54,   105,     6,   111,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   130,   109,   -38,
     110,    70,   129,    63,   134,   113,    85,    86,   127,   133,
      63,   128,   131,   132,   137,   144,    87,    88,   141,   139,
      89,    63,    90,   138,    61,   146,   162,    71,   176,    72,
     153,   154,   147,   -87,   149,    73,    74,   152,    75,   158,
      76,    77,    78,    79,   150,   165,    80,    81,    82,    83,
     155,   145,   166,   160,   161,   178,   159,   171,   169,    63,
      63,   112,     0,   170,   173,   177,     0,     0,     0,     0,
     172,    70,   180,     0,     0,     1,    63,     2,     3,     0,
       4,     5,     6,     7,     8,     9,     0,    10,     0,    11,
      12,    13,    14,    15,     0,     0,     0,    16,     0,     0,
       0,     0,     0,    17,    18,     0,     0,     0,     0,    19,
       0,     0,    20,     0,     0,    21,   142,    22,     1,    23,
       2,     3,     0,     4,     5,     6,     7,     8,     9,     0,
      10,     0,    11,    12,    13,    14,    15,     0,     0,     0,
      16,     0,     0,     0,     0,     0,    17,    18,     0,     0,
       0,     0,    19,     0,     0,    20,     0,     0,    21,   175,
      22,     1,    23,     2,     3,     0,     4,     5,     6,     7,
       8,     9,     0,    10,     0,    11,    12,    13,    14,    15,
       0,     0,     0,    16,     0,     0,     0,     0,     0,    17,
      18,     0,     0,     0,     0,    19,     0,     0,    20,     0,
       0,    21,   179,    22,     1,    23,     2,     3,     0,     4,
       5,     6,     7,     8,     9,     0,    10,     0,    11,    12,
      13,    14,    15,     0,     0,     0,    16,     0,     0,     0,
       0,     0,    17,    18,     0,     1,     0,     2,    19,     0,
       0,    20,     0,     0,    21,     0,    22,    10,    23,    11,
      12,    13,    14,    15,     0,     0,     0,    16,     0,     0,
       0,     0,     0,    17,    18,     0,     1,     0,     2,    47,
       0,     0,    20,     6,     0,     0,     0,    22,    10,    23,
      11,    12,    13,    14,    15,     0,     0,     0,    16,     0,
       0,     0,     0,     0,    17,    18,     0,     1,     0,     2,
       0,     0,     0,    20,     0,     0,     0,     0,    22,    10,
      23,    11,    12,    13,    14,    15,     0,     0,     0,    16,
       0,     0,     0,     0,     0,    17,    18,     0,     0,    71,
       0,    72,     0,     0,    20,     0,     0,    73,    74,    22,
      75,    23,    76,    77,    78,    79,     0,     0,    80,    81,
      82,    83,     0,    71,     0,    72,     0,     0,     0,     0,
       0,    73,    74,   135,    75,     0,    76,    77,    78,    79,
       0,     0,    80,    81,    82,    83,     0,    71,     0,    72,
       0,     0,     0,     0,     0,    73,    74,   136,    75,     0,
      76,    77,    78,    79,     0,     0,    80,    81,    82,    83,
       0,     0,    71,     0,    72,     0,     0,     0,     0,   148,
      73,    74,     0,    75,     0,    76,    77,    78,    79,     0,
       0,    80,    81,    82,    83,     0,     0,    71,     0,    72,
       0,     0,     0,     0,   151,    73,    74,     0,    75,     0,
      76,    77,    78,    79,     0,     0,    80,    81,    82,    83,
      71,     0,    72,     0,     0,     0,     0,   168,    73,    74,
       0,    75,     0,    76,    77,    78,    79,     0,     0,    80,
      81,    82,    83,     0,    71,   143,    72,     0,     0,     0,
       0,     0,    73,    74,     0,    75,     0,    76,    77,    78,
      79,     0,     0,    80,    81,    82,    83,    71,   108,    72,
       0,     0,     0,     0,     0,    73,    74,     0,    75,     0,
      76,    77,    78,    79,     0,     0,    80,    81,    82,    83,
      84,    71,     0,    72,     0,     0,     0,     0,     0,    73,
      74,     0,    75,     0,    76,    77,    78,    79,     0,     0,
      80,    81,    82,    83,   103,    71,     0,    72,     0,     0,
       0,     0,     0,    73,    74,     0,    75,     0,    76,    77,
      78,    79,     0,     0,    80,    81,    82,    83,   163,    71,
       0,    72,     0,     0,     0,     0,     0,    73,    74,     0,
      75,     0,    76,    77,    78,    79,    71,     0,    80,    81,
      82,    83,     0,     0,    73,    74,     0,    75,     0,    76,
      77,    78,    79,     0,     0,    80,    81,    82,    83,    73,
      74,     0,    75,     0,    76,    77,    78,    79,     0,     0,
      80,    81,    82,    83,   -88,    74,     0,    75,     0,    76,
      77,    78,   -88,     0,     0,    80,    81,    82,    83,    74,
       0,    75,     0,    76,    77,    78,     0,     0,     0,   -88,
     -88,   -88,   -88
};

static const yytype_int16 yycheck[] =
{
       7,    26,    60,    10,     5,     3,    41,     5,    23,    16,
      45,    47,    47,    17,    18,    22,    23,    15,     5,    17,
      18,    19,    20,    21,    27,    28,    29,    25,    47,   156,
      17,    44,    37,    31,    32,    42,    43,    44,   165,    54,
      17,    18,    40,    37,     5,    43,    47,    45,    46,    47,
      47,    41,    42,    40,    61,    45,     5,    47,    44,     0,
      47,    44,    10,    38,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    90,    46,    24,
      46,   106,    89,    90,    97,    48,    31,    32,     5,    96,
      97,     5,    24,     5,    37,   108,    41,    42,    48,     5,
      45,   108,    47,    47,    43,    47,     7,    14,   166,    16,
     135,   136,    47,    38,    48,    22,    23,    48,    25,    48,
      27,    28,    29,    30,   131,    38,    33,    34,    35,    36,
     137,   111,    43,   146,   147,   173,   143,   162,    48,   146,
     147,    48,    -1,    48,    48,    48,    -1,    -1,    -1,    -1,
     163,   176,   177,    -1,    -1,     3,   163,     5,     6,    -1,
       8,     9,    10,    11,    12,    13,    -1,    15,    -1,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    40,    -1,    -1,    43,    44,    45,     3,    47,
       5,     6,    -1,     8,     9,    10,    11,    12,    13,    -1,
      15,    -1,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    -1,
      -1,    -1,    37,    -1,    -1,    40,    -1,    -1,    43,    44,
      45,     3,    47,     5,     6,    -1,     8,     9,    10,    11,
      12,    13,    -1,    15,    -1,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    37,    -1,    -1,    40,    -1,
      -1,    43,    44,    45,     3,    47,     5,     6,    -1,     8,
       9,    10,    11,    12,    13,    -1,    15,    -1,    17,    18,
      19,    20,    21,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    31,    32,    -1,     3,    -1,     5,    37,    -1,
      -1,    40,    -1,    -1,    43,    -1,    45,    15,    47,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    32,    -1,     3,    -1,     5,    37,
      -1,    -1,    40,    10,    -1,    -1,    -1,    45,    15,    47,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    31,    32,    -1,     3,    -1,     5,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    45,    15,
      47,    17,    18,    19,    20,    21,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    14,
      -1,    16,    -1,    -1,    40,    -1,    -1,    22,    23,    45,
      25,    47,    27,    28,    29,    30,    -1,    -1,    33,    34,
      35,    36,    -1,    14,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    22,    23,    48,    25,    -1,    27,    28,    29,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    14,    -1,    16,
      -1,    -1,    -1,    -1,    -1,    22,    23,    48,    25,    -1,
      27,    28,    29,    30,    -1,    -1,    33,    34,    35,    36,
      -1,    -1,    14,    -1,    16,    -1,    -1,    -1,    -1,    46,
      22,    23,    -1,    25,    -1,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    -1,    -1,    14,    -1,    16,
      -1,    -1,    -1,    -1,    46,    22,    23,    -1,    25,    -1,
      27,    28,    29,    30,    -1,    -1,    33,    34,    35,    36,
      14,    -1,    16,    -1,    -1,    -1,    -1,    44,    22,    23,
      -1,    25,    -1,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    -1,    14,    39,    16,    -1,    -1,    -1,
      -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    14,    38,    16,
      -1,    -1,    -1,    -1,    -1,    22,    23,    -1,    25,    -1,
      27,    28,    29,    30,    -1,    -1,    33,    34,    35,    36,
      37,    14,    -1,    16,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    25,    -1,    27,    28,    29,    30,    -1,    -1,
      33,    34,    35,    36,    37,    14,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,
      29,    30,    -1,    -1,    33,    34,    35,    36,    37,    14,
      -1,    16,    -1,    -1,    -1,    -1,    -1,    22,    23,    -1,
      25,    -1,    27,    28,    29,    30,    14,    -1,    33,    34,
      35,    36,    -1,    -1,    22,    23,    -1,    25,    -1,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    22,
      23,    -1,    25,    -1,    27,    28,    29,    30,    -1,    -1,
      33,    34,    35,    36,    22,    23,    -1,    25,    -1,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    23,
      -1,    25,    -1,    27,    28,    29,    -1,    -1,    -1,    33,
      34,    35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     8,     9,    10,    11,    12,    13,
      15,    17,    18,    19,    20,    21,    25,    31,    32,    37,
      40,    43,    45,    47,    50,    51,    52,    53,    54,    55,
      57,    58,    59,    60,    65,    68,    72,    76,    79,    80,
      81,    82,    47,    47,    47,     5,    47,    37,    53,    37,
      37,    53,     5,    53,    47,    58,    60,    58,     5,    69,
      70,    43,    46,    53,    64,    66,    67,    53,    72,     0,
      51,    14,    16,    22,    23,    25,    27,    28,    29,    30,
      33,    34,    35,    36,    37,    31,    32,    41,    42,    45,
      47,    56,    61,    62,    63,    41,    45,    47,    53,    53,
      64,    73,    75,    37,    72,    44,    52,    53,    38,    46,
      46,    38,    48,    48,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,     5,     5,    53,
      64,    24,     5,    53,    64,    48,    48,    37,    47,     5,
      77,    48,    44,    39,    64,    66,    47,    47,    46,    48,
      53,    46,    48,    51,    51,    53,    74,    78,    48,    53,
      64,    64,     7,    37,    77,    38,    43,    71,    44,    48,
      48,    51,    64,    48,    77,    44,    52,    48,    71,    44,
      51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    54,    56,    55,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    62,    63,
      64,    64,    64,    65,    65,    65,    66,    66,    66,    67,
      69,    68,    70,    68,    71,    71,    73,    74,    72,    75,
      72,    76,    76,    76,    76,    76,    77,    78,    77,    77,
      79,    79,    80,    81,    82,    82
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
       0,     3,     0,     4,     2,     3,     0,     0,     8,     0,
       6,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       7,     5,     5,     9,     3,     2
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
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 89 "parser.y" /* yacc.c:1646  */
    { short status = symbolTable_lookup_exists(symbolTable,scope,yylval.str);
                                    if(status == ERROR_FUNC) {
                                        print_Red();
                                        fprintf(stderr, "error assign to function in line %d\n",yylineno);
                                        reset_Red();
                                    }
                                    }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 95 "parser.y" /* yacc.c:1646  */
    {   
    
                                    //fprintf(stderr,"lala : %s\n",yylval.str);
                                   

 }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 108 "parser.y" /* yacc.c:1646  */
    {
                                    SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    //printf("%s\n",$2);               
                                    //fprintf(stderr,"$1 : %s  scope : %d line : %d\n",$1,scope,yylineno);
                                    var = create_var((yyvsp[0].str),scope,yylineno);
                                    if(scope!=0) bucket=create_bucket_var( 1 ,  var  ,LOCAL );
                                    else bucket=create_bucket_var( 1 ,  var  ,GLOBAL );
                                
                                    if(symbolTable_lookup_exists(symbolTable,scope,(char * )(yyvsp[0].str))==0)
                                    {
                                            symbolTable_insert(symbolTable ,bucket );   
                                    }
                                    else
                                    {
                                        //printf("im here for : %s in line %d in scope %d \n", $1,yylineno,(scope-1));
                                        if (symbolTable_lookup_exists_exact_scope(symbolTable,0,(yyvsp[0].str))==0  && symbolTable_lookup_function(symbolTable , scope-1))
                                        {

                                            print_Red(); fprintf(stderr,"error no access to this variable in line :%d \n",yylineno); reset_Red();
                                        }
                                        //eisai prosbasimos?
                                        
                                    }

                                
                                
                                }
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 136 "parser.y" /* yacc.c:1646  */
    {  
                                    printf("lala2222\n");
                                    
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
#line 1647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 163 "parser.y" /* yacc.c:1646  */
    {   
                                    if(symbolTable_lookup_exists_exact_scope(symbolTable,0,(char*)(yyvsp[0].str))!=0 ) {
                                    print_Red(); 
                                    fprintf(stderr,"global variable doesnt exist\n"); 
                                    reset_Red();
                                    }
                                }
#line 1659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 202 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 202 "parser.y" /* yacc.c:1646  */
    {symbolTable_hide(symbolTable, scope); scope--;}
#line 1671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 203 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 203 "parser.y" /* yacc.c:1646  */
    {symbolTable_hide(symbolTable, scope); scope--;}
#line 1683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 205 "parser.y" /* yacc.c:1646  */
    {symbolTable_hide(symbolTable, scope); scope--;}
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 206 "parser.y" /* yacc.c:1646  */
    {symbolTable_hide(symbolTable, scope); scope--;}
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 209 "parser.y" /* yacc.c:1646  */
    {
                            Function * func;
                            SymbolTableEntry * bucket;
                            func=create_func((yyvsp[0].str) , scope , yylineno);
                            bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                            short status = symbolTable_lookup_exists_exact_scope(symbolTable,scope,(yyvsp[0].str));
                            if(is_library_func(symbolTable,(yyvsp[0].str)))
                            {
                                    print_Red(); 
                                    fprintf(stderr,"error:formal shadows libfunc\n"); 
                                    reset_Red();
                            }
                            else if (status==ERROR_FUNC )
                            {
                                    print_Red(); 
                                    fprintf(stderr,"error:function %s exists\n",(yyvsp[0].str)); 
                                    reset_Red();
                            }
                            else if(status==ERROR_VAR)
                            {
                                print_Red(); 
                                fprintf(stderr,"%s is variable \n",(yyvsp[0].str)); 
                                reset_Red();

                            }
                            else 
                            {
                                fprintf(stderr,"staus : %d\n",status);
                                symbolTable_insert(symbolTable, bucket);
                            }
                            


                        }
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 242 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 242 "parser.y" /* yacc.c:1646  */
    {
                                                                    /*Function * func;
                                                                    Variable **arguments;
                                                                    SymbolTableEntry ** arguments_buckets;
                                                                    unsigned int size;
                                                                   // printf("%s\n",);
                                                                    arguments=sanitize_arguments((char*)$4, &size,scope,func_line);
                                                                    //printf("scope : %d ,line : %d\n",scope,func_line);
                                                                    SymbolTableEntry * bucket;
                                                                    //printf("func name : %d\n",USERFUNC);
                                                                    func=create_func($2 , scope , func_line,arguments,size);
                                                                    bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                                                                    //print_args(func);
                                                                    if (!symbolTable_lookup_exists(symbolTable,  scope,(const char*)$2) )
                                                                    {
                                                                        if(arguments!=NULL)//no argumens provided
                                                                        {
                                                                            arguments_buckets=create_arguments_buckets(arguments,size);
                                                                            symbolTable_insert_args(symbolTable ,arguments_buckets,size);
                                                                        }
                                                                       
                                                                        symbolTable_insert(symbolTable, bucket);

                                                                    } */
                                                                    //free(arguments);


                                                                    }
#line 1773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 271 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 271 "parser.y" /* yacc.c:1646  */
    {
                                                                    /*Function * func;
                                                                    Variable **arguments;
                                                                    SymbolTableEntry ** arguments_buckets;
                                                                    unsigned int size;

                                                                    arguments=sanitize_arguments((char*)$2, &size,scope,yylineno);
                                                                    SymbolTableEntry * bucket;
                                                                    func=create_func(NULL , scope , yylineno,arguments,size);
                                                                    bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                                                                    //print_args(func);
                                                                    //print_args(func);

                                                                    if(arguments!=NULL)//no argumens provided
                                                                    {
                                                                        arguments_buckets=create_arguments_buckets(arguments,size);
                                                                        symbolTable_insert_args(symbolTable ,arguments_buckets,size);
                                                                    }
                                                                       
                                                                    symbolTable_insert(symbolTable, bucket);*/

                                                                     
                                                                    //free(arguments);
                                                                    }
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 299 "parser.y" /* yacc.c:1646  */
    { SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    var = create_var((yyvsp[0].str),scope,yylineno);
                                    bucket=create_bucket_var( 1 ,  var  ,FORMAL );
                                    if(is_library_func(symbolTable,(yyvsp[0].str))){
                                        print_Red(); 

                                        fprintf(stderr,"error:formal shadows libfunc\n"); 
                                       reset_Red();
                                    }
                                    else  if(symbolTable_lookup_exists_exact_scope(symbolTable,scope,(yyvsp[0].str))!=0){
                                        print_Red(); 

                                       fprintf(stderr,"error:formal redeclaration\n"); 
                                       reset_Red();

                                     } 
                                     else{
                                       symbolTable_insert(symbolTable,bucket);
                                     }          
            }
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 320 "parser.y" /* yacc.c:1646  */
    {                      SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    var = create_var((yyvsp[0].str),scope,yylineno);
                                    bucket=create_bucket_var( 1 ,  var  ,FORMAL );
                                     if(symbolTable_lookup_exists_exact_scope(symbolTable,scope,(yyvsp[0].str))!=0){
                                        print_Red(); 
                                       fprintf(stderr,"error:formal redeclaration\n"); 
                                       reset_Red();
                                     }else if(is_library_func(symbolTable,(yyvsp[0].str))){
                                        print_Red(); 

                                        fprintf(stderr,"error:formal shadows libfunc\n"); 
                                       reset_Red();

                                     }else{
                                       symbolTable_insert(symbolTable,bucket);
                                     }          
                                   
                                    }
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 338 "parser.y" /* yacc.c:1646  */
    { /*printf("lineee : %d\n",yylineno);*/ }
#line 1864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 342 "parser.y" /* yacc.c:1646  */
    { /*printf("if statement\n");*/ }
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 348 "parser.y" /* yacc.c:1646  */
    {/*printf("return\n");*/}
#line 1876 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1880 "y.tab.c" /* yacc.c:1646  */
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
#line 352 "parser.y" /* yacc.c:1906  */


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
    symbolTable_print(symbolTable);
    //symbolTable_print_scope_list(symbolTable, 1);

    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}


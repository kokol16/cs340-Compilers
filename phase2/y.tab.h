/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
    LOCAl = 272,
    TRUE = 273,
    FALSE = 274,
    NIL = 275,
    STRING = 276,
    EQUALS = 277,
    PLUS = 278,
    ASSIGN = 279,
    MINUS = 280,
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
#define LOCAl 272
#define TRUE 273
#define FALSE 274
#define NIL 275
#define STRING 276
#define EQUALS 277
#define PLUS 278
#define ASSIGN 279
#define MINUS 280
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
#line 13 "parser.y" /* yacc.c:1909  */

	int num;
    float real;
	char * str;

#line 154 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

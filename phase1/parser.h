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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
<<<<<<< HEAD:phase1/parser.h
    DIGIT = 258
  };
#endif
/* Tokens.  */
#define DIGIT 258

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
=======
    NUMBER = 258,
    IF = 259,
    ELSE = 260,
    WHILE = 261,
    FOR = 262,
    FUNCTION = 263,
    RETURN = 264,
    BREAK = 265,
    CONTINUE = 266,
    AND = 267,
    NOT = 268,
    OR = 269,
    LOCAL = 270,
    TRUE = 271,
    FALSE = 272,
    NIL = 273,
    STRING = 274,
    ID = 275,
    EQUALS = 276,
    PLUS = 277,
    ASSIGN = 278,
    MINUS = 279,
    ASTERISK = 280,
    DIVISION = 281,
    PERCENT = 282,
    DIFFERENT = 283,
    PLUS_PLUS = 284,
    MINUS_MINUS = 285,
    GREATER = 286,
    LESS = 287,
    GREATER_EQUALS = 288,
    LESS_EQUALS = 289,
    SEMICOLON = 290,
    COMMA = 291,
    COLON = 292,
    DOUBLE_COLON = 293,
    DOT = 294,
    Diaeresis = 295,
    LEFT_BRACE = 296,
    RIGHT_BRACE = 297,
    LEFT_SQUARE = 298,
    RIGHT_SQUARE = 299,
    LEFT_BRACKETS = 300,
    RIGHT_BRACKETS = 301
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define FOR 262
#define FUNCTION 263
#define RETURN 264
#define BREAK 265
#define CONTINUE 266
#define AND 267
#define NOT 268
#define OR 269
#define LOCAL 270
#define TRUE 271
#define FALSE 272
#define NIL 273
#define STRING 274
#define ID 275
#define EQUALS 276
#define PLUS 277
#define ASSIGN 278
#define MINUS 279
#define ASTERISK 280
#define DIVISION 281
#define PERCENT 282
#define DIFFERENT 283
#define PLUS_PLUS 284
#define MINUS_MINUS 285
#define GREATER 286
#define LESS 287
#define GREATER_EQUALS 288
#define LESS_EQUALS 289
#define SEMICOLON 290
#define COMMA 291
#define COLON 292
#define DOUBLE_COLON 293
#define DOT 294
#define Diaeresis 295
#define LEFT_BRACE 296
#define RIGHT_BRACE 297
#define LEFT_SQUARE 298
#define RIGHT_SQUARE 299
#define LEFT_BRACKETS 300
#define RIGHT_BRACKETS 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "parser.y" /* yacc.c:1909  */

	int num;
	char * str;

#line 151 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
>>>>>>> trelh:phase1/y.tab.h
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void * yylval);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

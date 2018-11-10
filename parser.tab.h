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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    PROG = 258,
    CLASS = 259,
    LEFT_CURLY = 260,
    RIGHT_CURLY = 261,
    LEFT_SQUARE = 262,
    RIGHT_SQUARE = 263,
    LEFT_ROUND = 264,
    RIGHT_ROUND = 265,
    VOID = 266,
    INT = 267,
    BOOL = 268,
    IF = 269,
    ELSE = 270,
    FOR = 271,
    RET = 272,
    BREAK = 273,
    CONT = 274,
    NOT = 275,
    PLUS = 276,
    MINUS = 277,
    MUL = 278,
    DIV = 279,
    MOD = 280,
    EQ = 281,
    MINEQ = 282,
    PLUSEQ = 283,
    CALLOUT = 284,
    GT = 285,
    LT = 286,
    GE = 287,
    LE = 288,
    EQEQ = 289,
    NEQ = 290,
    ANDAND = 291,
    OROR = 292,
    ALPHA = 293,
    DIGIT = 294,
    TRUE = 295,
    FALSE = 296,
    SQUOT = 297,
    DQUOT = 298,
    COMMA = 299,
    SEMICOLON = 300,
    CHAR = 301,
    UNDERSCORE = 302,
    REGEX_HEX = 303,
    REGEX_ID = 304,
    REGEX_DECIMAL = 305,
    REGEX_CHAR = 306,
    REGEX_STRING = 307
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

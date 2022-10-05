/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SRC_FRONTEND_SYNTACTIC_ANALYSIS_BISON_PARSER_H_INCLUDED
# define YY_YY_SRC_FRONTEND_SYNTACTIC_ANALYSIS_BISON_PARSER_H_INCLUDED
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
    INTEGER = 258,
    BST = 259,
    AVL = 260,
    RBT = 261,
    TREE = 262,
    VARIABLE_NAME = 263,
    FILE_PATH = 264,
    CONFIGURE = 265,
    ADD_SENTENCE = 266,
    DELETE_SENTENCE = 267,
    FIND_SENTENCE = 268,
    CREATE = 269,
    ADD_TREE_SENTENCE = 270,
    ADD_SAVE_PATH_SENTENCE = 271,
    ADD_TITLE_SENTENCE = 272,
    MAX = 273,
    MIN = 274,
    COUNT = 275,
    BALANCED = 276,
    HEIGHT = 277,
    COMMA = 278,
    SEMICOLON = 279,
    OPEN_PARENTHESIS = 280,
    CLOSE_PARENTHESIS = 281,
    OPEN_CURLY = 282,
    CLOSE_CURLY = 283
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 8 "../src/frontend/syntactic-analysis/bison-grammar.y"

	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int constantArray;
	int constant;
    int block;
    int integerParameters;
    int integerArray;

    int declaration;
    int declarationParameters;
    int treeType;

    int configureBlock;
    int treeSentences;
    int treeSentence;

    int createBlock;
    int fileSentences;
    int fileSentence;
    int fileParameter;
    int treeParameters;
    int treeArray;
    int titleParameters;
    int titleArray;
    int titleType;

	// Terminales.
	token token;
//	int integer;
  //  char nameId[1024];
    //char filePath[1024];

#line 129 "../src/frontend/syntactic-analysis/bison-parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FRONTEND_SYNTACTIC_ANALYSIS_BISON_PARSER_H_INCLUDED  */

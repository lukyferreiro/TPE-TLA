%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
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

    int declaration;

    int configureBlock;
    int treeSentences;
    int treeSentence;

    int createBlock;
    int fileSentences;
    int fileSentence;
    int treeParameters;

	// Terminales.
	token token;
	int integer;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <integer> INTEGER

// Tokens de arboles y archivos
%token <token> TREE_WORD
%token <token> TREE_ID
%token <token> TREE_TYPE
%token <token> FILE_ID

// Tokens para codigo trees
%token <token> CONFIGURE
%token <token> ADD_SENTENCE
%token <token> DELETE_SENTENCE
%token <token> FIND_SENTENCE

// Tokens para codigo files
%token <token> CREATE
%token <token> ADD_TREE_SENTENCE 
%token <token> ADD_SAVE_PATH_SENTENCE 
%token <token> FILE_PATH
%token <token> ADD_TITLE_SENTENCE

// Tokens solamente lexicos 
%token <token> COMMA
%token <token> SEMICOLON 
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_CURLY
%token <token> CLOSE_CURLY


// Tipos de dato para los no-terminales generados desde Bison.

// Generales del programa
%type <program> program
%type <constantArray> constantArray
%type <constant> constant 
%type <block> block
%type <integerParameters> integerParameters

// Bloque configure
%type <configureBlock> configureBlock
%type <treeSentences> treeSentences
%type <treeSentence> treeSentence

// Bloque create
%type <createBlock> createBlock
%type <fileSentences> fileSentences
%type <fileSentence> fileSentence
%type <treeParameters> treeParameters

// El símbolo inicial de la gramatica.
%start program

%%

// Reglas generales de estructura del programa
program: constantArray													{ $$ = ProgramGrammarAction($1); }
	;

constantArray: constant 
    | constant constantArray
    ;

constant: declaration
    | block
    ;


// Reglas para declarar una variable de tipo tree
declaration: TREE_WORD TREE_ID SEMICOLON
    | TREE_WORD TREE_ID integerParameters
    ;

integerParameters: OPEN_PARENTHESIS integerArray CLOSE_PARENTHESIS
    ;

integerArray: INTEGER
    | INTEGER COMMA integerArray
    ;

// Bloque de codigo, que puede referirse a un file o un tree
block: CONFIGURE TREE_TYPE TREE_ID configureBlock
    | CREATE FILE_ID createBlock
    ;

// Reglas para utilizar un bloque configure de tree
configureBlock: OPEN_CURLY treeSentences CLOSE_CURLY 
    ;

treeSentences: treeSentence
    | treeSentence treeSentences
    ;

treeSentence: ADD_SENTENCE integerParameters 
    | DELETE_SENTENCE integerParameters
    | FIND_SENTENCE integerParameters
    ;

// Reglas para utilizar un bloque create de file
createBlock: OPEN_CURLY fileSentences CLOSE_CURLY
    ;

fileSentences: fileSentence
    | fileSentence fileSentences
    ;

fileSentence: ADD_TREE_SENTENCE treeParameters
    | ADD_SAVE_PATH_SENTENCE FILE_PATH
    | ADD_TITLE_SENTENCE
    ;

treeParameters: TREE_ID
    | TREE_ID treeParameters;
    ;

%%

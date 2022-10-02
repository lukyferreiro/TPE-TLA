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
	int integer;
    char nameId[1024];
    char filePath[1024];
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <integer> INTEGER
%token <token> BST
%token <token> AVL
%token <token> RBT
// Tokens de arboles y archivos
%token <token> TREE
%token <nameId> TREE_NAME
%token <nameId> FILE_NAME
// Tokens para codigo trees
%token <token> CONFIGURE
%token <token> ADD_SENTENCE
%token <token> DELETE_SENTENCE
%token <token> FIND_SENTENCE
// Tokens para codigo files
%token <token> CREATE
%token <token> ADD_TREE_SENTENCE 
%token <token> ADD_SAVE_PATH_SENTENCE 
%token <filePath> FILE_PATH
%token <token> ADD_TITLE_SENTENCE
%token <token> MAX
%token <token> MIN
%token <token> COUNT
%token <token> BALANCED
%token <token> HEIGHT
// Tokens solamente lexicos 
%token <token> COMMA
%token <token> SEMICOLON 
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_CURLY
%token <token> CLOSE_CURLY


//-----------------------------------------------------------
// Tipos de dato para los no-terminales generados desde Bison.
//-----------------------------------------------------------

// Generales del programa
%type <program> program
%type <constantArray> constantArray
%type <constant> constant
%type <declaration> declaration 
%type <declarationParameters> declarationParameters
%type <block> block
%type <integerParameters> integerParameters
%type <integerArray> integerArray
%type <treeType> treeType
// Bloque configure
%type <configureBlock> configureBlock
%type <treeSentences> treeSentences
%type <treeSentence> treeSentence
// Bloque create
%type <createBlock> createBlock
%type <fileSentences> fileSentences
%type <fileSentence> fileSentence
%type <treeParameters> treeParameters
%type <treeArray> treeArray
%type <fileParameter> fileParameter
%type <titleParameters> titleParameters
%type <titleArray> titleArray
%type <titleType> titleType

// El símbolo inicial de la gramatica.
%start program

%%

// Reglas generales de estructura del programa
program: constantArray													{ $$ = ProgramGrammarAction($1); }
	;

constantArray: constant                                                 { $$ = ConstantGrammarAction($1); }
    | constant constantArray                                            { $$ = ConstantArrayGrammarAction($1, $2); } //check
    ;

constant: declaration                                                   { $$ = DeclarationGrammarAction($1); }
    | block                                                             { $$ = BlockGrammarAction($1); }
    ;

// Reglas para declarar una variable de tipo tree
declaration: TREE TREE_NAME declarationParameters SEMICOLON             { $$ = DeclarationTreeGrammarAction($2, $3); }
    ;

declarationParameters: integerParameters                                { $$ = DeclarationTreeParametersGrammarAction($1); }
    | /*lamba*/                                                         { $$ = 0 }
    ;

integerParameters: OPEN_PARENTHESIS integerArray CLOSE_PARENTHESIS      { $$ = IntegerParametersGrammarAction($2); }
    ;

integerArray: INTEGER                                                   { $$ = IntegerConstantGrammarAction($1); }
    | INTEGER COMMA integerArray                                        { $$ = IntegerConstantArrayGrammarAction($1, $3); }
    ;

// Bloque de codigo, que puede referirse a un file o un tree
block: CONFIGURE treeType TREE_NAME configureBlock                      { $$ = ConfigureBlockGrammarAction($2, $3, $4); }
    | CREATE FILE_NAME createBlock                                      { $$ = CreateBlockGrammarAction($2, $3); }
    ;

treeType: BST                                                           { $$ = TreeTypeBSTGrammarAction(); }
    | AVL                                                               { $$ = TreeTypeAVLGrammarAction(); }
    | RBT                                                               { $$ = TreeTypeRBTGrammarAction(); }
    | /*lambda*/                                                        { $$ = 0 }
    ;

// Reglas para utilizar un bloque configure de tree
configureBlock: OPEN_CURLY treeSentences CLOSE_CURLY                    { $$ = TreeSentencesGrammarAction($2); }
    ;

treeSentences: treeSentence                                             { $$ = TreeSentenceGrammarAction($1); }
    | treeSentence treeSentences                                        { $$ = TreeSentenceArrayGrammarAction($1, $2); }
    ;

treeSentence: ADD_SENTENCE integerParameters SEMICOLON                  { $$ = AddSentenceGrammarAction($2); }
    | DELETE_SENTENCE integerParameters SEMICOLON                       { $$ = DeleteSentenceGrammarAction($2); }
    | FIND_SENTENCE integerParameters SEMICOLON                         { $$ = FindSentenceGrammarAction($2); }
    ;

// Reglas para utilizar un bloque create de file
createBlock: OPEN_CURLY fileSentences CLOSE_CURLY                       { $$ = FileSentencesGrammarAction($2); }
    ;

fileSentences: fileSentence                                             { $$ = FileSentenceGrammarAction($1); }
    | fileSentence fileSentences                                        { $$ = FileSentenceArrayGrammarAction($1, $2); }
    ;

fileSentence: ADD_TREE_SENTENCE treeParameters SEMICOLON                { $$ = AddTreeSentenceGrammarAction($2); }
    | ADD_SAVE_PATH_SENTENCE fileParameter SEMICOLON                    { $$ = AddSavePathSentenceGrammarAction($2); }
    | ADD_TITLE_SENTENCE titleParameters SEMICOLON                      { $$ = AddTitleSentenceGrammarAction($2); }
    ;

treeParameters: OPEN_PARENTHESIS treeArray CLOSE_PARENTHESIS            { $$ = TreeParametersGrammarAction($2); }
    ;

fileParameter: OPEN_PARENTHESIS FILE_PATH CLOSE_PARENTHESIS             { $$ = FileParameterSentenceGrammarAction($2); }
    ;

treeArray: TREE_NAME                                                    { $$ = TreeNameGrammarAction($1); }
    | TREE_NAME COMMA treeArray                                         { $$ = TreeNameArrayGrammarAction($1, $3); }
    ;

titleParameters: OPEN_PARENTHESIS titleArray CLOSE_PARENTHESIS          { $$ = TitleParametersGrammarAction($2); }
    ;

titleArray: titleType                                                   { $$ = TitleTypeGrammarAction($1); }
    | titleType COMMA titleArray                                        { $$ = TitleTypeArrayGrammarAction($1, $3); }
    ;

titleType: MAX                                                          { $$ = TitleMaxGrammarAction(); }
    | MIN                                                               { $$ = TitleMinGrammarAction(); }
    | COUNT                                                             { $$ = TitleCountGrammarAction(); }
    | BALANCED                                                          { $$ = TitleBalancedGrammarAction(); }
    | HEIGHT                                                            { $$ = TitleHeightGrammarAction(); }
    ;

%%

%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
    Program program;
    ConstantArray constantArray;
    Constant constant;
    Block block;
    IntegerParameters integerParameters;
    IntegerArray integerArray;
    Declaration declaration;
    DeclarationParameters declarationParameters;
    TreeType treeType;
    ConfigureBlock configureBlock;
    TreeSentences treeSentences;
    TreeSentence treeSentence;
    CreateBlock createBlock;
    FileSentences fileSentences;
    FileSentence fileSentence;
    FileParameter fileParameter;
    TreeParameters treeParameters;
    TreeArray treeArray;
    LegendParameters legendParameters;
    LegendArray legendArray;
    LegendType legendType;

	// Terminales.
	token token;
    int integer;
    char* string;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <integer> INTEGER
%token <token> BST
%token <token> AVL
%token <token> RBT
// Tokens de arboles y archivos
%token <token> TREE
%token <string> VARIABLE_NAME
%token <string> FILE_PATH
// Tokens para codigo trees
%token <token> CONFIGURE
%token <token> ADD_NODE
%token <token> DELETE_NODE
%token <token> FIND_NODE
// Tokens para codigo files
%token <token> CREATE
%token <token> ADD_TREE
%token <token> ADD_FILE_PATH
%token <token> ADD_LEGEND
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
%token <token> UNKNOWN

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
%type <legendParameters> legendParameters
%type <legendArray> legendArray
%type <legendType> legendType

// El símbolo inicial de la gramatica.
%start program

%%

// Reglas generales de estructura del programa
program: constantArray													{ $$ = ProgramGrammarAction($1); }
	;

constantArray: constant                                                 { $$ = ConstantGrammarAction($1); }
    | constant constantArray                                            { $$ = ConstantArrayGrammarAction($1, $2); }
    ;

constant: declaration                                                   { $$ = DeclarationGrammarAction($1); }
    | block                                                             { $$ = BlockGrammarAction($1); }
    ;

// Reglas para declarar una variable de tipo tree
declaration: TREE VARIABLE_NAME declarationParameters SEMICOLON         { $$ = DeclarationTreeGrammarAction($2, $3); }
    ;

declarationParameters: integerParameters                                { $$ = DeclarationTreeParametersGrammarAction($1); }
    | %empty                                                            { $$ = 0; }
    ;

integerParameters: OPEN_PARENTHESIS integerArray CLOSE_PARENTHESIS      { $$ = IntegerParametersGrammarAction($2); }
    ;

integerArray: INTEGER                                                   { $$ = IntegerConstantGrammarAction($1); }
    | INTEGER COMMA integerArray                                        { $$ = IntegerConstantArrayGrammarAction($1, $3); }
    ;

// Bloque de codigo, que puede referirse a un file o un tree
block: CONFIGURE treeType VARIABLE_NAME configureBlock                  { $$ = ConfigureBlockGrammarAction($2, $3, $4); }
    | CREATE VARIABLE_NAME createBlock                                  { $$ = CreateBlockGrammarAction($2, $3); }
    ;

treeType: BST                                                           { $$ = TreeTypeBSTGrammarAction(); }
    | AVL                                                               { $$ = TreeTypeAVLGrammarAction(); }
    | RBT                                                               { $$ = TreeTypeRBTGrammarAction(); }
    | %empty                                                            { $$ = 0; }
    ;

// Reglas para utilizar un bloque configure de tree
configureBlock: OPEN_CURLY treeSentences CLOSE_CURLY                    { $$ = TreeSentencesGrammarAction($2); }
    ;

treeSentences: treeSentence                                             { $$ = TreeSentenceGrammarAction($1); }
    | treeSentence treeSentences                                        { $$ = TreeSentenceArrayGrammarAction($1, $2); }
    ;

treeSentence: ADD_NODE integerParameters SEMICOLON                      { $$ = AddNodeGrammarAction($2); }
    | DELETE_NODE integerParameters SEMICOLON                           { $$ = DeleteNodeGrammarAction($2); }
    | FIND_NODE integerParameters SEMICOLON                             { $$ = FindNodeGrammarAction($2); }
    ;

// Reglas para utilizar un bloque create de file
createBlock: OPEN_CURLY fileSentences CLOSE_CURLY                       { $$ = FileSentencesGrammarAction($2); }
    ;

fileSentences: fileSentence                                             { $$ = FileSentenceGrammarAction($1); }
    | fileSentence fileSentences                                        { $$ = FileSentenceArrayGrammarAction($1, $2); }
    ;

fileSentence: ADD_TREE treeParameters SEMICOLON                         { $$ = AddTreeGrammarAction($2); }
    | ADD_FILE_PATH fileParameter SEMICOLON                             { $$ = AddFilePathGrammarAction($2); }
    | ADD_LEGEND legendParameters SEMICOLON                             { $$ = AddLegendGrammarAction($2); }
    ;

treeParameters: OPEN_PARENTHESIS treeArray CLOSE_PARENTHESIS            { $$ = TreeParametersGrammarAction($2); }
    ;

fileParameter: OPEN_PARENTHESIS FILE_PATH CLOSE_PARENTHESIS             { $$ = FileParameterSentenceGrammarAction($2); }
    ;

treeArray: VARIABLE_NAME                                                { $$ = TreeNameGrammarAction($1); }
    | VARIABLE_NAME COMMA treeArray                                     { $$ = TreeNameArrayGrammarAction($1, $3); }
    ;

legendParameters: OPEN_PARENTHESIS legendArray CLOSE_PARENTHESIS        { $$ = LegendParametersGrammarAction($2); }
    ;

legendArray: legendType                                                 { $$ = LegendTypeGrammarAction($1); }
    | legendType COMMA legendArray                                      { $$ = LegendTypeArrayGrammarAction($1, $3); }
    ;

legendType: MAX                                                         { $$ = LegendMaxGrammarAction(); }
    | MIN                                                               { $$ = LegendMinGrammarAction(); }
    | COUNT                                                             { $$ = LegendCountGrammarAction(); }
    | BALANCED                                                          { $$ = LegendBalancedGrammarAction(); }
    | HEIGHT                                                            { $$ = LegendHeightGrammarAction(); }
    ;

%%

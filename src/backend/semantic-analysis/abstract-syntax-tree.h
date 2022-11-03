#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

/* *
 * Se realiza este tipo de definiciones cuando el tipo de dato debe
 * auto-referenciarse, como es el caso de una "Expression", que está compuesta
 * de otras 2 expresiones.
 */
/* typedef struct Expression Expression; */

/**
 * Para cada terminal se define una nueva estructura que representa su tipo
 * de dato y, por lo tanto, su nodo en el AST (Árbol de Sintaxis Abstracta).
 */
/* typedef struct {
    int value;
} Constant; */

/**
 * En caso de que un no-terminal ("Factor" en este caso), posea más de una
 * regla de producción asociada, se crea además de la estructura un enumerado
 * que identitifque cada reducción posible (cada regla de producción). Luego,
 * se agrega una instancia de este enumerado dentro del nodo del no-terminal.
 *
 * De este modo, al recorrer el AST, es posible determinar qué nodos hijos
 * posee según el valor de este enumerado.
 */
/* 
typedef enum {
    EXPRESSION,
    CONSTANT
} FactorType;

typedef struct {
    FactorType type;
    Expression* expression;
} Factor;

typedef enum {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    FACTOR
} ExpressionType;

struct Expression {
    ExpressionType type;
    Expression* leftExpression;
    Expression* rightExpression;
};

typedef struct {
    Expression* expression;
} Program; */

//--------------------------------------------------
//---------------------TERMINALES-------------------
//--------------------------------------------------

typedef struct {
    int* value;
} Integer; 

typedef struct {
    char* name;
} TreeName; 

typedef struct {
    char* name;
} FileName; 

typedef struct {
    char* file_path;
} FilePath; 

//--------------------------------------------------
//-------------------NO TERMINALES------------------
//--------------------------------------------------

typedef enum {
    MAX,
    MIN,
    COUNT,
    BALANCED,
    HEIGHT
} LegendType;

typedef struct LegendArray LegendArray;
struct LegendArray {
    LegendType legendType;
    LegendArray* LegendArray;
};

typedef struct {
    LegendArray* legendArray;
} LegendParameters; 

typedef struct {
    FilePath filePath;
} FileParameter; 

typedef struct TreeArray TreeArray;
struct TreeArray {
    TreeName TreeName;
    TreeArray* TreeArray;
};

typedef struct {
    TreeArray* treeArray;
} TreeParameters; 

typedef enum {
    TREE,
    FILE_PATH,
    LEGEND
} FileSentenceType;

typedef struct {
    FileSentenceType type;
    TreeParameters* treeParameters;
    FileParameter* fileParameter;
    LegendParameters* legendParameters;
} FileSentence; 

typedef struct FileSentences FileSentences;
struct FileSentences {
    FileSentence* fileSentence;
    FileSentences* fileSentences;
};

typedef struct {
    FileSentences* fileSentences;
} CreateBlock; 

typedef enum {
    ADD,
    DELETE,
    FIND
} TreeSentenceType;

typedef struct {
    TreeSentenceType type;
    IntegerParameters* integerParameters;
} TreeSentence; 

typedef struct TreeSentences TreeSentences;
struct TreeSentences {
    TreeSentence* treeSentence;
    TreeSentences* treeSentence;
};

typedef struct {
    TreeSentences* treeSentences;
} ConfigureBlock; 

typedef enum {
    BST,
    AVL,
    RBT
} TreeType;

typedef enum {
    CONFIGURE,
    CREATE
} BlockType;

typedef struct {
    BlockType type;
    TreeType treeType;
    TreeName treeName;
    FileName fileName;
    ConfigureBlock* configureBlock;
    CreateBlock* createBlock;
} Block; 

typedef struct IntegerArray IntegerArray;

struct IntegerArray {
    Integer integer;
    IntegerArray* IntegerArray;
};
typedef struct {
    IntegerArray* integerArray;
} IntegerParameters; 

typedef enum {
    INTEGER_PARAMETERS,
    EMPTY
} DeclarationParametersType;

typedef struct {
    DeclarationParametersType type;
    IntegerParameters* integerParameters;
} DeclarationParameters; 

typedef struct {
    TreeName* treeName;
    DeclarationParameters* declarationParameters;
} Declaration; 

typedef enum {
    DECLARATION,
    BLOCK
} ConstantType;

typedef struct {
    ConstantType type;
    Declaration* declaration;
    Block* block;
} Constant; 

typedef struct ConstantArray ConstantArray;

struct ConstantArray {
    Constant* constant;
    ConstantArray* constantArray;
};
typedef struct {
    ConstantArray* constantArray;
} Program;

#endif

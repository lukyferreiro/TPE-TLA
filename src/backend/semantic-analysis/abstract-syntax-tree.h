#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

typedef struct Variable Variable;
typedef struct Program Program;
typedef struct ConstantArray ConstantArray;
typedef struct Constant Constant;
typedef struct Declaration Declaration;
typedef struct DeclarationParameters DeclarationParameters;
typedef struct Block Block;
typedef struct TreeTypeStruct TreeTypeStruct;
typedef struct ConfigureBlock ConfigureBlock;
typedef struct TreeSentences TreeSentences;
typedef struct TreeSentence TreeSentence;
typedef struct CreateBlock CreateBlock;
typedef struct FileSentences FileSentences;
typedef struct FileSentence FileSentence;
typedef struct TreeParameters TreeParameters;
typedef struct TreeArray TreeArray;
typedef struct FileParameter FileParameter;
typedef struct LegendParameters LegendParameters;
typedef struct LegendArray LegendArray;
typedef struct LegendTypeStruct LegendTypeStruct;
typedef struct IntegerParameters IntegerParameters;
typedef struct IntegerArray IntegerArray;

typedef enum {
    ONE_INTEGER,
    VARIOUS_INTEGER
} IntegerArrayType;

struct IntegerArray {
    IntegerArrayType type;
    int value;
    IntegerArray* nextIntegerArray;
};

struct IntegerParameters {
    IntegerArray* integerArray;
};

typedef enum {
    MAX_LEGEND,
    MIN_LEGEND,
    COUNT_LEGEND,
    BALANCED_LEGEND,
    HEIGHT_LEGEND,
    NONE
} LegendType;

struct LegendTypeStruct {
    LegendType legendType;
};

typedef enum {
    ONE_LEGEND,
    VARIOUS_LEGENDS
} LegendArrayType;

struct LegendArray {
    LegendArrayType type;
    LegendTypeStruct* legendType;
    LegendArray* nextLegendArray;
};

struct LegendParameters {
    LegendArray* legendArray;
};

struct FileParameter {
    char* filePath;
};

typedef enum {
    ONE_TREE,
    VARIOUS_TREES
} TreeArrayType;

struct TreeArray {
    TreeArrayType type;
    char* treeName;
    TreeArray* nextTreeArray;
};

struct TreeParameters {
    TreeArray* treeArray;
};

typedef enum {
    ADD_TREE_SENTENCE,
    ADD_FILE_PATH_SENTENCE,
    ADD_LEGEND_SENTENCE
} FileSentenceType;

struct FileSentence {
    FileSentenceType type;
    TreeParameters* treeParameters;
    FileParameter* fileParameter;
    LegendParameters* legendParameters;
};

typedef enum {
    ONE_FILE_SENTENCE,
    VARIOUS_FILE_SENTENCES
} FileSentencesType;

struct FileSentences {
    FileSentencesType type;
    FileSentence* fileSentence;
    FileSentences* nextFileSentences;
};

struct CreateBlock {
    FileSentences* fileSentences;
};

typedef enum {
    ADD_NODE_SENTENCE,
    DELETE_NODE_SENTENCE,
    FIND_NODE_SENTENCE
} TreeSentenceType;

struct TreeSentence {
    TreeSentenceType type;
    IntegerParameters* integerParameters;
};

typedef enum {
    ONE_TREE_SENTENCE,
    VARIOUS_TREE_SENTENCES
} TreeSentencesType;

struct TreeSentences {
    TreeSentencesType type;
    TreeSentence* treeSentence;
    TreeSentences* nextTreeSentences;
};

struct ConfigureBlock {
    TreeSentences* treeSentences;
};

typedef enum {
    BST_TYPE,
    AVL_TYPE,
    RBT_TYPE
} TreeType;

struct TreeTypeStruct {
    TreeType treeType;
};

typedef enum {
    CONFIGURE_BLOCK,
    CREATE_BLOCK
} BlockType;

struct Block {
    BlockType type;
    TreeTypeStruct* treeType;
    char* treeName;
    char* fileName;
    ConfigureBlock* configureBlock;
    CreateBlock* createBlock;
};

struct DeclarationParameters {
    IntegerParameters* integerParameters;
};

struct Declaration {
    char* treeName;
    DeclarationParameters* declarationParameters;
};

typedef enum {
    DECLARATION,
    BLOCK
} ConstantType;

struct Constant {
    ConstantType type;
    Declaration* declaration;
    Block* block;
};

typedef enum {
    ONE_CONSTANT,
    VARIOUS_CONSTANTS
} ConstantArrayType;

struct ConstantArray {
    ConstantArrayType type;
    Constant* constant;
    ConstantArray* nextConstantArray;
};

struct Program {
    ConstantArray* constantArray;
};

#endif

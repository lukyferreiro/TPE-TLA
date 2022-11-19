#include "generator.h"
#include "../../backend/support/logger.h"
#include "../../backend/domain-specific/tree_handlers/tree.h"

#define MAX_NUM_TREES 128

struct FileWithName {
    char* name;
    char* filePath;
    //arreglo con los árboles que va a imprimir
    //arreglo de modificadores para el archivo
};
struct GeneratorState {
    char* treeNames[MAX_NUM_TREES]; //arreglo con los nombres
    struct node* currentTrees[MAX_NUM_TREES];
    int size;
};

static struct GeneratorState *myGeneratorState;

void Generator(Program* program, FILE* out) {
    //inicializar struct generator state
    //myGeneratorState= (struct GeneratorState *) calloc(1, sizeof(struct GeneratorState));
    LogInfo("Generating program");
    GeneratorConstantArray(program->constantArray, out);
}

void GeneratorConstantArray(ConstantArray* constantArray, FILE* out) {
    LogInfo("Generating ConstantArray");
    switch (constantArray->type) {
        case ONE_CONSTANT:
            GeneratorConstant(constantArray->constant, out);
            break;
        case VARIOUS_CONSTANTS:;
            GeneratorConstant(constantArray->constant, out);
            GeneratorConstantArray(constantArray->nextConstantArray, out);
            break;
        default:
            break;
    }
}

void GeneratorConstant(Constant* constant, FILE* out) {
    LogInfo("Generating Constant");
    switch (constant->type) {
        case DECLARATION:
            GeneratorDeclaration(constant->declaration, out);
            break;
        case BLOCK:
            GeneratorBlock(constant->block, out);
            break;
        default:
            break;
    }
}

void GeneratorDeclaration(Declaration* declaration, FILE* out) {
    LogInfo("Generating Declaration");
    fprintf(out, "\tlabel = \"%s\";\n", declaration->treeName);

    //guardo el nombre del nuevo arbol y inicializo ese arbol con null
    //ver cuando conviene mover el size++
    //myGeneratorState->treeNames[myGeneratorState->size] = declaration->treeName;
    //myGeneratorState->currentTrees[myGeneratorState->size] = NULL;
    GeneratorDeclarationParameters(declaration->declarationParameters, out);
}

void GeneratorDeclarationParameters(DeclarationParameters* declarationParameters, FILE* out) {
    LogInfo("Generating DeclarationParameters");
    GeneratorIntegerParameters(declarationParameters->integerParameters, out);
}

void GeneratorIntegerParameters(IntegerParameters* integerParameters, FILE* out) {
    LogInfo("Generating IntegerParameters");
    GeneratorIntegerArray(integerParameters->integerArray, out);
}

void GeneratorIntegerArray(IntegerArray* integerArray, FILE* out) {
    LogInfo("Generating IntegerArray");
    switch (integerArray->type) {
        case ONE_INTEGER:
            GeneratorInteger(integerArray->value, out);
            break;
        case VARIOUS_INTEGER:
            GeneratorInteger(integerArray->value, out);
            GeneratorIntegerArray(integerArray->nextIntegerArray, out);
            break;
        default:
            break;
    }
}

void GeneratorBlock(Block* block, FILE* out) {
    LogInfo("Generating Block");
    switch (block->type) {
        case CONFIGURE_BLOCK:
            //capaz debería inicializar una variable según el tipo que nos hayan pasado
            GeneratorTreeType(block->treeType, out);
            //debería buscar en el estado del programa el árbol con ese nombre 
            // cambiarle el tipo por el nuevo??? 
            //insertar los nodos que ya tuviera
            //ya debería estar creado. con esto lo único que hago es devoler el nombre 
            GeneratorTreeName(block->treeName, out);
            //pasar el árbol como parámetro?
            GeneratorConfigureBlock(block->configureBlock, out);
            break;
        case CREATE_BLOCK:
            //crear un struct que sea para los files, con el filename
            //filepath, arreglo de nombres de arboles, etc... ?
            GeneratorFileName(block->fileName, out);
            GeneratorCreateBlock(block->createBlock, out);
            break;
        default:
            break;
    }
}

void GeneratorConfigureBlock(ConfigureBlock* configureBlock, FILE* out) {
    LogInfo("Generating ConfigureBlock");
    GeneratorTreeSentences(configureBlock->treeSentences, out);
}

void GeneratorTreeSentences(TreeSentences* treeSentences, FILE* out) {
    LogInfo("Generating TreeSentences");
    switch (treeSentences->type) {
        case ONE_TREE_SENTENCE:
            GeneratorTreeSentence(treeSentences->treeSentence, out);
            break;
        case VARIOUS_TREE_SENTENCES:
            GeneratorTreeSentence(treeSentences->treeSentence, out);
            GeneratorTreeSentences(treeSentences->nextTreeSentences, out);
            break;
        default:
            break;
    }
}

void GeneratorTreeSentence(TreeSentence* treeSentence, FILE* out) {
    LogInfo("Generating TreeSentence");
    switch (treeSentence->type) {
        case ADD_NODE_SENTENCE:
            //Voy al arbol que haga falta y le inserto el nodo
            //si ya existía el nodo, debería tirar un warning y no generar outputs
            GeneratorIntegerParameters(treeSentence->integerParameters, out);
            break;
        case DELETE_NODE_SENTENCE:
            //Voy al arbol que haga falta y le borro el nodo
            //si no existía el nodo, debería tirar un warning y no generar outputs
            GeneratorIntegerParameters(treeSentence->integerParameters, out);
            break;
        case FIND_NODE_SENTENCE:
            //Voy al arbol que haga falta y le seteo al nodo found=true?
            //Si no existía, no hago nada y sigo
            GeneratorIntegerParameters(treeSentence->integerParameters, out);
            break;
        default:
            break;
    }
}

void GeneratorCreateBlock(CreateBlock* createBlock, FILE* out) {
    LogInfo("Generating CreateBlock");
    GeneratorFileSentences(createBlock->fileSentences, out);
}

void GeneratorFileSentences(FileSentences* fileSentences, FILE* out) {
    LogInfo("Generating FileSentences");
    switch (fileSentences->type) {
        case ONE_FILE_SENTENCE:
            GeneratorFileSentence(fileSentences->fileSentence, out);
            break;
        case VARIOUS_FILE_SENTENCES:
            GeneratorFileSentence(fileSentences->fileSentence, out);
            GeneratorFileSentences(fileSentences->nextFileSentences, out);
            break;
        default:
            break;
    }
}

void GeneratorFileSentence(FileSentence* fileSentence, FILE* out) {
    LogInfo("Generating FileSentence");
    switch (fileSentence->type) {
        case ADD_TREE_SENTENCE:
            //Voy al arbol y lo agrego al archivo
            GeneratorTreeParameters(fileSentence->treeParameters, out);
            break;
        case ADD_FILE_PATH_SENTENCE:
            //agrego al struct el filepath 
            GeneratorFileParameter(fileSentence->fileParameter, out);
            break;
        case ADD_LEGEND_SENTENCE:
            //agrego a un arreglo de legend parameters el que me pasen
            //O tengo un arreglo de bool a ver si tengo que usarlo o no
            GeneratorLegendParameters(fileSentence->legendParameters, out);
            break;
        default:
            break;
    }
}

void GeneratorTreeParameters(TreeParameters* treeParameters, FILE* out) {
    LogInfo("Generating TreeParameters");
    GeneratorTreeArray(treeParameters->treeArray, out);
}

void GeneratorTreeArray(TreeArray* treeArray, FILE* out) {
    LogInfo("Generating TreeArray");
    switch (treeArray->type) {
        case ONE_TREE:
            // Veo como agregar las structs a 
            GeneratorTreeName(treeArray->treeName, out);
            break;
        case VARIOUS_TREES:
            // TODO mmmmmm
            GeneratorTreeName(treeArray->treeName, out);
            GeneratorTreeArray(treeArray->nextTreeArray, out);
            break;
        default:
            break;
    }
}

void GeneratorFileParameter(FileParameter* fileParameter, FILE* out) {
    LogInfo("Generating FileParameter");
    GeneratorFilePath(fileParameter->filePath, out);
}

void GeneratorLegendParameters(LegendParameters* legendParameters, FILE* out) {
    LogInfo("Generating LegendParameters");
    GeneratorLegendArray(legendParameters->legendArray, out);
}

void GeneratorLegendArray(LegendArray* legendArray, FILE* out) {
    LogInfo("Generating LegendArray");
    switch (legendArray->type) {
        case ONE_LEGEND:
            GeneratorLegendType(legendArray->legendType, out);
            break;
        case VARIOUS_LEGENDS:
            GeneratorLegendType(legendArray->legendType, out);
            GeneratorLegendArray(legendArray->nextLegendArray, out);
            break;
        default:
            break;
    }
}

void GeneratorInteger(int value, FILE* out) {
    LogInfo("Generating Integer leaf");
    //aca realizo la inserción en sí al arbol que me vayan pasando
    //agregar switch case para ver si tengo que hacer insert, delete, o find
    //if(myGeneratorState->currentTrees[myGeneratorState->size]==NULL){
    //    myGeneratorState->currentTrees[myGeneratorState->size] = insertFirstNode(myGeneratorState->currentTrees[myGeneratorState->size], value, BST);
    //}
    //else {
    //    myGeneratorState->currentTrees[myGeneratorState->size] = insertNode(myGeneratorState->currentTrees[myGeneratorState->size], value);
    //}

    fprintf(out, "\t%d;\n", value);
}

void GeneratorTreeType(TreeTypeStruct* type, FILE* out) {
    // TODO
    LogInfo("Generating TreeType leaf");
    type->treeType;
}

void GeneratorLegendType(LegendTypeStruct* type, FILE* out) {
    // TODO
    LogInfo("Generating LegendType leaf");
    type->legendType;
}

void GeneratorTreeName(char* treeName, FILE* out) {
    // TODO
    LogInfo("Generating TreeName leaf");
}

void GeneratorFileName(char* fileName, FILE* out) {
    // TODO
    LogInfo("Generating FileName leaf");
}

void GeneratorFilePath(char* FilePath, FILE* out) {
    // TODO
    LogInfo("Generating FilePath leaf");
}
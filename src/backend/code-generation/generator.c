#include "generator.h"
#include "../../backend/domain-specific/tree.h"
#include "../../backend/support/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_TREES 20

struct FileWithName {
    char* name;
    char* filePath;

    // Nombre del archivo con su path
    char* fullPathName;
    // Comando a correr para generar el .png
    char* command;

    // Arreglo con los nombres de los árboles que va a imprimir
    char* treeNames[MAX_NUM_TREES];
    // Arreglo con los árboles que va a imprimir
    struct node* currentTrees[MAX_NUM_TREES];
    int treeSize;

    // arreglo de modificadores para el archivo
    LegendType legendParams[LEGEND_TYPES];
};
struct GeneratorState {
    // Arreglo global con todos los árboles, y sus nombres
    char* treeNames[MAX_NUM_TREES];
    struct node* currentTrees[MAX_NUM_TREES];
    int size;
};

// Estado global de la aplicación
static struct GeneratorState* myGeneratorState;
// Archivo actual a utilizar
static struct FileWithName* currentFile;
// FILE* al que escribir el .dot
static FILE* outputFile;
// Arreglo de char* para indicar si un legend se encuentra repetido
static char* legendNames[LEGEND_TYPES] = {"max", "min", "count", "balanced", "height"};

// Variable a retornar al main.c
// 0 si no hubo problemas, 1 en caso de warning, 2 en caso de error
static int programSuccess = 0;

// Funciones auxiliares
static int findTreeIndexByName(char* treeName);
static void resetFoundNodes();
static void generateDotFullPathName();
static void generateCommand();

int Generator(Program* program) {
    // Inicializar struct generator state
    myGeneratorState = (struct GeneratorState*)calloc(1, sizeof(struct GeneratorState));

    if (myGeneratorState == NULL) {
        LogError("El programa finalizo abruptamente debido a que ya no hay memoria disponible");
        programSuccess = 2;
        return programSuccess;
    }

    LogDebug("Generating program");
    GeneratorConstantArray(program->constantArray);
    return programSuccess;
}

void GeneratorConstantArray(ConstantArray* constantArray) {
    LogDebug("Generating ConstantArray");
    switch (constantArray->type) {
        case ONE_CONSTANT:
            GeneratorConstant(constantArray->constant);
            break;
        case VARIOUS_CONSTANTS:;
            GeneratorConstant(constantArray->constant);
            GeneratorConstantArray(constantArray->nextConstantArray);
            break;
        default:
            break;
    }
}

void GeneratorConstant(Constant* constant) {
    LogDebug("Generating Constant");
    switch (constant->type) {
        case DECLARATION:
            GeneratorDeclaration(constant->declaration);
            break;
        case BLOCK:
            GeneratorBlock(constant->block);
            break;
        default:
            break;
    }
}

void GeneratorDeclaration(Declaration* declaration) {
    LogDebug("Generating Declaration");

    // Chequeamos que todavía se puedan agregar árboles. Sino, informamos el error
    if (myGeneratorState->size >= MAX_NUM_TREES) {
        LogError("La aplicación solo soporta un máximo de 20 árboles simultáneamente\n");
        programSuccess = 2;
        return;
    }

    // Guardo el nombre del nuevo arbol
    myGeneratorState->treeNames[myGeneratorState->size] = declaration->treeName;

    // Inicializo ese arbol en null
    myGeneratorState->currentTrees[myGeneratorState->size] = NULL;

    // incremento el size luego de que paso el index como param, para que las funciones que sigan sepan donde realizar la operacion
    GeneratorDeclarationParameters(declaration->declarationParameters, myGeneratorState->size++);
}

void GeneratorDeclarationParameters(DeclarationParameters* declarationParameters, int treeIndex) {
    LogDebug("Generating DeclarationParameters");
    // Por default las declaration se hacen sobre el tipo BST. La operación será obviamente, addNode
    GeneratorIntegerParameters(declarationParameters->integerParameters, treeIndex, ADD_NODE_SENTENCE, BST_TYPE);
}

void GeneratorIntegerParameters(IntegerParameters* integerParameters, int treeIndex, TreeSentenceType sentenceType, TreeType treeType) {
    LogDebug("Generating IntegerParameters");
    GeneratorIntegerArray(integerParameters->integerArray, treeIndex, sentenceType, treeType);
}

void GeneratorIntegerArray(IntegerArray* integerArray, int treeIndex, TreeSentenceType sentenceType, TreeType treeType) {
    LogDebug("Generating IntegerArray");
    switch (integerArray->type) {
        case ONE_INTEGER:
            GeneratorInteger(integerArray->value, treeIndex, sentenceType, treeType);
            break;
        case VARIOUS_INTEGER:
            GeneratorInteger(integerArray->value, treeIndex, sentenceType, treeType);
            GeneratorIntegerArray(integerArray->nextIntegerArray, treeIndex, sentenceType, treeType);
            break;
        default:
            break;
    }
}

void GeneratorBlock(Block* block) {
    LogDebug("Generating Block");
    int treeIndex;
    switch (block->type) {
        case CONFIGURE_BLOCK:
            // Guardo el treeType y el index asociado al nombre para pasar a las funciones siguientes
            treeIndex = GeneratorTreeName(block->treeName);
            GeneratorConfigureBlock(block->configureBlock, treeIndex, GeneratorTreeType(block->treeType, treeIndex));
            break;
        case CREATE_BLOCK:
            // Guardo el nombre del archivo
            GeneratorFileName(block->fileName);
            // Guardo los distintos parámetros que se hayan mandado en el bloque create
            GeneratorCreateBlock(block->createBlock);

            // Guardo el nombre de archivo completo donde se guardará el .dot
            generateDotFullPathName();

            // Hago un fopen de dicho fileName, al que le voy a escribir el archivo .dot
            outputFile = fopen(currentFile->fullPathName, "w+");

            // En caso de error, libero los recursos utilizados hasta el momento
            if (outputFile == NULL) {
                LogError("Error abriendo archivo .dot\n");
                free(currentFile->fullPathName);
                free(currentFile);
                programSuccess = 2;
                return;
            }

            // Genero el archivo dot y lo guardo en el FILE* outputFile
            generateDotFile(currentFile->currentTrees, currentFile->treeNames, currentFile->treeSize, currentFile->legendParams, outputFile);

            fclose(outputFile);

            // Si no había ningún árbol, informo el warning
            if (currentFile->treeSize == 0) {
                LogWarn("No se agregaron arboles. El archivo %s se ha generado vacio.", currentFile->name);
                programSuccess = programSuccess==0 ? 1:programSuccess;
            }

            // Creo el comando que transformará en foto el archivo .dot
            generateCommand();

            LogInfo("Se ha corrido el comando: %s", currentFile->command);

            // Corro el comando command, en caso de error, logueo
            if (system(currentFile->command) == -1) {
                LogError("Se produjo un error al correr el comando %s", currentFile->command);
                free(currentFile->command);
                free(currentFile);
                programSuccess = 2;
                return;
            }

            free(currentFile->command);
            free(currentFile);
            resetFoundNodes();

            break;
        default:
            break;
    }
}

void GeneratorConfigureBlock(ConfigureBlock* configureBlock, int treeIndex, TreeType treeType) {
    LogDebug("Generating ConfigureBlock");
    // Hago el cambio de type de ser necesario antes de empezar a ejecutar las sentencias
    // Si el tipo fuera el mismo, no se hace más que devolver la misma root
    myGeneratorState->currentTrees[treeIndex] = switchType(myGeneratorState->currentTrees[treeIndex], treeType, &programSuccess);
    GeneratorTreeSentences(configureBlock->treeSentences, treeIndex, treeType);
}

void GeneratorTreeSentences(TreeSentences* treeSentences, int treeIndex, TreeType treeType) {
    LogDebug("Generating TreeSentences");
    switch (treeSentences->type) {
        case ONE_TREE_SENTENCE:
            GeneratorTreeSentence(treeSentences->treeSentence, treeIndex, treeType);
            break;
        case VARIOUS_TREE_SENTENCES:
            GeneratorTreeSentence(treeSentences->treeSentence, treeIndex, treeType);
            GeneratorTreeSentences(treeSentences->nextTreeSentences, treeIndex, treeType);
            break;
        default:
            break;
    }
}

void GeneratorTreeSentence(TreeSentence* treeSentence, int treeIndex, TreeType treeType) {
    LogDebug("Generating TreeSentence");
    switch (treeSentence->type) {
        case ADD_NODE_SENTENCE:
            // Voy al arbol que haga falta y le inserto el nodo
            // Si ya existía el nodo, tira un warning 
            GeneratorIntegerParameters(treeSentence->integerParameters, treeIndex, ADD_NODE_SENTENCE, treeType);
            break;
        case DELETE_NODE_SENTENCE:
            // Voy al arbol que haga falta y le borro el nodo
            // Si no existía el nodo, tira un warning
            GeneratorIntegerParameters(treeSentence->integerParameters, treeIndex, DELETE_NODE_SENTENCE, treeType);
            break;
        case FIND_NODE_SENTENCE:
            // Voy al arbol que haga falta y le seteo al nodo found=true
            // Si no existía el nodo, no hago nada y sigo
            GeneratorIntegerParameters(treeSentence->integerParameters, treeIndex, FIND_NODE_SENTENCE, treeType);
            break;
        default:
            break;
    }
}

void GeneratorCreateBlock(CreateBlock* createBlock) {
    LogDebug("Generating CreateBlock");
    GeneratorFileSentences(createBlock->fileSentences);
}

void GeneratorFileSentences(FileSentences* fileSentences) {
    LogDebug("Generating FileSentences");
    switch (fileSentences->type) {
        case ONE_FILE_SENTENCE:
            GeneratorFileSentence(fileSentences->fileSentence);
            break;
        case VARIOUS_FILE_SENTENCES:
            GeneratorFileSentence(fileSentences->fileSentence);
            GeneratorFileSentences(fileSentences->nextFileSentences);
            break;
        default:
            break;
    }
}

void GeneratorFileSentence(FileSentence* fileSentence) {
    LogDebug("Generating FileSentence");
    switch (fileSentence->type) {
        case ADD_TREE_SENTENCE:
            // Voy al arbol y lo agrego al archivo
            GeneratorTreeParameters(fileSentence->treeParameters);
            break;
        case ADD_FILE_PATH_SENTENCE:
            // Agrego al struct el filepath
            GeneratorFileParameter(fileSentence->fileParameter);
            break;
        case ADD_LEGEND_SENTENCE:
            // Agrego a un arreglo de legend parameters el que me pasen
            GeneratorLegendParameters(fileSentence->legendParameters);
            break;
        default:
            break;
    }
}

void GeneratorTreeParameters(TreeParameters* treeParameters) {
    LogDebug("Generating TreeParameters");
    GeneratorTreeArray(treeParameters->treeArray);
}

void GeneratorTreeArray(TreeArray* treeArray) {
    LogDebug("Generating TreeArray");
    switch (treeArray->type) {
        case ONE_TREE:
            // Agrego nombre del árbol y root en la struct currentFile
            currentFile->treeNames[currentFile->treeSize] = treeArray->treeName;
            currentFile->currentTrees[currentFile->treeSize++] = myGeneratorState->currentTrees[GeneratorTreeName(treeArray->treeName)];
            break;
        case VARIOUS_TREES:
            // Agrego nombre del árbol y root en la struct currentFile
            // Me desplazo al siguiente y sigo agregando árboles
            currentFile->treeNames[currentFile->treeSize] = treeArray->treeName;
            currentFile->currentTrees[currentFile->treeSize++] = myGeneratorState->currentTrees[GeneratorTreeName(treeArray->treeName)];
            GeneratorTreeArray(treeArray->nextTreeArray);
            break;
        default:
            break;
    }
}

void GeneratorFileParameter(FileParameter* fileParameter) {
    LogDebug("Generating FileParameter");
    GeneratorFilePath(fileParameter->filePath);
}

void GeneratorLegendParameters(LegendParameters* legendParameters) {
    LogDebug("Generating LegendParameters");
    GeneratorLegendArray(legendParameters->legendArray);
}

void GeneratorLegendArray(LegendArray* legendArray) {
    LogDebug("Generating LegendArray");
    switch (legendArray->type) {
        case ONE_LEGEND:
            GeneratorLegendType(legendArray->legendType);
            break;
        case VARIOUS_LEGENDS:
            GeneratorLegendType(legendArray->legendType);
            GeneratorLegendArray(legendArray->nextLegendArray);
            break;
        default:
            break;
    }
}

void GeneratorInteger(int value, int treeIndex, TreeSentenceType sentenceType, TreeType treeType) {
    LogDebug("Generating Integer leaf");
    switch (sentenceType) {
        case ADD_NODE_SENTENCE:
            // Recibo por parámetro el treeType siempre, porque puede llegar a ser la primer inserción y necesitarlo
            if (myGeneratorState->currentTrees[treeIndex] == NULL) {
                myGeneratorState->currentTrees[treeIndex] = insertFirstNode(myGeneratorState->currentTrees[treeIndex], value, treeType, &programSuccess);
            } else {
                myGeneratorState->currentTrees[treeIndex] = insertNode(myGeneratorState->currentTrees[treeIndex], value, &programSuccess);
            }
            break;
        case DELETE_NODE_SENTENCE:
            myGeneratorState->currentTrees[treeIndex] = deleteNode(myGeneratorState->currentTrees[treeIndex], value, &programSuccess);
            break;
        case FIND_NODE_SENTENCE:
            findNode(myGeneratorState->currentTrees[treeIndex], value);
            break;
        default:
            break;
    }
}

TreeType GeneratorTreeType(TreeTypeStruct* type, int treeIndex) {
    LogDebug("Generating TreeType leaf");
    // Si tengo un treeType distinto de empty, lo devuelvo directamente
    // porque quiere decir que quiero cambiar el tipo de arbol
    if (type->treeType != NO_TYPE) {
        LogDebug("Handled != no type");
        return type->treeType;
    }

    // Sino, me fijo si en esa posición había un árbol y devuelvo su tipo
    if (myGeneratorState->currentTrees[treeIndex] != NULL) {
        LogDebug("Handled previous tree type");
        return myGeneratorState->currentTrees[treeIndex]->type;
    }

    LogDebug("Handled default tree type");
    // Si no había un árbol y estaba vacío, devuelvo BST_TYPE como default
    return BST_TYPE;
}

void GeneratorLegendType(LegendTypeStruct* type) {
    LogDebug("Generating LegendType leaf");
    int alreadyAdded = 0;
    for (int i = 0; i < LEGEND_TYPES && !alreadyAdded; i++) {
        // Si todavía no estaba, agrego
        if (currentFile->legendParams[i] == NONE) {
            currentFile->legendParams[i] = type->legendType;
            alreadyAdded = 1;
        }
        // Si ya se agregó, ignoro y tiro un warning
        else if (currentFile->legendParams[i] == type->legendType) {
            LogWarn("Legend %s ya agregado", legendNames[i]);
            programSuccess = programSuccess==0 ? 1:programSuccess;
            alreadyAdded = 1;
        }
    }
}

int GeneratorTreeName(char* treeName) {
    LogDebug("Generating TreeName leaf");
    return findTreeIndexByName(treeName);
}

void GeneratorFileName(char* fileName) {
    LogDebug("Generating FileName leaf");

    // Reservo memoria para la estructura de currentFile y luego inicializo sus campos
    currentFile = (struct FileWithName*)calloc(1, sizeof(struct FileWithName));

    if (currentFile == NULL) {
        LogError("El programa finalizo abruptamente debido a que ya no hay memoria disponible");
        programSuccess = 2;
        return;
    }

    currentFile->filePath = NULL;
    currentFile->fullPathName = NULL;
    currentFile->command = NULL;
    currentFile->name = fileName;

    for (int i = 0; i < LEGEND_TYPES; i++) {
        currentFile->legendParams[i] = NONE;
    }
}

void GeneratorFilePath(char* FilePath) {
    LogDebug("Generating FilePath leaf");
    currentFile->filePath = FilePath;
}

void freeGeneratorState() {
    for (int i = 0; i < myGeneratorState->size; i++) {
        freeTree(myGeneratorState->currentTrees[i]);
    }
}

static int findTreeIndexByName(char* treeName) {
    for (int i = 0; i < myGeneratorState->size; i++) {
        if (strcmp(treeName, myGeneratorState->treeNames[i]) == 0) {
            return i;
        }
    }
    // No debería llegar nunca porque handlea la tabla de simbolos, pero se deja por completitud
    return -1;
}

static void resetFoundNodes() {
    for (int i = 0; i < currentFile->treeSize; i++) {
        resetFindNode(currentFile->currentTrees[i]);
    }
}

static void generateDotFullPathName() {
    // Genero el path completo del archivo .dot a abrir
    char* dotAux = ".dot";
    char* noFilePathAux = "./";

    if (currentFile->filePath == NULL) {
        currentFile->fullPathName = calloc(strlen(noFilePathAux) + strlen(currentFile->name) + strlen(dotAux) + 1, sizeof(char));

        if (currentFile->fullPathName == NULL) {
            LogError("El programa finalizo abruptamente debido a que ya no hay memoria disponible");
            programSuccess = 2;
            return;
        }

        strcat(currentFile->fullPathName, noFilePathAux);
        strcat(currentFile->fullPathName, currentFile->name);
        strcat(currentFile->fullPathName, dotAux);
    } else {
        currentFile->fullPathName = calloc(strlen(currentFile->filePath) + strlen(currentFile->name) + strlen(dotAux) + 1, sizeof(char));

        if (currentFile->fullPathName == NULL) {
            LogError("El programa finalizo abruptamente debido a que ya no hay memoria disponible");
            programSuccess = 2;
            return;
        }

        strcat(currentFile->fullPathName, currentFile->filePath);
        strcat(currentFile->fullPathName, currentFile->name);
        strcat(currentFile->fullPathName, dotAux);
    }
}

static void generateCommand() {
    // Genero el comando a ejecutar para crear el png

    char* dotCommandAux = "dot -Tpng ";
    char* outAux = " -o ";
    int fullPathNameSize = strlen(currentFile->fullPathName);

    currentFile->command = calloc(strlen(dotCommandAux) + 2 * fullPathNameSize + strlen(outAux) + 1, sizeof(char));

    if (currentFile->command == NULL) {
        LogError("El programa finalizo abruptamente debido a que ya no hay memoria disponible");
        programSuccess = 2;
        return;
    }

    strcat(currentFile->command, dotCommandAux);
    strcat(currentFile->command, currentFile->fullPathName);
    strcat(currentFile->command, outAux);

    currentFile->fullPathName[fullPathNameSize - 1] = 'g';
    currentFile->fullPathName[fullPathNameSize - 2] = 'n';
    currentFile->fullPathName[fullPathNameSize - 3] = 'p';

    strcat(currentFile->command, currentFile->fullPathName);

    free(currentFile->fullPathName);
}
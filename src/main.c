#include "backend/code-generation/generator.h"
#include "backend/semantic-analysis/abstract-syntax-tree.h"
#include "backend/semantic-analysis/symbol-table.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "backend/support/free_ast.h"
#include "frontend/syntactic-analysis/bison-actions.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include <stdio.h>

#define MAX_COMMAND 1024

// Estado de la aplicación.
CompilerState state;
FILE* out;
int yyparse();

// Punto de entrada principal del compilador.
const int main(const int argumentCount, const char** arguments) {
    // Inicializar estado de la aplicación.
    // state es una variable global que almacena el estado del compilador
    state.program = NULL;
    state.result = 0;
    state.succeed = false;

    // Mostrar parámetros recibidos por consola.
    for (int i = 0; i < argumentCount; ++i) {
        LogInfo("Argumento %d: '%s'", i, arguments[i]);
    }

    // Compilar el programa de entrada.
    LogInfo("Compilando...\n");
    initialize_st();
    const int result = yyparse();
    switch (result) {
        case 0:
            if (state.succeed) {
                switch (Generator(state.program)) {
                    case 0:
                        LogInfo("La compilacion fue exitosa.");
                        break;
                    case 1:
                        LogInfo("La compilacion se realizo con warnings.");
                        break;
                    case 2:
                        LogInfo("La compilacion encontro uno o más errores.");
                        break;
                    default:
                        break;
                }
            } else {
                LogError("Se produjo un error en la aplicacion.");
                free_st();
                return -1;
            }
            break;
        case 1:
            LogError("Bison finalizo debido a un error de sintaxis.");
            break;
        case 2:
            LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
            break;
        default:
            LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
    }
    LogInfo("Fin.");
    freeGeneratorState();
    free_st();
    freeProgram(state.program);
    return result;
}

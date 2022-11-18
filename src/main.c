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
                char to_write_commands[MAX_COMMAND];
                // Creamos el archivo .dot
                out = fopen("./a.dot", "w+");
                if (out == NULL) {
                    perror("Se produjo un error en la aplicacion.");
                    free_st();
                    exit(EXIT_FAILURE);
                }

                fprintf(out, "strict graph {\n");
                Generator(state.program, out);
                fprintf(out, "}");
                fclose(out);

                sprintf(to_write_commands, "dot -Tsvg a.dot -o foto.svg");
                if (system(to_write_commands) == -1) {
                    LogError("Se produjo un error en la aplicacion.");
                    free_st();
                    freeProgram(state.program);
                    return -1;
                }

                LogInfo("La compilacion fue exitosa.");
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
    free_st();
    freeProgram(state.program);
    return result;
}

#include "flex-actions.h"
#include "../../backend/support/logger.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */

void BeginCommentPatternAction() {
    LogDebug("BeginCommentPatternAction.");
}

void EndCommentPatternAction() {
    LogDebug("EndCommentPatternAction.");
}

token IntegerPatternAction(const char* lexeme, const int length) {
    LogDebug("IntegerPatternAction: '%s' (length = %d).", lexeme, length);
    char* integer = (char*)calloc(length + 1, sizeof(char));
    strncpy(integer, lexeme, length);
    yylval.integer = atoi(integer);
    free(integer);     //TODO chequear si hay que hacer este free
    return INTEGER;
}

token VariableNamePatternAction(const char* lexeme, const int length) {
    LogDebug("VariableNamePatternAction: '%s' (length = %d).", lexeme, length);
    char* variableName = (char*)calloc(length + 1, sizeof(char));
    strncpy(variableName, lexeme, length);
    yylval.string = variableName;
    free(variableName);     //TODO chequear si hay que hacer este free
    return VARIABLE_NAME;
}

token FilePathPatternAction(const char* lexeme, const int length) {
    LogDebug("FilePathPatternAction: '%s' (length = %d).", lexeme, length);
    char* filePath = (char*)calloc(length + 1, sizeof(char));
    strncpy(filePath, lexeme, length);
    yylval.string = filePath;
    free(filePath);     //TODO chequear si hay que hacer este free
    return FILE_PATH;
}

void IgnoredPatternAction(const char* lexeme, const int length) {
    LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
    // Como no debe hacer nada con el patrón, solo se loguea en consola.
}

token UnknownPatternAction(const char* lexeme, const int length) {
    LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
    // TODO esto originalmente tenia el valor YYUNDEF
    // Al emitir este token, el compilador aborta la ejecución.
    yylval.token = UNKNOWN;
    return UNKNOWN;
}
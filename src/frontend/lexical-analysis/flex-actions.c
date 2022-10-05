#include "../../backend/support/logger.h"
#include "flex-actions.h"
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

token TreePatternAction(const char * lexeme){
	LogDebug("TreePatternAction: '%s'.", lexeme);
	yylval.token = TREE;
	return TREE;
}

token ConfigurePatternAction(const char * lexeme){
	LogDebug("ConfigurePatternAction: '%s'.", lexeme);
	yylval.token = CONFIGURE;
	return CONFIGURE;
}

token CreatePatternAction(const char * lexeme){
	LogDebug("CreatePatternAction: '%s'.", lexeme);
	yylval.token = CREATE;
	return CREATE;
}

token AddNodePatternAction(const char * lexeme){
	LogDebug("AddNodePatternAction: '%s'.", lexeme);
	yylval.token = ADD_NODE;
	return ADD_NODE;
}

token DeleteNodePatternAction(const char * lexeme){
	LogDebug("DeleteNodePatternAction: '%s'.", lexeme);
	yylval.token = DELETE_NODE;
	return DELETE_NODE;
}

token FindNodePatternAction(const char * lexeme){
	LogDebug("FindNodePatternAction: '%s'.", lexeme);
	yylval.token = FIND_NODE;
	return FIND_NODE;
}

token AddTreePatternAction(const char * lexeme){
	LogDebug("AddTreePatternAction: '%s'.", lexeme);
	yylval.token = ADD_TREE;
	return ADD_TREE;
}

token AddPathPatternAction(const char * lexeme){
	LogDebug("AddPathPatternAction: '%s'.", lexeme);
	yylval.token = ADD_SAVE_PATH;
	return ADD_SAVE_PATH;
}

token AddLegendPatternAction(const char * lexeme){
	LogDebug("AddLegendPatternAction: '%s'.", lexeme);
	yylval.token = ADD_LEGEND;
	return ADD_LEGEND;
}

token BstPatternAction(const char * lexeme){
	LogDebug("BstPatternAction: '%s'.", lexeme);
	yylval.token = BST;
	return BST;
}

token AvlPatternAction(const char * lexeme){
	LogDebug("AvlPatternAction: '%s'.", lexeme);
	yylval.token = AVL;
	return AVL;
}

token RbtPatternAction(const char * lexeme){
	LogDebug("RbtPatternAction: '%s'.", lexeme);
	yylval.token = RBT;
	return RBT;
}

token MaxPatternAction(const char * lexeme){
	LogDebug("MaxPatternAction: '%s'.", lexeme);
	yylval.token = MAX;
	return MAX;
}

token MinPatternAction(const char * lexeme){
	LogDebug("MinPatternAction: '%s'.", lexeme);
	yylval.token = MIN;
	return MIN;
}

token CountPatternAction(const char * lexeme){
	LogDebug("CountPatternAction: '%s'.", lexeme);
	yylval.token = COUNT;
	return COUNT;
}

token HeightPatternAction(const char * lexeme){
	LogDebug("HeightPatternAction: '%s'.", lexeme);
	yylval.token = HEIGHT;
	return HEIGHT;
}

token BalancedPatternAction(const char * lexeme){
	LogDebug("BalancedPatternAction: '%s'.", lexeme);
	yylval.token = BALANCED;
	return BALANCED;
}

token OpenBlockPatternAction(const char * lexeme){
	LogDebug("OpenBlockPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_CURLY;
	return OPEN_CURLY;
}

token CloseBlockPatternAction(const char * lexeme){
	LogDebug("CloseBlockPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_CURLY;
	return CLOSE_CURLY;
}

token OpenParenthesisPatternAction(const char * lexeme) {
	LogDebug("OpenParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_PARENTHESIS;
	return OPEN_PARENTHESIS;
}

token CloseParenthesisPatternAction(const char * lexeme) {
	LogDebug("CloseParenthesisPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_PARENTHESIS;
	return CLOSE_PARENTHESIS;
}

token CommaPatternAction(const char * lexeme){
	LogDebug("SemiColonPatternAction: '%s'", lexeme);
	yylval.token = COMMA;
	return COMMA;
}

token SemiColonPatternAction(const char * lexeme){
	LogDebug("SemiColonPatternAction: '%s'", lexeme);
	yylval.token = SEMICOLON;
	return SEMICOLON;
}

token IntegerPatternAction(const char * lexeme, const int length) {
	LogDebug("IntegerPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = INTEGER;
	return INTEGER;
}

token VariableNamePatternAction(const char * lexeme, const int length){
	LogDebug("VariableNamePatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = VARIABLE_NAME;
	return VARIABLE_NAME;
}

token FilePathPatternAction(const char * lexeme, const int length){
	LogDebug("FilePathPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = FILE_PATH;
	return FILE_PATH;
}


void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}


token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
	//TODO esto originalmente tenia otro valor
	yylval.token = 2;
	// Al emitir este token, el compilador aborta la ejecución.
	return 2;
}
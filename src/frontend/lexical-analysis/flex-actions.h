#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 *
 * Debería existir una acción por cada patrón disponible en Flex (es decir,
 * por cada regla).
 *
 * Solo aquellas acciones que tengan interés en conocer el largo del lexema
 * emplean el parámetro adicional "length". Esto es útil cuando se desea
 * asignar memoria dinámica, y por lo tanto, se debe saber exactamente el
 * largo de aquello que se va a almacenar.
 */

// Bloque de comentarios multilínea.
void BeginCommentPatternAction();
void EndCommentPatternAction();

token TreePatternAction(const char * lexeme);
token ConfigurePatternAction(const char * lexeme);
token CreatePatternAction(const char * lexeme);
token AddNodePatternAction(const char * lexeme);
token DeleteNodePatternAction(const char * lexeme);
token FindNodePatternAction(const char * lexeme);
token AddTreePatternAction(const char * lexeme);
token AddFilePathPatternAction(const char * lexeme);
token AddLegendPatternAction(const char * lexeme);
token BstPatternAction(const char * lexeme);
token AvlPatternAction(const char * lexeme);
token RbtPatternAction(const char * lexeme);
token MaxPatternAction(const char * lexeme);
token MinPatternAction(const char * lexeme);
token CountPatternAction(const char * lexeme);
token HeightPatternAction(const char * lexeme);
token BalancedPatternAction(const char * lexeme);
token OpenBlockPatternAction(const char * lexeme);
token CloseBlockPatternAction(const char * lexeme);
token OpenParenthesisPatternAction(const char * lexeme);
token CloseParenthesisPatternAction(const char * lexeme);
token CommaPatternAction(const char * lexeme);
token SemiColonPatternAction(const char * lexeme);
token IntegerPatternAction(const char * lexeme, const int length);
token VariableNamePatternAction(const char * lexeme, const int length);
token FilePathPatternAction(const char * lexeme, const int length);

// Regla que no hace nada, permite ignorar parte de la entrada.
void IgnoredPatternAction(const char * lexeme, const int length);

// Patrón desconocido, permite abortar debido a un error de sintaxis.
token UnknownPatternAction(const char * lexeme, const int length);

#endif

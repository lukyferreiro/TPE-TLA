%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x COMMENT

/* Patrones reutilizables. */
/* https://www.regextester.com/115652 */
variableName    [A-Za-z][A-Za-z0-9]*
/* TODO 
/* El patrón para filePath es muy restrictivo, deberían usar un contexto */
/* de Flex similar al que utilizarían para manipular strings o comentarios, */
/* y así evitar colisiones o solapamientos con otras secciones del programa. */
/* filePath        ([/]{1}[a-z0-9.]+)+(\/?){1}$|^([\/]{1}) */
/* filePath        [A-Za-z/]* */
digit			[0-9]
endline			[\n]
whitespace		[ \f\n\r\t\v]

%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }


"tree"                                      { return TreePatternAction(yytext); }
"configure"                                 { return ConfigurePatternAction(yytext); }
"create"                                    { return CreatePatternAction(yytext); }

"addNode"                                   { return AddNodePatternAction(yytext); }
"deleteNode"                                { return DeleteNodePatternAction(yytext); }
"findNode"                                  { return FindNodePatternAction(yytext); }

"addTree"                                   { return AddTreePatternAction(yytext); }
"addFilePath"                               { return AddFilePathPatternAction(yytext); }
"addLegend"                                 { return AddLegendPatternAction(yytext); }

"bst"                                       { return BstPatternAction(yytext); }
"avl"                                       { return AvlPatternAction(yytext); }
"rbt"                                       { return RbtPatternAction(yytext); }

"max"                                       { return MaxPatternAction(yytext); }
"min"                                       { return MinPatternAction(yytext); }
"count"                                     { return CountPatternAction(yytext); }
"height"                                    { return HeightPatternAction(yytext); }
"balanced"                                  { return BalancedPatternAction(yytext); }

"{"                                         { return OpenBlockPatternAction(yytext); }
"}"                                         { return CloseBlockPatternAction(yytext); }
"("                                         { return OpenParenthesisPatternAction(yytext); }
")"                                         { return CloseParenthesisPatternAction(yytext); }

","                                         { return CommaPatternAction(yytext); }
";"                                         { return SemiColonPatternAction(yytext); }

{digit}+									{ return IntegerPatternAction(yytext, yyleng); }

{variableName}                              { return VariableNamePatternAction(yytext, yyleng); }
([/]{1}[a-z0-9.]+)+(\/?){1}$|^([\/]{1})     { return FilePathPatternAction(yytext, yyleng); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }
{endline}                                   { IgnoredPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%

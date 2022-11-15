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
%x CONTEXT_FILE_PATH

/* Patrones reutilizables. */
/* https://www.regextester.com/115652 */
variableName    [A-Za-z][A-Za-z0-9]*
/* TODO 
/* El patrón para filePath es muy restrictivo, deberían usar un contexto */
/* de Flex similar al que utilizarían para manipular strings o comentarios, */
/* y así evitar colisiones o solapamientos con otras secciones del programa. */
/* filePath        ([/]{1}[a-z0-9.]+)+(\/?){1}$|^([\/]{1}) */
filePath        (([/]{1}[A-Za-z0-9_-]+)+([/]?){1})|(^([\/]{1}))
digit			[0-9]
endline			[\n]
whitespace		[ \f\n\r\t\v]

%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"\""								        { BEGIN(CONTEXT_FILE_PATH); BeginContextFilePathPatternAction(); }
<CONTEXT_FILE_PATH>{filePath}	            { return FilePathPatternAction(yytext, yyleng); }
<CONTEXT_FILE_PATH>"\""						{ EndContextFilePathPatternAction(); BEGIN(INITIAL); }


"tree"                                      { yylval.token = TREE; return TREE; }
"configure"                                 { yylval.token = CONFIGURE; return CONFIGURE; }
"create"                                    { yylval.token = CREATE; return CREATE; }

"addNode"                                   { yylval.token = ADD_NODE; return ADD_NODE; }
"deleteNode"                                { yylval.token = DELETE_NODE; return DELETE_NODE; }
"findNode"                                  { yylval.token = FIND_NODE; return FIND_NODE; }

"addTree"                                   { yylval.token = ADD_TREE; return ADD_TREE; }
"addFilePath"                               { yylval.token = ADD_FILE_PATH; return ADD_FILE_PATH; }
"addLegend"                                 { yylval.token = ADD_LEGEND; return ADD_LEGEND; }

"bst"                                       { yylval.token = BST; return BST; }
"avl"                                       { yylval.token = AVL; return AVL; }
"rbt"                                       { yylval.token = RBT; return RBT; }

"max"                                       { yylval.token = MAX; return MAX; }
"min"                                       { yylval.token = MIN; return MIN; }
"count"                                     { yylval.token = COUNT; return COUNT; }
"height"                                    { yylval.token = HEIGHT; return HEIGHT; }
"balanced"                                  { yylval.token = BALANCED; return BALANCED; }

"{"                                         { return OPEN_CURLY; }
"}"                                         { return CLOSE_CURLY; }
"("                                         { return OPEN_PARENTHESIS; }
")"                                         { return CLOSE_PARENTHESIS; }

","                                         { return COMMA; }
";"                                         { return SEMICOLON; }

{digit}+									{ return IntegerPatternAction(yytext, yyleng); }

{variableName}                              { return VariableNamePatternAction(yytext, yyleng); }

{whitespace}+								{ IgnoredPatternAction(yytext, yyleng); }
{endline}                                   { IgnoredPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%

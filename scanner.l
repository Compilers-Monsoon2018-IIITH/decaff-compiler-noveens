%{
# include "parser.tab.h"
%}

%%

"class" 					{ printf("%s", yytext); return CLASS; }
"Program" 					{ printf("%s", yytext); return PROG; }
"{" 						{ printf("%s", yytext); return LEFT_CURLY; }
"}" 						{ printf("%s", yytext); return RIGHT_CURLY; }
"[" 						{ printf("%s", yytext); return LEFT_SQUARE; }
"]" 						{ printf("%s", yytext); return RIGHT_SQUARE; }
"(" 						{ printf("%s", yytext); return LEFT_ROUND; }
")" 						{ printf("%s", yytext); return RIGHT_ROUND; }
"void" 						{ printf("%s", yytext); return VOID; }
"int" 						{ printf("%s", yytext); return INT; }
"boolean" 					{ printf("%s", yytext); return BOOL; }
"if" 						{ printf("%s", yytext); return IF; }
"else" 						{ printf("%s", yytext); return ELSE; }
"for" 						{ printf("%s", yytext); return FOR; }
"return" 					{ printf("%s", yytext); return RET; }
"break" 					{ printf("%s", yytext); return BREAK; }
"continue" 					{ printf("%s", yytext); return CONT; }
"!" 						{ printf("%s", yytext); return NOT; }
"+" 						{ printf("%s", yytext); return PLUS; }
"-" 						{ printf("%s", yytext); return MINUS; }
"*" 						{ printf("%s", yytext); return MUL; }
"/" 						{ printf("%s", yytext); return DIV; }
"%" 						{ printf("%s", yytext); return MOD; }
"=" 						{ printf("%s", yytext); return EQ; }
"-=" 						{ printf("%s", yytext); return MINEQ; }
"+=" 						{ printf("%s", yytext); return PLUSEQ; }
"callout" 					{ printf("%s", yytext); return CALLOUT; }
">" 						{ printf("%s", yytext); return GT; }
"<" 						{ printf("%s", yytext); return LT; }
">=" 						{ printf("%s", yytext); return GE; }
"<=" 						{ printf("%s", yytext); return LE; }
"==" 						{ printf("%s", yytext); return EQEQ; }
"!=" 						{ printf("%s", yytext); return NEQ; }
"&&" 						{ printf("%s", yytext); return ANDAND; }
"||" 						{ printf("%s", yytext); return OROR; }
"true" 						{ printf("%s", yytext); return TRUE; }
"false" 					{ printf("%s", yytext); return FALSE; }
"'" 						{ printf("%s", yytext); return SQUOT; }
"\"" 						{ printf("%s", yytext); return DQUOT; }
"," 						{ printf("%s", yytext); return COMMA; }
";" 						{ printf("%s", yytext); return SEMICOLON; }
"_" 						{ printf("%s", yytext); return UNDERSCORE; }
"\t" 						{ printf("\t"); }
"\n" 						{ printf("\n"); }
" " 						{ printf(" "); }
(0x)[0-9a-fA-F]+ 			{ printf("%s", yytext); return REGEX_HEX;}
[a-zA-Z_][a-zA-Z_0-9]* 		{ printf("%s", yytext); return REGEX_ID;}
[0-9][0-9]* 				{ printf("%s", yytext);  return REGEX_DECIMAL; }
[ -~] 						{ printf("CHAR %s", yytext); return CHAR; } /* FIX THIS */

%%

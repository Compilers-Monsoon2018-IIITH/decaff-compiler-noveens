%{
# include "bits/stdc++.h"
# include "class_definition.h"
# include "parser.tab.h"
# define YY_DECL extern "C" int yylex()
extern union Node yylval;
using namespace std;

void yyerror (char const *s) {
	fprintf (stderr, "%s at statement -> %d\nNot parsed completely\n", s,yylineno);
}

%}

%%

"class"                     { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return CLASS; }
"Program"                   { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return PROG; }
"{"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return LEFT_CURLY; }
"}"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return RIGHT_CURLY; }
"["                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return LEFT_SQUARE; }
"]"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return RIGHT_SQUARE; }
"("                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return LEFT_ROUND; }
")"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return RIGHT_ROUND; }
"void"                      { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return VOID; }
"int"                       { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return INT; }
"boolean"                   { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return BOOL; }
"if"                        { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return IF; }
"else"                      { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return ELSE; }
"for"                       { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return FOR; }
"return"                    { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return RET; }
"break"                     { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return BREAK; }
"continue"                  { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return CONT; }
"!"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return NOT; }
"+"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return PLUS; }
"-"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return MINUS; }
"*"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return MUL; }
"/"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return DIV; }
"%"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return MOD; }
"="                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return EQ; }
"-="                        { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return MINEQ; }
"+="                        { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return PLUSEQ; }
"callout"                   { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return CALLOUT; }
">"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return GT; }
"<"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return LT; }
">="                        { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return GE; }
"<="                        { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return LE; }
"=="                        { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return EQEQ; }
"!="                        { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return NEQ; }
"&&"                        { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return ANDAND; }
"||"                        { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return OROR; }
"true"                      { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return TRUE; }
"false"                     { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return FALSE; }
","                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return COMMA; }
";"                         { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return SEMICOLON; }
"\t"                        { printf("\t"); }
"\n"                        { printf("\n"); }
" "                         { printf(" "); }
(0x)[0-9a-fA-F]+            { printf("%s", yytext); yylval.num = strtol(yytext, 0, 16); return REGEX_HEX; }
[a-zA-Z_][a-zA-Z_0-9]*      { printf("%s", yytext); yylval.lit = new string(yytext, yyleng); return REGEX_ID; }
[0-9][0-9]*                 { printf("%s", yytext); yylval.num = strtol(yytext, 0, 10);  return REGEX_DECIMAL; }
^\'[ -~]\'$                 { printf("CHAR %s", yytext); yylval.lit = new string(yytext, yyleng); return REGEX_CHAR; } /* FIX THIS */
^\"[ -~]*\"$                { printf("STRING_LIT %s", yytext); yylval.lit = new string(yytext, yyleng); return REGEX_STRING; } /* FIX THIS */

%%

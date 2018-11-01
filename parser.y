%{
#include <stdio.h>
int yylex();
int yyerror();
%}

%start program

%token PROG
%token CLASS
%token LEFT_CURLY
%token RIGHT_CURLY
%token LEFT_SQUARE
%token RIGHT_SQUARE
%token LEFT_ROUND
%token RIGHT_ROUND
%token VOID
%token INT
%token BOOL
%token IF
%token ELSE
%token FOR
%token RET
%token BREAK
%token CONT
%token NOT
%token PLUS
%token MINUS
%token MUL
%token DIV
%token MOD
%token EQ
%token MINEQ
%token PLUSEQ
%token CALLOUT
%token GT
%token LT
%token GE
%token LE
%token EQEQ
%token NEQ
%token ANDAND
%token OROR
%token HEX
%token ALPHA
%token DIGIT
%token TRUE
%token FALSE
%token SQUOT
%token DQUOT
%token COMMA
%token SEMICOLON
%token CHAR
%token UNDERSCORE
%token REGEX_HEX
%token REGEX_ID
%token REGEX_DECIMAL

%%

program: CLASS PROG LEFT_CURLY field_decl method_decl RIGHT_CURLY							{ $$ = new Program($4, $5); }
	;

field_decl: 																				{ $$ = new FieldDeclList(); }
	| field_decl field_decls																{ $$->push_back($2); }
	;

method_decl: 																				{ $$ = new MethodDeclList(); }
	| method_decl method_decls																{ $$->push_back($2); }
	;

field_decls: type follow id SEMICOLON														{ $$->push_back($3); }
	| type follow id LEFT_SQUARE int_literal RIGHT_SQUARE SEMICOLON							{ $$->push_back($3, $5); }
	;

follow:																						{ $$ = new VariableList(); }
	| follow id COMMA																		{ $$->push_back($2); }
	| follow id LEFT_SQUARE int_literal RIGHT_SQUARE COMMA									{ $$->push_back($2, $4); }
	;

method_decls: type id LEFT_ROUND RIGHT_ROUND block											{ $$ = new MethodDecl(); $$->pb($1, $2) }
	| type id LEFT_ROUND param type id RIGHT_ROUND block									{ $$ = new MethodDecl(); $4->add_arg($5, $6); $$->params = $4; }
	| VOID id LEFT_ROUND RIGHT_ROUND block													{ $$ = new MethodDecl(); $$->pb($1, $2) }
	| VOID id LEFT_ROUND param type id RIGHT_ROUND block									{ $$ = new MethodDecl(); $4->add_arg($5, $6); $$->params = $4; }
	;

param: 																						{ $$ = new ParamList(); }
	| param type id COMMA																	{ $$->push_back($2, $4); }
	;

block: LEFT_CURLY multi_var_decl multi_statement RIGHT_CURLY 								{ $$ = new Block($2, $3); }
	;

multi_var_decl: 																			{ $$ = new DeclerationList(); }
	| multi_var_decl type multi_id id SEMICOLON												{ $3->push_back($4); $$->push_back($2, $3); }
	;

multi_id: 																					{ $$ = new VariableList(); }
	| multi_id id COMMA 																	{ $$->push_back($2); }
	;

multi_statement: 																			{ $$ = new StatementList(); }
	| multi_statement statement 															{ $1->push_back($2);  $$->push_back($1); }
	;

type: INT 																					{ $$ = $1; }
	| BOOL 																					{ $$ = $1; }
	;

statement: location assign_op expr SEMICOLON 												{ $$ = new AssignStmt($1, $3); }
	| method_call SEMICOLON 																{ $$ = new MethodCall }
	| IF LEFT_ROUND expr RIGHT_ROUND block ELSE block 										{ $$ = new IfElseStmt($3, $5, $7); }
	| IF LEFT_ROUND expr RIGHT_ROUND block 													{ $$ = new IfStmt($3, $5); }
	| FOR id EQ expr COMMA expr block 														{ $$ = new ForStmt($2, $4, $6, $7); }
	| RET expr SEMICOLON 																	{ $$ = new RetExpr($2); }
	| RET SEMICOLON 																		{ $$ = new Ret(); }
	| BREAK SEMICOLON 																		{ $$ = bew BreakStmt(); }
	| CONT SEMICOLON 																		{ $$ = new ContStmt(); }
	| block 																				{ $$ = $1; }
	;

assign_op: EQ 																				{ $$ = $1; }
	| MINEQ																					{ $$ = $1; }
	| PLUSEQ																				{ $$ = $1; }
	;

method_call: method_name LEFT_ROUND RIGHT_ROUND 											{ $$ = new MethodCall(); }
	| method_name LEFT_ROUND multi_expr expr RIGHT_ROUND 									{ $3->push_back($4); $$ = new MethodCall($3); }
	| CALLOUT LEFT_ROUND string_literal RIGHT_ROUND 										{ $$ = new CalloutCall($3); }
	| CALLOUT LEFT_ROUND string_literal COMMA multi_callout_arg callout_arg RIGHT_ROUND 	{ $5->push_back($6); $$ = new CalloutCall($3, $5); }
	;

multi_expr: 																				{ $$ = new MethodArgInpList(); }
	| multi_expr expr COMMA 																{ $$->push_back($2); }
	;

multi_callout_arg:  																		{ $$ = new CalloutArgList(); }
	| multi_callout_arg callout_arg COMMA 													{ $$->push_back($2); }
	;

method_name: id 																			{ $$ = $1; }
	;

location: id 																				{ $$ = new TerminalVariable($1); }
	| id LEFT_SQUARE expr RIGHT_SQUARE 														{ $$ = new TerminalVariable($1, $3); }
	;

expr: location 																				{ $$ = $1; }
	| method_call 																			{ $$ = $1; }
	| literal 																				{ $$ = $1; }
	| expr bin_op expr /*FIXXXXXXXXXXXXX*/ 													{ $$ = new BinaryOpExpression($1, $2, $3); }
	| MINUS expr 																			{ $$ = new UniaryOpExpression($1, $2); }
	| NOT expr 																				{ $$ = new UniaryOpExpression($1, $2); }
	| LEFT_ROUND expr RIGHT_ROUND 															{ $$ = $2; }
	;

callout_arg: expr 																			{ $$ = $1; }
	| string_literal 																		{ $$ = $1; }
	;

bin_op: arith_op 																			{ $$ = $1; }
	| rel_op																				{ $$ = $1; }
	| eq_op 																				{ $$ = $1; }
	| cond_op 																				{ $$ = $1; }
	;

arith_op: PLUS 																				{ $$ = $1; }
	| MINUS 																				{ $$ = $1; }
	| MUL 																					{ $$ = $1; }
	| DIV 																					{ $$ = $1; }
	| MOD 																					{ $$ = $1; }
	;

rel_op: GT  																				{ $$ = $1; }
	| LT  																					{ $$ = $1; }
	| GE 																					{ $$ = $1; }
	| LE 																					{ $$ = $1; }
	;

eq_op: EQEQ  																				{ $$ = $1; }
	| NEQ 																					{ $$ = $1; }
	;

cond_op: ANDAND 																			{ $$ = $1; }
	| OROR 																					{ $$ = $1; }
	;

literal: int_literal 																		{ $$ = $1; }
	| char_literal 																			{ $$ = $1; }
	| bool_literal 																			{ $$ = $1; }
	;

id: REGEX_ID 																				{ $$ = $1; }
	;

int_literal: decimal_literal 																{ $$ = $1; }
	| hex_literal 																			{ $$ = $1; }
	;

decimal_literal: REGEX_DECIMAL 																{ $$ = $1; }
	;

hex_literal: REGEX_HEX 																		{ $$ = $1; }
	;

bool_literal: TRUE 																			{ $$ = $1; }
	| FALSE 																				{ $$ = $1; }
	;

char_literal: /*SQUOT CHAR SQUOT*/ REGEX_CHAR 												{ $$ = $1; }
	;

string_literal: /*DQUOT multichar DQUOT*/ REGEX_STRING 										{ $$ = $1; }
	;

%%

int main(int argc, char **argv) {
	yyparse();
}
int yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}

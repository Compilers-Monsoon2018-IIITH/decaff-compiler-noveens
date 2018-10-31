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

program: CLASS PROG LEFT_CURLY field_decl method_decl RIGHT_CURLY		{ $$ = new Program($4, $5); }
	;

field_decl: 					{ $$ = new FieldDeclList(); }
	| field_decl field_decls	{ $$->push_back($2); }
	;

method_decl: 					{ $$ = new MethodDeclList(); }
	| method_decl method_decls	{ $$->push_back($2); }
	;

field_decls: type follow id SEMICOLON									{ $$->push_back($3); }
	| type follow id LEFT_SQUARE int_literal RIGHT_SQUARE SEMICOLON		{ $$->push_back($3, $5); }
	;

follow:															{ $$ = new VariableList(); }
	| follow id COMMA											{ $$->push_back($2); }
	| follow id LEFT_SQUARE int_literal RIGHT_SQUARE COMMA		{ $$->push_back($2, $4); }
	;

method_decls: type id LEFT_ROUND RIGHT_ROUND block			{ $$ = new MethodDecl(); $$->pb($1, $2) }
	| type id LEFT_ROUND param type id RIGHT_ROUND block	{ $$ = new MethodDecl(); $4->add_arg($5, $6); $$->params = $4; }
	| VOID id LEFT_ROUND RIGHT_ROUND block					{ $$ = new MethodDecl(); $$->pb($1, $2) }
	| VOID id LEFT_ROUND param type id RIGHT_ROUND block	{ $$ = new MethodDecl(); $4->add_arg($5, $6); $$->params = $4; }
	;

param: 						{ $$ = new ParamList(); }
	| param type id COMMA	{ $$->push_back($2, $4); }
	;

block: LEFT_CURLY multi_var_decl multi_statement RIGHT_CURLY 	{ $$ = new Block($2, $3); }
	;

multi_var_decl: 									{ $$ = new DeclerationList(); }
	| multi_var_decl type multi_id id SEMICOLON		{ $3->push_back($4); $$->push_back($2, $3); }
	;

multi_id: 					{ $$ = new VariableList(); }
	| multi_id id COMMA 	{ $$->push_back($2); }
	;

multi_statement: 					{ $$ = new StatementList(); }
	| multi_statement statement 	{ $1->push_back($2);  $$->push_back($1); }
	;

type: INT
	| BOOL
	;

statement: location assign_op expr SEMICOLON 			{ $$ = new AssignStmt($1, $3); }
	| method_call SEMICOLON 							{ $$ = new MethodCall }
	| IF LEFT_ROUND expr RIGHT_ROUND block ELSE block 	{ $$ = new IfElseStmt($3, $5, $7); }
	| IF LEFT_ROUND expr RIGHT_ROUND block 				{ $$ = new IfStmt($3, $5); }
	| FOR id EQ expr COMMA expr block 					{ $$ = new ForStmt($2, $4, $6, $7); }
	| RET expr SEMICOLON 								{ $$ = new RetExpr($2); }
	| RET SEMICOLON 									{ $$ = new Ret(); }
	| BREAK SEMICOLON 									{ $$ = bew BreakStmt(); }
	| CONT SEMICOLON 									{ $$ = new ContStmt(); }
	| block 											{ $$ = $1; }
	;

assign_op: EQ
	| MINEQ
	| PLUSEQ
	;

method_call: method_name LEFT_ROUND multi_expr expr RIGHT_ROUND
	| CALLOUT LEFT_ROUND string_literal multi_callout_arg callout_arg RIGHT_ROUND
	;

multi_expr: 
	| multi_expr expr COMMA
	;

multi_callout_arg: 
	| multi_callout_arg callout_arg COMMA
	;

method_name: id
	;

location: id
	| id LEFT_SQUARE expr RIGHT_SQUARE
	;

expr: location
	| method_call
	| literal
	| expr bin_op expr /*FIXXXXXXXXXXXXX*/
	| MINUS expr
	| NOT expr
	| LEFT_ROUND expr RIGHT_ROUND
	;

callout_arg: expr
	| string_literal
	;

bin_op: arith_op
	| rel_op
	| eq_op
	| cond_op
	;

arith_op: PLUS
	| MINUS
	| MUL
	| DIV
	| MOD
	;

rel_op: GT
	| LT
	| GE
	| LE
	;

eq_op: EQEQ
	| NEQ
	;

cond_op: ANDAND
	| OROR
	;

literal: int_literal
	| char_literal
	| bool_literal
	;

id: REGEX_ID
	;

int_literal: decimal_literal
	| hex_literal
	;

decimal_literal: REGEX_DECIMAL
	;

hex_literal: REGEX_HEX
	;

bool_literal: TRUE
	| FALSE
	;

char_literal: SQUOT CHAR SQUOT
	;

string_literal: DQUOT multichar DQUOT
	;

multichar: 
	| CHAR multichar
	;

%%

int main(int argc, char **argv) {
	yyparse();
}
int yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}

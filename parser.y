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

program: CLASS PROG LEFT_CURLY field_decl method_decl RIGHT_CURLY
	;

field_decl: 
	| field_decl field_decls
	;

method_decl: 
	| method_decl method_decls
	;

field_decls: type follow id SEMICOLON
	| type follow id LEFT_SQUARE int_literal RIGHT_SQUARE SEMICOLON
	;

follow:
	| follow id COMMA
	| follow id LEFT_SQUARE int_literal RIGHT_SQUARE COMMA
	;

method_decls: type id LEFT_ROUND RIGHT_ROUND block
	| type id LEFT_ROUND param type id RIGHT_ROUND block
	| VOID id LEFT_ROUND RIGHT_ROUND block
	| VOID id LEFT_ROUND param type id RIGHT_ROUND block
	;

param: 
	| param type id COMMA
	;

block: LEFT_CURLY multi_var_decl multi_statement RIGHT_CURLY
	;

multi_var_decl: 
	| multi_var_decl type multi_id id SEMICOLON
	;

multi_id:
	| multi_id id COMMA
	;

multi_statement:
	| multi_statement statement
	;

type: INT
	| BOOL
	;

statement: location assign_op expr SEMICOLON
	| method_call SEMICOLON
	| IF LEFT_ROUND expr RIGHT_ROUND block ELSE block
	| IF LEFT_ROUND expr RIGHT_ROUND block
	| FOR id EQ expr COMMA expr block
	| RET expr SEMICOLON
	| RET SEMICOLON
	| BREAK SEMICOLON
	| CONT SEMICOLON
	| block
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

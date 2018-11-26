%{

#include <bits/stdc++.h>
#include "class_definition.h"
bool fl_parsed_correct = true;
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int linenum;
extern union Node yylval;
extern "C" int errors;
void yyerror(const char *s);
class Program* rootAst = NULL;
int errors=0;

%}

%start program

%token <lit> PROG
%token <lit> CLASS
%token <lit> LEFT_CURLY RIGHT_CURLY
%token <lit> LEFT_SQUARE RIGHT_SQUARE
%token <lit> LEFT_ROUND RIGHT_ROUND
%token <lit> VOID INT BOOL
%token <lit> IF
%token <lit> ELSE
%token <lit> FOR
%token <lit> RET
%token <lit> BREAK
%token <lit> CONT
%token <lit> CALLOUT
%token <lit> TRUE
%token <lit> FALSE
%token <lit> COMMA
%token <lit> SEMICOLON

%token <num> REGEX_HEX
%token <lit> REGEX_ID
%token <num> REGEX_DECIMAL
%token <lit> REGEX_CHAR
%token <lit> REGEX_STRING

%left <lit> ANDAND OROR NOT NEQ EQEQ
%left <lit> LT GT LE GE
%left <lit> PLUS MINUS 
%left <lit> MUL DIV
%nonassoc <lit> MOD
%left <lit> PLUSEQ MINEQ EQ

%type <Programs> program;
%type <FieldDeclLists> field_decl;
%type <VariableLists> field_decls;
%type <VariableLists> follow;
%type <MethodDeclLists> method_decl;
%type <MethodDecls> method_decls;
%type <ParamLists> param;
%type <Blocks> block;
%type <FieldDeclLists> multi_var_decl;
%type <VariableLists> multi_id;
%type <StatementLists> multi_statement;
%type <lit> type;
%type <Statements> statement;
%type <lit> assign_op;
%type <MethodCalls> method_call;
%type <CalloutCalls> callout_call;
%type <MethodArgInpLists> multi_expr;
%type <CalloutArgLists> multi_callout_arg;
%type <TerminalVariables> method_name;
%type <Locations> location;
%type <Exprs> expr;
%type <CalloutArgs> callout_arg;
%type <Literals> literal;
%type <TerminalVariables> id;
%type <num> int_literal;
%type <lit> bool_literal;
%type <lit> char_literal;
%type <lit> string_literal;

%%

program: CLASS PROG LEFT_CURLY field_decl method_decl RIGHT_CURLY							{ $$ = new Program($4, $5); rootAst = $$; $$->lineno = linenum; }
	;

field_decl: 																				{ $$ = new FieldDeclList(); $$->lineno = linenum; }
	| field_decl field_decls																{ $$ = $1; $$->push_back($2); }
	;

field_decls: type id follow SEMICOLON														{ $3->push_back($2); $3->set_type($1); $$ = $3; }
	| type id LEFT_SQUARE int_literal RIGHT_SQUARE follow SEMICOLON							{ $6->push_back(new ArrayTerminalVariable($2, $4)); $6->set_type($1); $$ = $6; $$->lineno = linenum; }
	;

follow:																						{ $$ = new VariableList(); $$->lineno = linenum; }
	| COMMA id follow																		{ $$ = $3; $$->push_back($2); }
	| COMMA id LEFT_SQUARE int_literal RIGHT_SQUARE follow									{ $$ = $6; $$->push_back(new ArrayTerminalVariable($2, int($4))); $$->lineno = linenum; }
	;

method_decl: 																				{ $$ = new MethodDeclList(); $$->lineno = linenum; }
	| method_decls method_decl																{ $$ = $2; $$->push_back($1); }
	;

method_decls: type id LEFT_ROUND RIGHT_ROUND block											{ $$ = new MethodDecl($1, $2, $5); $$->lineno = linenum; }
	| type id LEFT_ROUND param type id RIGHT_ROUND block									{ $4->push_back($5, $6); $$ = new MethodDecl($1, $2, $4, $8); $$->lineno = linenum; }
	| VOID id LEFT_ROUND RIGHT_ROUND block													{ $$ = new MethodDecl($1, $2, $5); $$->lineno = linenum; }
	| VOID id LEFT_ROUND param type id RIGHT_ROUND block									{ $4->push_back($5, $6); $$ = new MethodDecl($1, $2, $4, $8); $$->lineno = linenum; }
	;

param: 																						{ $$ = new ParamList(); $$->lineno = linenum; }
	| param type id COMMA																	{ $$->push_back($2, $3); }
	;

block: LEFT_CURLY multi_var_decl multi_statement RIGHT_CURLY 								{ $$ = new Block($2, $3); $$->lineno = linenum; }
	;

multi_var_decl: 																			{ $$ = new FieldDeclList(); $$->lineno = linenum; }
	| multi_var_decl type multi_id id SEMICOLON												{ $3->push_back($4); $3->set_type($2); $$->push_back($3); }
	;

multi_id: 																					{ $$ = new VariableList(); $$->lineno = linenum; }
	| multi_id id COMMA 																	{ $$->push_back($2); }
	;

multi_statement: 																			{ $$ = new StatementList(); $$->lineno = linenum; }
	| multi_statement statement 															{ $$->push_back($2); }
	;

type: INT 																					{ $$ = $1; }
	| BOOL 																					{ $$ = $1; }
	;

statement: location assign_op expr SEMICOLON 												{ $$ = new AssignStmt($1, $2, $3); $$->lineno = linenum; }
	| method_call SEMICOLON 																{ $$ = $1; }
	| callout_call SEMICOLON 																{ $$ = $1; }
	| IF LEFT_ROUND expr RIGHT_ROUND block ELSE block 										{ $$ = new IfElseStmt($3, $5, $7); $$->lineno = linenum; }
	| IF LEFT_ROUND expr RIGHT_ROUND block 													{ $$ = new IfStmt($3, $5); $$->lineno = linenum; }
	| FOR id EQ expr COMMA expr block 														{ $$ = new ForStmt($2, $4, $6, $7); $$->lineno = linenum; }
	| RET expr SEMICOLON 																	{ $$ = new RetExpr($2); $$->lineno = linenum; }
	| RET SEMICOLON 																		{ $$ = new StringRetBrkContStatement($1); $$->lineno = linenum; }
	| BREAK SEMICOLON 																		{ $$ = new StringRetBrkContStatement($1); $$->lineno = linenum; }
	| CONT SEMICOLON 																		{ $$ = new StringRetBrkContStatement($1); $$->lineno = linenum; }
	| block 																				{ $$ = $1; }
	;

assign_op: EQ 																				{ $$ = $1; }
	| MINEQ																					{ $$ = $1; }
	| PLUSEQ																				{ $$ = $1; }
	;

method_call: method_name LEFT_ROUND RIGHT_ROUND 											{ $$ = new MethodCall($1); $$->lineno = linenum; }
	| method_name LEFT_ROUND multi_expr expr RIGHT_ROUND 									{ $3->push_back($4); $$ = new MethodCall($1, $3); $$->lineno = linenum; }
	;

callout_call: CALLOUT LEFT_ROUND string_literal RIGHT_ROUND 								{ $$ = new CalloutCall($3); $$->lineno = linenum; }
	| CALLOUT LEFT_ROUND string_literal COMMA multi_callout_arg callout_arg RIGHT_ROUND 	{ $5->push_back($6); $$ = new CalloutCall($3, $5); $$->lineno = linenum; }
	;

multi_expr: 																				{ $$ = new MethodArgInpList(); $$->lineno = linenum; }
	| multi_expr expr COMMA 																{ $$->push_back($2); }
	;

multi_callout_arg:  																		{ $$ = new CalloutArgList(); $$->lineno = linenum; }
	| multi_callout_arg callout_arg COMMA 													{ $$->push_back($2); }
	;

method_name: id 																			{ $$ = $1; }
	;

location: id 																				{ $$ = new Location($1); $$->lineno = linenum; }
	| id LEFT_SQUARE expr RIGHT_SQUARE 														{ $$ = new Location($1, $3); $$->lineno = linenum; }
	;

expr: location 																				{ $$ = $1; }
	| method_call 																			{ $$ = $1; }
	| callout_call 																			{ $$ = $1; }
	| literal 																				{ $$ = $1; }
	| expr PLUS expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr MINUS expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr MUL expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr DIV expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr MOD expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr LT expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr GT expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr LE expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr GE expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr EQEQ expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr NEQ expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr ANDAND expr  																	{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| expr OROR expr  																		{ $$ = new BinaryOpExpression($1, $2, $3); $$->lineno = linenum; }
	| MINUS expr 																			{ $$ = new UnaryOpExpression($1, $2); $$->lineno = linenum; }
	| NOT expr 																				{ $$ = new UnaryOpExpression($1, $2); $$->lineno = linenum; }
	| LEFT_ROUND expr RIGHT_ROUND 															{ $$ = $2; }
	;

callout_arg: expr 																			{ $$ = new CalloutArg($1); $$->lineno = linenum; }
	| string_literal 																		{ $$ = new CalloutArg($1); $$->lineno = linenum; }
	;

literal: int_literal 																		{ $$ = new Literal($1); $$->lineno = linenum; }
	| char_literal 																			{ $$ = new Literal($1); $$->lineno = linenum; }
	| bool_literal 																			{ $$ = new Literal($1); $$->lineno = linenum; }
	;

id: REGEX_ID 																				{ $$ = new TerminalVariable($1); $$->lineno = linenum; }
	;

int_literal: REGEX_DECIMAL 																	{ $$ = $1; }
	| REGEX_HEX 																			{ $$ = $1; }
	;

bool_literal: TRUE 																			{ $$ = $1; }
	| FALSE 																				{ $$ = $1; }
	;

char_literal: REGEX_CHAR 																	{ $$ = $1; }
	;

string_literal: REGEX_STRING 																{ $$ = $1; }
	;

%%

int main(int argc, char **argv) {
	yyparse();

	if (fl_parsed_correct == true) {
		// Checking the AST construction
		/* class SomeVisitor *visitor = new SomeVisitor();
		visitor->visit(rootAst); */

		cout << endl << endl;

		// Semantic checking
		class SemanticVisitor *semantic_visitor = new SemanticVisitor(new LogErrorClass());
		semantic_visitor->visit(rootAst);

		// Code generation
		rootAst->codegen(semantic_visitor->logger_class);
	}
}

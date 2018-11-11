#ifndef __CLASS_DEF__
#define __CLASS_DEF__
#include <bits/stdc++.h>

using namespace std;

union Node{
	int num;
	string* lit;
	class Program* Programs;
	class Expr* Exprs;
	class BinaryOpExpression* BinaryOpExpressions;
	class UnaryOpExpression* UnaryOpExpressions;
	class MethodCall* MethodCalls;
	class MethodArgInpList* MethodArgInpLists;
	class CalloutCall* CalloutCalls;
	class CalloutArgList* CalloutArgLists;
	class TerminalVariable* TerminalVariables;
	class ArrayTerminalVariable* ArrayTerminalVariables;
	class FieldDeclList* FieldDeclLists;
	class VariableList* VariableLists;
	class MethodDeclList* MethodDeclLists;
	class MethodDecl* MethodDecls;
	class ParamList* ParamLists;
	class Block* Blocks;
	class Statement* Statements;
	class StatementList* StatementLists;
	class AssignStmt* AssignStmts;
	class IfElseStmt* IfElseStmts;
	class IfStmt* IfStmts;
	class ForStmt* ForStmts;
	class RetExpr* RetExprs;
	class StringRetBrkContStatement* StringRetBrkContStatements;
	class Location* Locations;
	class CalloutArg* CalloutArgs;
	class Literal* Literals;
	Node() {
		num = 0;
		lit = NULL;
		Programs = NULL;
		Exprs = NULL;
		BinaryOpExpressions = NULL;
		UnaryOpExpressions = NULL;
		MethodCalls = NULL;
		MethodArgInpLists = NULL;
		CalloutCalls = NULL;
		CalloutArgLists = NULL;
		TerminalVariables = NULL;
		ArrayTerminalVariables = NULL;
		FieldDeclLists = NULL;
		VariableLists = NULL;
		MethodDeclLists = NULL;
		MethodDecls = NULL;
		ParamLists = NULL;
		Blocks = NULL;
		Statements = NULL;
		StatementLists = NULL;
		AssignStmts = NULL;
		IfElseStmts = NULL;
		IfStmts = NULL;
		ForStmts = NULL;
		RetExprs = NULL;
		StringRetBrkContStatements = NULL;
		Locations = NULL;
		CalloutArgs = NULL;
		Literals = NULL;
	}
	~Node(){}
};
typedef union Node YYSTYPE;

#define YYSTYPE_IS_DECLARED 1

class ASTVisitor{
	public:
		virtual void visit(class BaseAst&) = 0;
};

/* Base AST Node class, inherited by every other class */
class BaseAst {
	public:
		virtual void accept(class ASTVisitor& v) {
			v.visit(*this);
		}
		BaseAst() {} // Defined Here itself
		// virtual ~BaseAst() = 0;
};

class Program: public BaseAst {
	public:
		class FieldDeclList* field_decl;
		class MethodDeclList* method_decl;

		Program(class FieldDeclList*, class MethodDeclList*) ;
};

/* Final Variables */
class Expr: public BaseAst {
	public:
		Expr() {} // Defined Here itself
		// virtual ~Expr() = 0; // Abstract class, can't be instantiated
};

// Base class
class Statement: public BaseAst {
	public:
		Statement() {} // Defined Here itself
		// virtual ~Statement() = 0; // Abstract class, can't be instantiated
};

class BinaryOpExpression: public Expr {
	public:
		string *op;
		class Expr* left;
		class Expr* right;

		BinaryOpExpression(class Expr*, string*, class Expr*) ;
};

class UnaryOpExpression: public Expr {
	public:
		string *op;
		class Expr* expr;

		UnaryOpExpression(string*, class Expr*) ;
};

class MethodCall: public Expr, public Statement {
	public:
		class MethodArgInpList* args;
		
		MethodCall() ;
		MethodCall(class MethodArgInpList*) ;
};

class MethodArgInpList: public BaseAst {
	public:
		vector<class Expr*> arg_list;

		MethodArgInpList() ;

		void push_back(class Expr*);
};

class CalloutCall: public Expr, public Statement {
	public:
		string *function_name;
		class CalloutArgList* args;
		
		CalloutCall(string*) ;
		CalloutCall(string*, class CalloutArgList*) ;
};

class CalloutArgList: public BaseAst {
	public:
		vector<class CalloutArg*> arg_list;

		CalloutArgList() ;

		void push_back(class CalloutArg*);
};

class Location: public Expr {
	public:
		class TerminalVariable* var_name;
		class Expr* index;
		string location_type;

		Location(class TerminalVariable*) ;
		Location(class TerminalVariable*, class Expr*) ;
};

class CalloutArg: public BaseAst {
	public:
		class Expr* arg_expr;
		string *arg_string;
		string arg_type = "";

		CalloutArg(class Expr*) ;
		CalloutArg(string*) ;
};

class TerminalVariable: public Expr {
	public:
		string *variable_name;
		
		TerminalVariable(string*) ;
};

class ArrayTerminalVariable: public Expr {
	public:
		class TerminalVariable* arr_name;
		class Expr* index;
		int index_int;
		string index_type;

		ArrayTerminalVariable(class TerminalVariable*, class Expr*) ;
		ArrayTerminalVariable(class TerminalVariable*, int) ;
};

/* Field decleration
eg. int a, b, c; bool d, e;
*/

class FieldDeclList: public BaseAst {
	public:	
		vector<class VariableList*> all_declerations;
		
		FieldDeclList() ;
		
		void push_back(class VariableList*);
};

class VariableList: public BaseAst {
	public:	
		vector<class TerminalVariable*> declarations;
		vector<class ArrayTerminalVariable*> declarations_array;
		string *decleration_type;
		
		VariableList() ;
		
		void push_back(class TerminalVariable*);
		void push_back(class ArrayTerminalVariable*);
		void set_type(string*);
};

class MethodDeclList: public BaseAst {
	public:	
		vector<class MethodDecl*> method_declerations_list;
		
		MethodDeclList() ;
		
		void push_back(class MethodDecl*);
};

/* Method decleration
eg. int function_name(int a, bool b, int c) <block>
*/

class MethodDecl: public BaseAst {
	public:	
		string *return_type;
		class TerminalVariable* method_name;
		class ParamList* param_list;
		class Block* code_block;

		MethodDecl(string*, class TerminalVariable*, class ParamList*, class Block*) ;
		MethodDecl(string*, class TerminalVariable*, class Block*) ;
};

class ParamList: public BaseAst {
	public:	
		vector<pair<string*, class TerminalVariable*>> parameters_list;

		ParamList() ;

		void push_back(string*, class TerminalVariable*);
};

/* Statements */

// List class
class StatementList: public BaseAst {
	public:
		vector<class Statement*> statement_list;

		StatementList() ;

		void push_back(class Statement*);
};

class Block: public Statement {
	public:
		class FieldDeclList* decleration_list;
		class StatementList* statement_list;

		Block(class FieldDeclList*, class StatementList*) ;
};

// Specific Statement class
class AssignStmt: public Statement {
	public:
		class Location* left;
		string *op;
		class Expr* right;

		AssignStmt(class Location*, string*, class Expr*) ;
};

// Specific Statement class
class IfElseStmt: public Statement {
	public:
		class Expr* cond;
		class Block* if_block;
		class Block* else_block;

		IfElseStmt(class Expr*, class Block*, class Block*) ;
};

// Specific Statement class
class IfStmt: public Statement {
	public:
		class Expr* cond;
		class Block* if_block;

		IfStmt(class Expr*, class Block*) ;
};

// Specific Statement class
class ForStmt: public Statement {
	public:
		class TerminalVariable* loop_var;
		class ArrayTerminalVariable* loop_var_arr;
		class Expr* start_cond;
		class Expr* right_cond; 
		class Block* code_block;		

		ForStmt(class TerminalVariable*, class Expr*, class Expr*, class Block*) ;
		ForStmt(class ArrayTerminalVariable*, class Expr*, class Expr*, class Block*) ;
};

// Specific Statement class
class RetExpr: public Statement {
	public:
		class Expr* expr;

		RetExpr(class Expr*) ;
};

class StringRetBrkContStatement: public Statement {
	public:
		string *type;

		StringRetBrkContStatement(string*) ;
};

class Literal: public Expr {
	public:
		int lit_int;
		string *lit_string;
		string literal_type;

		Literal(int) ;
		Literal(string*) ;
};

#endif // __CLASS_DEF__
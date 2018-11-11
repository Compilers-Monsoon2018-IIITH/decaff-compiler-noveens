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

/* Visitor Classes */
class ASTVisitor {
	public:
		virtual void visit(class Program*) = 0;
		virtual void visit(class BinaryOpExpression*) = 0;
		virtual void visit(class UnaryOpExpression*) = 0;
		virtual void visit(class MethodCall*) = 0;
		virtual void visit(class MethodArgInpList*) = 0;
		virtual void visit(class CalloutCall*) = 0;
		virtual void visit(class CalloutArgList*) = 0;
		virtual void visit(class TerminalVariable*) = 0;
		virtual void visit(class ArrayTerminalVariable*) = 0;
		virtual void visit(class FieldDeclList*) = 0;
		virtual void visit(class VariableList*) = 0;
		virtual void visit(class MethodDeclList*) = 0;
		virtual void visit(class MethodDecl*) = 0;
		virtual void visit(class ParamList*) = 0;
		virtual void visit(class Block*) = 0;
		virtual void visit(class StatementList*) = 0;
		virtual void visit(class AssignStmt*) = 0;
		virtual void visit(class IfElseStmt*) = 0;
		virtual void visit(class IfStmt*) = 0;
		virtual void visit(class ForStmt*) = 0;
		virtual void visit(class RetExpr*) = 0;
		virtual void visit(class StringRetBrkContStatement*) = 0;
		virtual void visit(class Location*) = 0;
		virtual void visit(class CalloutArg*) = 0;
		virtual void visit(class Literal*) = 0;
};

class SomeVisitor: public ASTVisitor {
	public:
		SomeVisitor() ;

		void visit(class Program*);
		void visit(class BinaryOpExpression*);
		void visit(class UnaryOpExpression*);
		void visit(class MethodCall*);
		void visit(class MethodArgInpList*);
		void visit(class CalloutCall*);
		void visit(class CalloutArgList*);
		void visit(class TerminalVariable*);
		void visit(class ArrayTerminalVariable*);
		void visit(class FieldDeclList*);
		void visit(class VariableList*);
		void visit(class MethodDeclList*);
		void visit(class MethodDecl*);
		void visit(class ParamList*);
		void visit(class Block*);
		void visit(class StatementList*);
		void visit(class AssignStmt*);
		void visit(class IfElseStmt*);
		void visit(class IfStmt*);
		void visit(class ForStmt*);
		void visit(class RetExpr*);
		void visit(class StringRetBrkContStatement*);
		void visit(class Location*);
		void visit(class CalloutArg*);
		void visit(class Literal*);
};

/* Base AST Node class, inherited by every other class */
class BaseAst {
	public:
		virtual void accept(ASTVisitor* v) = 0;
};

class Program: public BaseAst {
	public:
		class FieldDeclList* field_decl;
		class MethodDeclList* method_decl;

		Program(class FieldDeclList*, class MethodDeclList*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

/* Final Variables */
class Expr: public BaseAst {
	public:
		Expr() {} // Defined Here itself
};

// Base class
class Statement: public BaseAst {
	public:
		Statement() {} // Defined Here itself
};

class BinaryOpExpression: public Expr {
	public:
		string *op;
		class Expr* left;
		class Expr* right;

		BinaryOpExpression(class Expr*, string*, class Expr*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

class UnaryOpExpression: public Expr {
	public:
		string *op;
		class Expr* expr;

		UnaryOpExpression(string*, class Expr*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

class MethodCall: public Expr, public Statement {
	public:
		class MethodArgInpList* args;
		class TerminalVariable* method_name;
		
		MethodCall(class TerminalVariable*) ;
		MethodCall(class TerminalVariable*, class MethodArgInpList*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

class MethodArgInpList: public BaseAst {
	public:
		vector<class Expr*> arg_list;

		MethodArgInpList() ;

		void push_back(class Expr*);
		void accept(ASTVisitor* v) { v->visit(this); };
};

class CalloutCall: public Expr, public Statement {
	public:
		string *function_name;
		class CalloutArgList* args;
		
		CalloutCall(string*) ;
		CalloutCall(string*, class CalloutArgList*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

class CalloutArgList: public BaseAst {
	public:
		vector<class CalloutArg*> arg_list;

		CalloutArgList() ;

		void push_back(class CalloutArg*);
		void accept(ASTVisitor* v) { v->visit(this); };
};

class Location: public Expr {
	public:
		class TerminalVariable* var_name;
		class Expr* index;
		string location_type;

		Location(class TerminalVariable*) ;
		Location(class TerminalVariable*, class Expr*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

class CalloutArg: public BaseAst {
	public:
		class Expr* arg_expr;
		string *arg_string;
		string arg_type = "";

		CalloutArg(class Expr*) ;
		CalloutArg(string*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

class TerminalVariable: public Expr {
	public:
		string *variable_name;
		
		TerminalVariable(string*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

class ArrayTerminalVariable: public Expr {
	public:
		class TerminalVariable* arr_name;
		class Expr* index;
		int index_int;
		string index_type;

		ArrayTerminalVariable(class TerminalVariable*, class Expr*) ;
		ArrayTerminalVariable(class TerminalVariable*, int) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

/* Field decleration
eg. int a, b, c; bool d, e;
*/

class FieldDeclList: public BaseAst {
	public:	
		vector<class VariableList*> all_declerations;
		
		FieldDeclList() ;
		
		void push_back(class VariableList*);
		void accept(ASTVisitor* v) { v->visit(this); };
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
		void accept(ASTVisitor* v) { v->visit(this); };
};

class MethodDeclList: public BaseAst {
	public:	
		vector<class MethodDecl*> method_declerations_list;
		
		MethodDeclList() ;
		
		void push_back(class MethodDecl*);
		void accept(ASTVisitor* v) { v->visit(this); };
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

		void accept(ASTVisitor* v) { v->visit(this); };
};

class ParamList: public BaseAst {
	public:	
		vector<pair<string*, class TerminalVariable*>> parameters_list;

		ParamList() ;

		void push_back(string*, class TerminalVariable*);
		void accept(ASTVisitor* v) { v->visit(this); };
};

/* Statements */

// List class
class StatementList: public BaseAst {
	public:
		vector<class Statement*> statement_list;

		StatementList() ;

		void push_back(class Statement*);
		void accept(ASTVisitor* v) { v->visit(this); };
};

class Block: public Statement {
	public:
		class FieldDeclList* decleration_list;
		class StatementList* statement_list;

		Block(class FieldDeclList*, class StatementList*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

// Specific Statement class
class AssignStmt: public Statement {
	public:
		class Location* left;
		string *op;
		class Expr* right;

		AssignStmt(class Location*, string*, class Expr*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

// Specific Statement class
class IfElseStmt: public Statement {
	public:
		class Expr* cond;
		class Block* if_block;
		class Block* else_block;

		IfElseStmt(class Expr*, class Block*, class Block*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

// Specific Statement class
class IfStmt: public Statement {
	public:
		class Expr* cond;
		class Block* if_block;

		IfStmt(class Expr*, class Block*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

// Specific Statement class
class ForStmt: public Statement {
	public:
		class TerminalVariable* loop_var;
		class ArrayTerminalVariable* loop_var_arr;
		class Expr* start_cond;
		class Expr* right_cond; 
		class Block* code_block;		
		string var_type;

		ForStmt(class TerminalVariable*, class Expr*, class Expr*, class Block*) ;
		ForStmt(class ArrayTerminalVariable*, class Expr*, class Expr*, class Block*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

// Specific Statement class
class RetExpr: public Statement {
	public:
		class Expr* expr;

		RetExpr(class Expr*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

class StringRetBrkContStatement: public Statement {
	public:
		string *type;

		StringRetBrkContStatement(string*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

class Literal: public Expr {
	public:
		int lit_int;
		string *lit_string;
		string literal_type;

		Literal(int) ;
		Literal(string*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
};

#endif // __CLASS_DEF__

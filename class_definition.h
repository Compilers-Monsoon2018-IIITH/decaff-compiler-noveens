#ifndef __CLASS_DEF__
#define __CLASS_DEF__
#include <bits/stdc++.h>

using namespace std;

class BaseAst;

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
		virtual ~BaseAst() = 0;
};

/* Final Variables */
class Expr: public BaseAst {
	public:
		virtual ~Expr() = 0; // Abstract class, can't be instantiated
};

class BinaryOpExpression: public Expr {
	public:
		string op;
		class Expr* left;
		class Expr* right;

		BinaryOpExpression(class Expr*, string, class Expr*) ;
};

class UnaryOpExpression: public Expr {
	public:
		string op;
		class Expr* expr;

		UnaryOpExpression(string, class Expr*) ;
};

class MethodCall: public Expr {
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

class CalloutCall: public Expr {
	public:
		string function_name;
		class CalloutArgList* args;
		
		CalloutCall(string) ;
		CalloutCall(string, class CalloutArgList*) ;
};

class CalloutArgList: public BaseAst {
	public:
		vector<class Expr*> arg_list_expr;
		vector<string> arg_list_string;

		CalloutArgList() ;

		void push_back(class Expr*);
		void push_back(string);
};

class ExprIntCharBool: public Expr {
	public:
		int this_int;
		char this_char;
		bool this_bool;
		string what_type;

		ExprIntCharBool(int) ;
		ExprIntCharBool(char) ;
		ExprIntCharBool(bool) ;
};

class TerminalVariable: public Expr {
	public:
		string variable_name;
		
		TerminalVariable(string) ;
};

class ArrayTerminalVariable: public Expr {
	public:
		class TerminalVariable* arr_name;
		class Expr* index;

		ArrayTerminalVariable(class TerminalVariable*, class Expr*) ;
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
		string decleration_type;
		
		VariableList() ;
		
		void push_back(class TerminalVariable*);
		void push_back(class ArrayTerminalVariable*);
		void set_type(string);
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
		string return_type;
		class TerminalVariable* method_name;
		class ParamList* param_list;
		class Block* code_block;

		MethodDecl(string, class TerminalVariable*, class ParamList*, class Block*) ;
		MethodDecl(string, class TerminalVariable*, class Block*) ;
};

class ParamList: public BaseAst {
	public:	
		vector<pair<string, class TerminalVariable*>> parameters_list;

		ParamList() ;

		void push_back(string, class TerminalVariable*);
};

class Block: public BaseAst {
	public:
		class DeclerationList* decleration_list;
		class StatementList* statement_list;

		Block(class DeclerationList*, class StatementList*) ;
};

/* Statements */

// List class
class StatementList: public BaseAst {
	public:
		vector<class Statement*> statement_list;

		StatementList() ;

		void push_back(class Statement*);
};

// Base class
class Statement: public BaseAst {
	public:
		virtual ~Statement() = 0; // Abstract class, can't be instantiated
};

// Specific Statement class
class AssignStmt: public Statement {
	public:
		class TerminalVariable* left;
		class ArrayTerminalVariable* left_arr;
		string op, left_type;
		class Expr* right;

		AssignStmt(class TerminalVariable*, string, class Expr*) ;
		AssignStmt(class ArrayTerminalVariable*, string, class Expr*) ;
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

#endif // __CLASS_DEF__
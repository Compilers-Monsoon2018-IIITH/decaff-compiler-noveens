#ifndef __CLASS_DEF__
#define __CLASS_DEF__
#include <bits/stdc++.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>

using namespace std;
using namespace llvm;

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

class LogErrorClass {
	public:
		vector<string> all_errors;

		LogErrorClass() {};

		void add(string, int);
};

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

class SemanticVisitor: public ASTVisitor {
	public:
		// Data Structures needed for semantic checking
		class LogErrorClass* logger_class;

		SemanticVisitor(class LogErrorClass*) ;

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
		virtual Value* codegen() {}
};

class Program: public BaseAst {
	public:
		class FieldDeclList* field_decl;
		class MethodDeclList* method_decl;

		Program(class FieldDeclList*, class MethodDeclList*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen(class LogErrorClass*);
		void print_llvm_ir();
};

/* Final Variables */
class Expr: public BaseAst {
	public:
		Expr() {} // Defined Here itself

		virtual string get_expr_type() = 0;
		int lineno;
};

// Base class
class Statement: public BaseAst {
	public:
		Statement() {} // Defined Here itself

		virtual string get_statement_type() = 0;
		int lineno;
};

class BinaryOpExpression: public Expr {
	public:
		string *op;
		class Expr* left;
		class Expr* right;

		BinaryOpExpression(class Expr*, string*, class Expr*) ;

		string get_expr_type() { return "BinaryOpExpression"; };
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

class UnaryOpExpression: public Expr {
	public:
		string *op;
		class Expr* expr;

		UnaryOpExpression(string*, class Expr*) ;

		string get_expr_type() { return "UnaryOpExpression"; };
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

class MethodCall: public Expr, public Statement {
	public:
		class MethodArgInpList* args;
		class TerminalVariable* method_name;
		
		MethodCall(class TerminalVariable*) ;
		MethodCall(class TerminalVariable*, class MethodArgInpList*) ;

		string get_expr_type() { return "MethodCall"; };
		string get_statement_type() { return "MethodCall"; };
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

class MethodArgInpList: public BaseAst {
	public:
		vector<class Expr*> arg_list;

		MethodArgInpList() ;

		void push_back(class Expr*);
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		// Value* codegen();
};

class CalloutCall: public Expr, public Statement {
	public:
		string *function_name;
		class CalloutArgList* args;
		
		CalloutCall(string*) ;
		CalloutCall(string*, class CalloutArgList*) ;

		string get_expr_type() { return "CalloutCall"; };
		string get_statement_type() { return "CalloutCall"; };
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

class CalloutArgList: public BaseAst {
	public:
		vector<class CalloutArg*> arg_list;

		CalloutArgList() ;

		void push_back(class CalloutArg*);
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
};

class Location: public Expr {
	public:
		class TerminalVariable* var_name;
		class Expr* index;
		string location_type;

		Location(class TerminalVariable*) ;
		Location(class TerminalVariable*, class Expr*) ;

		string get_expr_type() { return "Location"; };
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

class CalloutArg: public BaseAst {
	public:
		class Expr* arg_expr;
		string *arg_string;
		string arg_type = "";

		CalloutArg(class Expr*) ;
		CalloutArg(string*) ;

		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

class TerminalVariable: public Expr {
	public:
		string *variable_name;
		
		TerminalVariable(string*) ;

		string get_expr_type() { return "TerminalVariable"; };
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		// Value* codegen();
};

class ArrayTerminalVariable: public Expr {
	public:
		class TerminalVariable* arr_name;
		class Expr* index;
		int index_int;
		string index_type;

		ArrayTerminalVariable(class TerminalVariable*, class Expr*) ;
		ArrayTerminalVariable(class TerminalVariable*, int) ;

		string get_expr_type() { return "ArrayTerminalVariable"; };
		void accept(ASTVisitor* v) { v->visit(this); };
		int get_length() { return index_int; };
		int lineno;
		// Value* codegen();
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
		int lineno;
		Value* codegen(bool, map<string, AllocaInst *> &);
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
		int lineno;
		Value* codegen(bool, map<string, AllocaInst *> &);
};

class MethodDeclList: public BaseAst {
	public:	
		vector<class MethodDecl*> method_declerations_list;
		
		MethodDeclList() ;
		
		void push_back(class MethodDecl*);
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
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
		int lineno;
		Function* codegen();
};

class ParamList: public BaseAst {
	public:	
		vector<pair<string*, class TerminalVariable*>> parameters_list;

		ParamList() ;

		void push_back(string*, class TerminalVariable*);
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		// Value* codegen();
};

/* Statements */

// List class
class StatementList: public BaseAst {
	public:
		vector<class Statement*> statement_list;

		StatementList() ;

		bool has_return();
		bool has_return_expr();
		void push_back(class Statement*);
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

class Block: public Statement {
	public:
		class FieldDeclList* decleration_list;
		class StatementList* statement_list;

		Block(class FieldDeclList*, class StatementList*) ;

		bool has_return();
		bool has_return_expr();
		string get_statement_type() { return "Block"; }
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

// Specific Statement class
class AssignStmt: public Statement {
	public:
		class Location* left_part;
		string *op;
		class Expr* right_part;

		AssignStmt(class Location*, string*, class Expr*) ;

		string get_statement_type() { return "Assign"; }
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

// Specific Statement class
class IfElseStmt: public Statement {
	public:
		class Expr* cond;
		class Block* if_block;
		class Block* else_block;

		IfElseStmt(class Expr*, class Block*, class Block*) ;

		string get_statement_type() { return "IfElse"; }
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

// Specific Statement class
class IfStmt: public Statement {
	public:
		class Expr* cond;
		class Block* if_block;

		IfStmt(class Expr*, class Block*) ;

		string get_statement_type() { return "If"; }
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

// Specific Statement class
class ForStmt: public Statement {
	public:
		class TerminalVariable* loop_var;
		// class ArrayTerminalVariable* loop_var_arr;
		class Expr* start_cond;
		class Expr* right_cond; 
		class Block* code_block;		
		// string var_type;

		ForStmt(class TerminalVariable*, class Expr*, class Expr*, class Block*) ;
		// ForStmt(class ArrayTerminalVariable*, class Expr*, class Expr*, class Block*) ;

		string get_statement_type() { return "For"; }
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

// Specific Statement class
class RetExpr: public Statement {
	public:
		class Expr* expr;

		RetExpr(class Expr*) ;

		string get_statement_type() { return "RetExpr"; }
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

class StringRetBrkContStatement: public Statement {
	public:
		string *type;

		StringRetBrkContStatement(string*) ;

		string get_statement_type() { 
			if (*type == "return") {
				return "Ret"; 
			}
			else if (*type == "break") {
				return "Break";
			}
			else if (*type == "continue") {
				return "Continue";
			}
		}
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

class Literal: public Expr {
	public:
		int lit_int;
		bool lit_bool;
		string *lit_string;
		string literal_type;

		Literal(int) ;
		Literal(string*) ;

		string get_expr_type() { return "Literal"; };
		void accept(ASTVisitor* v) { v->visit(this); };
		int lineno;
		Value* codegen();
};

#endif // __CLASS_DEF__

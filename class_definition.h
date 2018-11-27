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
		virtual Value * visit(class Program*) = 0;
		virtual Value * visit(class BinaryOpExpression*) = 0;
		virtual Value * visit(class UnaryOpExpression*) = 0;
		virtual Value * visit(class MethodCall*) = 0;
		virtual Value * visit(class MethodArgInpList*) = 0;
		virtual Value * visit(class CalloutCall*) = 0;
		virtual Value * visit(class CalloutArgList*) = 0;
		virtual Value * visit(class TerminalVariable*) = 0;
		virtual Value * visit(class ArrayTerminalVariable*) = 0;
		virtual Value * visit(class FieldDeclList*) = 0;
		virtual Value * visit(class VariableList*) = 0;
		virtual Value * visit(class MethodDeclList*) = 0;
		virtual Function * visit(class MethodDecl*) = 0;
		virtual Value * visit(class ParamList*) = 0;
		virtual Value * visit(class Block*) = 0;
		virtual Value * visit(class StatementList*) = 0;
		virtual Value * visit(class AssignStmt*) = 0;
		virtual Value * visit(class IfElseStmt*) = 0;
		virtual Value * visit(class IfStmt*) = 0;
		virtual Value * visit(class ForStmt*) = 0;
		virtual Value * visit(class RetExpr*) = 0;
		virtual Value * visit(class StringRetBrkContStatement*) = 0;
		virtual Value * visit(class Location*) = 0;
		virtual Value * visit(class CalloutArg*) = 0;
		virtual Value * visit(class Literal*) = 0;
};

class SomeVisitor: public ASTVisitor {
	public:
		SomeVisitor() ;

		Value * visit(class Program*);
		Value * visit(class BinaryOpExpression*);
		Value * visit(class UnaryOpExpression*);
		Value * visit(class MethodCall*);
		Value * visit(class MethodArgInpList*);
		Value * visit(class CalloutCall*);
		Value * visit(class CalloutArgList*);
		Value * visit(class TerminalVariable*);
		Value * visit(class ArrayTerminalVariable*);
		Value * visit(class FieldDeclList*);
		Value * visit(class VariableList*);
		Value * visit(class MethodDeclList*);
		Function * visit(class MethodDecl*);
		Value * visit(class ParamList*);
		Value * visit(class Block*);
		Value * visit(class StatementList*);
		Value * visit(class AssignStmt*);
		Value * visit(class IfElseStmt*);
		Value * visit(class IfStmt*);
		Value * visit(class ForStmt*);
		Value * visit(class RetExpr*);
		Value * visit(class StringRetBrkContStatement*);
		Value * visit(class Location*);
		Value * visit(class CalloutArg*);
		Value * visit(class Literal*);
};

class SemanticVisitor: public ASTVisitor {
	public:
		// Data Structures needed for semantic checking
		class LogErrorClass* logger_class;

		SemanticVisitor(class LogErrorClass*) ;

		Value * visit(class Program*);
		Value * visit(class BinaryOpExpression*);
		Value * visit(class UnaryOpExpression*);
		Value * visit(class MethodCall*);
		Value * visit(class MethodArgInpList*);
		Value * visit(class CalloutCall*);
		Value * visit(class CalloutArgList*);
		Value * visit(class TerminalVariable*);
		Value * visit(class ArrayTerminalVariable*);
		Value * visit(class FieldDeclList*);
		Value * visit(class VariableList*);
		Value * visit(class MethodDeclList*);
		Function * visit(class MethodDecl*);
		Value * visit(class ParamList*);
		Value * visit(class Block*);
		Value * visit(class StatementList*);
		Value * visit(class AssignStmt*);
		Value * visit(class IfElseStmt*);
		Value * visit(class IfStmt*);
		Value * visit(class ForStmt*);
		Value * visit(class RetExpr*);
		Value * visit(class StringRetBrkContStatement*);
		Value * visit(class Location*);
		Value * visit(class CalloutArg*);
		Value * visit(class Literal*);
};

class CodeGenVisitor: public ASTVisitor {
	public:
		CodeGenVisitor(class LogErrorClass*) ;

		Value * visit(class Program*);
		Value * visit(class BinaryOpExpression*);
		Value * visit(class UnaryOpExpression*);
		Value * visit(class MethodCall*);
		Value * visit(class MethodArgInpList*);
		Value * visit(class CalloutCall*);
		Value * visit(class CalloutArgList*);
		Value * visit(class TerminalVariable*);
		Value * visit(class ArrayTerminalVariable*);
		Value * visit(class FieldDeclList*);
		Value * visit(class VariableList*);
		Value * visit(class MethodDeclList*);
		Function * visit(class MethodDecl*);
		Value * visit(class ParamList*);
		Value * visit(class Block*);
		Value * visit(class StatementList*);
		Value * visit(class AssignStmt*);
		Value * visit(class IfElseStmt*);
		Value * visit(class IfStmt*);
		Value * visit(class ForStmt*);
		Value * visit(class RetExpr*);
		Value * visit(class StringRetBrkContStatement*);
		Value * visit(class Location*);
		Value * visit(class CalloutArg*);
		Value * visit(class Literal*);
};

/* Base AST Node class, inherited by every other class */
class BaseAst {
	public:
		virtual Value * accept(ASTVisitor* v) = 0;
		// virtual Value* codegen() {}
};

class Program: public BaseAst {
	public:
		class FieldDeclList* field_decl;
		class MethodDeclList* method_decl;

		Program(class FieldDeclList*, class MethodDeclList*) ;

		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen(class LogErrorClass*);
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
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

class UnaryOpExpression: public Expr {
	public:
		string *op;
		class Expr* expr;

		UnaryOpExpression(string*, class Expr*) ;

		string get_expr_type() { return "UnaryOpExpression"; };
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

class MethodCall: public Expr, public Statement {
	public:
		class MethodArgInpList* args;
		class TerminalVariable* method_name;
		
		MethodCall(class TerminalVariable*) ;
		MethodCall(class TerminalVariable*, class MethodArgInpList*) ;

		string get_expr_type() { return "MethodCall"; };
		string get_statement_type() { return "MethodCall"; };
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

class MethodArgInpList: public BaseAst {
	public:
		vector<class Expr*> arg_list;

		MethodArgInpList() ;

		void push_back(class Expr*);
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		Value* codegen();
};

class CalloutCall: public Expr, public Statement {
	public:
		string *function_name;
		class CalloutArgList* args;
		
		CalloutCall(string*) ;
		CalloutCall(string*, class CalloutArgList*) ;

		string get_expr_type() { return "CalloutCall"; };
		string get_statement_type() { return "CalloutCall"; };
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

class CalloutArgList: public BaseAst {
	public:
		vector<class CalloutArg*> arg_list;

		CalloutArgList() ;

		void push_back(class CalloutArg*);
		Value * accept(ASTVisitor* v) { return v->visit(this); };
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
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

class CalloutArg: public BaseAst {
	public:
		class Expr* arg_expr;
		string *arg_string;
		string arg_type = "";

		CalloutArg(class Expr*) ;
		CalloutArg(string*) ;

		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

class TerminalVariable: public Expr {
	public:
		string *variable_name;
		
		TerminalVariable(string*) ;

		string get_expr_type() { return "TerminalVariable"; };
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		Value* codegen();
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
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int get_length() { return index_int; };
		int lineno;
		Value* codegen();
};

/* Field decleration
eg. int a, b, c; bool d, e;
*/

class FieldDeclList: public BaseAst {
	public:	
		vector<class VariableList*> all_declerations;
		
		FieldDeclList() ;
		
		void push_back(class VariableList*);
		Value * accept(ASTVisitor* v) { return v->visit(this); };
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
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		Value* codegen(bool, map<string, AllocaInst *> &);
};

class MethodDeclList: public BaseAst {
	public:	
		vector<class MethodDecl*> method_declerations_list;
		
		MethodDeclList() ;
		
		void push_back(class MethodDecl*);
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
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

		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		Function* codegen();
};

class ParamList: public BaseAst {
	public:	
		vector<pair<string*, class TerminalVariable*>> parameters_list;

		ParamList() ;

		void push_back(string*, class TerminalVariable*);
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		Value* codegen();
};

/* Statements */

// List class
class StatementList: public BaseAst {
	public:
		vector<class Statement*> statement_list;

		StatementList() ;

		bool has_return();
		bool has_return_expr();
		bool has_break();
		bool has_continue();
		void push_back(class Statement*);
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

class Block: public Statement {
	public:
		class FieldDeclList* decleration_list;
		class StatementList* statement_list;

		Block(class FieldDeclList*, class StatementList*) ;

		bool has_return();
		bool has_return_expr();
		bool has_break();
		bool has_continue();
		string get_statement_type() { return "Block"; }
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

// Specific Statement class
class AssignStmt: public Statement {
	public:
		class Location* left_part;
		string *op;
		class Expr* right_part;

		AssignStmt(class Location*, string*, class Expr*) ;

		string get_statement_type() { return "Assign"; }
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

// Specific Statement class
class IfElseStmt: public Statement {
	public:
		class Expr* cond;
		class Block* if_block;
		class Block* else_block;

		IfElseStmt(class Expr*, class Block*, class Block*) ;

		string get_statement_type() { return "IfElse"; }
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

// Specific Statement class
class IfStmt: public Statement {
	public:
		class Expr* cond;
		class Block* if_block;

		IfStmt(class Expr*, class Block*) ;

		string get_statement_type() { return "If"; }
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
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
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

// Specific Statement class
class RetExpr: public Statement {
	public:
		class Expr* expr;

		RetExpr(class Expr*) ;

		string get_statement_type() { return "RetExpr"; }
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
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
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
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
		Value * accept(ASTVisitor* v) { return v->visit(this); };
		int lineno;
		// Value* codegen();
};

#endif // __CLASS_DEF__

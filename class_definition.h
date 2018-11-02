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
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/raw_ostream.h>

using namespace std;
using namespace llvm;

/* Base AST Node class, inherited by every other class */
class BaseAst {
	public:
		virtual int accept(Visitor* v) {};
		virtual Value* codegen() {}
};

/* Final Variables */
class Expr: public BaseAst {
	public:
		Expr() {}
}

///////////////////////////////////////////////// DONT FORGET TO INHERIT TO EXPR:
/*

		ArrayTerminalVariable(class TerminalVariable*, class BinaryOpExpression*) {}
		ArrayTerminalVariable(class TerminalVariable*, class UnaryOpExpression*) {}
		ArrayTerminalVariable(class TerminalVariable*, class ArrayTerminalVariable*) {}
		ArrayTerminalVariable(class TerminalVariable*, class TerminalVariable*) {}
		ArrayTerminalVariable(class TerminalVariable*, class MethodCall*) {}
		ArrayTerminalVariable(class TerminalVariable*, class CalloutCall*) {}
		ArrayTerminalVariable(class TerminalVariable*, int) {}
		ArrayTerminalVariable(class TerminalVariable*, char) {}
		ArrayTerminalVariable(class TerminalVariable*, bool) {}
 */

class TerminalVariable: public Expr {
	public:
		string veriable_name;
		
		TerminalVariable(string) {}
};

class ArrayTerminalVariable: public Expr {
	public:
		ArrayTerminalVariable(class TerminalVariable*, class Expr*)
};

/* Field decleration
eg. int a, b, c; bool d, e;
*/

class FieldDeclList: public BaseAst {
	public:	
		vector<class VariableList*> all_declerations;
		
		FieldDeclList() {}
		
		void push_back(class VariableList*);
};

class VariableList: public BaseAst {
	public:	
		vector<class TerminalVariable*> declarations;
		vector<class ArrayTerminalVariable*> declarations_array;
		string decleration_type;
		
		VariableList() {}
		
		void push_back(class TerminalVariable*);
		void push_back(class ArrayTerminalVariable*);
		void set_type(string);
};

class MethodDeclList: public BaseAst {
	public:	
		vector<class MethodDecl*> method_declerations_list;
		
		MethodDeclList() {}
		
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

		MethodDecl(string, class TerminalVariable*, class ParamList*, class Block*) {}
		MethodDecl(string, class TerminalVariable*, class Block*) {}
};

class ParamList: public BaseAst {
	public:	
		vector<pair<string, class TerminalVariable*>> parameters_list;

		ParamList() {}

		void push_back(string, class TerminalVariable*);
};

class Block: public BaseAst {
	public:
		class DeclerationList* decleration_list;
		class StatementList* statement_list;

		Block(class DeclerationList*, class StatementList*) {}
};

/* Statements */

// List class
class StatementList: public BaseAst {
	public:
		vector<class Statment*> statement_list;

		StatementList() {}

		void push_back(class Statement*);
};

// Base class
class Statement: public BaseAst {
	public:
		int nothing;

		Statement() {}
};

// Specific Statement class
class AssignStmt: public Statement {
	public:
		AssignStmt(class TerminalVariable*, string, class Expr*) {}
		AssignStmt(class ArrayTerminalVariable*, string, class Expr*) {}
};

// Specific Statement class
class IfElseStmt: public Statement {
	public:
		IfElseStmt(class Expr*, class Block*, class Block*) {}
};

// Specific Statement class
class IfStmt: public Statement {
	public:
		IfStmt(class Expr*, class Block*) {}
};

// Specific Statement class
class ForStmt: public Statement {
	public:
		ForStmt(class TerminalVariable*, class Expr*, class Expr*, class Block*) {}
		ForStmt(class ArrayTerminalVariable*, class Expr*, class Expr*, class Block*) {}
};

// Specific Statement class
class RetExpr: public Statement {
	public:
		RetExpr(class Expr*) {}
};

/* Method call */

class MethodCall: public BaseAst {
	public:
		MethodCall() {}
		MethodCall() {class }
};
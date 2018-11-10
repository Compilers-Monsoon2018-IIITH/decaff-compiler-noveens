#include <bits/stdc++.h>
#include "class_definition.h"

using namespace std;

// Class-1
BinaryOpExpression::BinaryOpExpression(class Expr* _left, string _op, class Expr* _right)
: op(_op), left(_left), right(_right) {};

// Class-2
UnaryOpExpression::UnaryOpExpression(string _op, class Expr* _expr) 
: op(_op), expr(_expr) {};

// Class-3
MethodCall::MethodCall(class MethodArgInpList* _args) 
: args(_args) {};
MethodCall::MethodCall()
: MethodCall(new MethodArgInpList()) {};

// Class-4
MethodArgInpList::MethodArgInpList() {};
void MethodArgInpList::push_back(class Expr* arg) {
	arg_list.push_back(arg);
}

// Class-5
CalloutCall::CalloutCall(string _function_name, class CalloutArgList* _args) 
: function_name(_function_name), args(_args) {};
CalloutCall::CalloutCall(string _function_name)
: CalloutCall(_function_name, new CalloutArgList()) {};

// Class-6
CalloutArgList::CalloutArgList() {};
void CalloutArgList::push_back(class Expr* arg) {
	arg_list_expr.push_back(arg);
}
void CalloutArgList::push_back(string arg) {
	arg_list_string.push_back(arg);
}

// Class-7
ExprIntCharBool::ExprIntCharBool(int var)
: this_int(var) { what_type = "int"; };
ExprIntCharBool::ExprIntCharBool(char var)
: this_char(var) { what_type = "char"; };
ExprIntCharBool::ExprIntCharBool(bool var)
: this_bool(var) { what_type = "bool"; };

// Class-8
TerminalVariable::TerminalVariable(string _variable_name)
: variable_name(_variable_name) {};

// Class-9
ArrayTerminalVariable::ArrayTerminalVariable(class TerminalVariable* _arr_name, class Expr* _index)
: arr_name(_arr_name), index(_index) {};

// Class-10
FieldDeclList::FieldDeclList() {};
void FieldDeclList::push_back(class VariableList* decleration) {
	all_declerations.push_back(decleration);
}

// Class-11
VariableList::VariableList() {};
void VariableList::push_back(class TerminalVariable* var) {
	declarations.push_back(var);
}
void push_back(class ArrayTerminalVariable* var) {
	declarations_array.push_back(var);
}
void set_type(string type) {
	decleration_type = type;
}

// Class-12
MethodDeclList::MethodDeclList() {};
void MethodDeclList::push_back(class MethodDecl* decl) {
	method_declerations_list.push_back(decl);
}

// Class-13
MethodDecl::MethodDecl(string _return_type, class TerminalVariable* _method_name, class ParamList* param_list, class Block* _code_block) 
: return_type(_return_type), method_name(_method_name), param_list(_param_list), code_block(_code_block) {};
MethodDecl::MethodDecl(string _return_type, class TerminalVariable* _method_name, class Block* _code_block) 
: MethodDecl(_return_type, _method_name, new ParamList(), _code_block) {};

// Class-14
ParamList::ParamList() {};
void ParamList::push_back(string type, class TerminalVariable* var) {
	parameters_list.push_back(make_pair(type, var));
}

// Class-15
Block::Block(class DeclerationList* _decleration_list, class StatementList* _statement_list) 
: decleration_list(_decleration_list), statement_list(_statement_list) {};

// Class-16
StatementList::StatementList() {};
void StatementList::push_back(class Statement* statement) {
	statement_list.push_back(statement);
}

// Class-17
AssignStmt::AssignStmt(class TerminalVariable* _left, string _op, class Expr* _right) 
: left(_left), op(_op), right(_right) { left_type = "variable"; };
AssignStmt::AssignStmt(class ArrayTerminalVariable* _left, string _op, class Expr* _right) 
: left_arr(_left), op(_op), right(_right) { left_type = "array"; };

// Class-18
IfElseStmt::IfElseStmt(class Expr* _cond, class Block* _if_block, class Block* _else_block)
: cond(_cond), if_block(_if_block), else_block(_else_block) {};

// Class-19
IfStmt::IfStmt(class Expr* _cond, class Block* _if_block)
: cond(_cond), if_block(_if_block) {};

// Class-20
ForStmt::ForStmt(class TerminalVariable* _loop_var, class Expr* _start_cond, class Expr* _right_cond, class Block* _code_block)
: loop_var(_loop_var), start_cond(_start_cond), right_cond(_right_cond), code_block(_code_block) {};
ForStmt::ForStmt(class ArrayTerminalVariable* _loop_var, class Expr* _start_cond, class Expr* _right_cond, class Block* _code_block)
: loop_var_arr(_loop_var), start_cond(_start_cond), right_cond(_right_cond), code_block(_code_block) {};

// Class-21
RetExpr::RetExpr(class Expr* _expr)
: expr(_expr) {};

#include <bits/stdc++.h>
#include "class_definition.h"

using namespace std;

// Class-1
BinaryOpExpression::BinaryOpExpression(class Expr* _left, string *_op, class Expr* _right)
: op(_op), left(_left), right(_right) {};

// Class-2
UnaryOpExpression::UnaryOpExpression(string *_op, class Expr* _expr) 
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
CalloutCall::CalloutCall(string *_function_name, class CalloutArgList* _args) 
: function_name(_function_name), args(_args) {};
CalloutCall::CalloutCall(string *_function_name)
: CalloutCall(_function_name, new CalloutArgList()) {};

// Class-6
CalloutArgList::CalloutArgList() {};
void CalloutArgList::push_back(class CalloutArg* arg) {
	arg_list.push_back(arg);
}

//
CalloutArg::CalloutArg(class Expr* arg)
: arg_expr(arg) { arg_type = "expr"; };
CalloutArg::CalloutArg(string *arg)
: arg_string(arg) { arg_type = "string"; };

//
Location::Location(class TerminalVariable* _var_name)
: var_name(_var_name) { location_type = "variable"; };
Location::Location(class TerminalVariable* _var_name, class Expr* _index)
: var_name(_var_name), index(_index) { location_type = "array"; };

// Class-8
TerminalVariable::TerminalVariable(string *_variable_name)
: variable_name(_variable_name) {};

// Class-9
ArrayTerminalVariable::ArrayTerminalVariable(class TerminalVariable* _arr_name, class Expr* _index)
: arr_name(_arr_name), index(_index) { index_type = "expr"; };
ArrayTerminalVariable::ArrayTerminalVariable(class TerminalVariable* _arr_name, int _index)
: arr_name(_arr_name), index_int(_index) { index_type = "int"; };

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
void VariableList::push_back(class ArrayTerminalVariable* var) {
	declarations_array.push_back(var);
}
void VariableList::set_type(string *type) {
	decleration_type = type;
}

// Class-12
MethodDeclList::MethodDeclList() {};
void MethodDeclList::push_back(class MethodDecl* decl) {
	method_declerations_list.push_back(decl);
}

// Class-13
MethodDecl::MethodDecl(string *_return_type, class TerminalVariable* _method_name, class ParamList* _param_list, class Block* _code_block) 
: return_type(_return_type), method_name(_method_name), param_list(_param_list), code_block(_code_block) {};
MethodDecl::MethodDecl(string *_return_type, class TerminalVariable* _method_name, class Block* _code_block) 
: MethodDecl(_return_type, _method_name, new ParamList(), _code_block) {};

// Class-14
ParamList::ParamList() {};
void ParamList::push_back(string *type, class TerminalVariable* var) {
	parameters_list.push_back(make_pair(type, var));
}

// Class-15
Block::Block(class FieldDeclList* _decleration_list, class StatementList* _statement_list) 
: decleration_list(_decleration_list), statement_list(_statement_list) {};

// Class-16
StatementList::StatementList() {};
void StatementList::push_back(class Statement* stat) {
	statement_list.push_back(stat);
}

// Class-17
AssignStmt::AssignStmt(class Location* _left, string *_op, class Expr* _right) 
: left(_left), op(_op), right(_right) {};

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

// Class-22
StringRetBrkContStatement::StringRetBrkContStatement(string *_type)
: type(_type) {};

// Class-23
Program::Program(class FieldDeclList* _field_decl, class MethodDeclList* _method_decl)
: field_decl(_field_decl), method_decl(_method_decl) {};

//
Literal::Literal(int _lit_int)
: lit_int(_lit_int) { literal_type = "int"; };
Literal::Literal(string *_lit_string)
: lit_string(_lit_string) { literal_type = "string"; };

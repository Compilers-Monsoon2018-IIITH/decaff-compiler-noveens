#include <bits/stdc++.h>
#include "class_definition.h"
#include "colormod.h"

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT);

using namespace std;

SomeVisitor::SomeVisitor() {};

void SomeVisitor::visit(class Program* node) {
	cout << "\n\nEncountered Program node" << endl;
	node->field_decl->accept(this);
	node->method_decl->accept(this);
}

void SomeVisitor::visit(class BinaryOpExpression* node) {
	cout << "Binary Op Expression: ";
	cout << "Left Expr: "; node->left->accept(this);
	cout << ", Op: " << *(node->op);
	cout << ", Right Expr: "; node->right->accept(this);
}

void SomeVisitor::visit(class UnaryOpExpression* node) {
	cout << "Unary Op Expression: ";
	cout << "Op: " << *(node->op);
	cout << ", Expr: "; node->expr->accept(this);
}

void SomeVisitor::visit(class MethodCall* node) {
	cout << "Method call: ";
	cout << "Method name: "; node->method_name->accept(this); cout << endl;
	node->args->accept(this);
}

void SomeVisitor::visit(class MethodArgInpList* node) {
	int num = 1;
	for (auto arg: node->arg_list) {
		cout << "Method Arg #" << num << ": ";
		arg->accept(this);
		cout << ", ";
		num++;
	}
	cout << endl;
}

void SomeVisitor::visit(class CalloutCall* node) {
	cout << "Callout Call: ";
	cout << "function name: " << *(node->function_name);
	cout << "args: "; node->args->accept(this);
}

void SomeVisitor::visit(class CalloutArgList* node) {
	int num = 1;
	for (auto arg: node->arg_list) {
		cout << "Arg #" << num << ": ";
		arg->accept(this);
		// cout << endl;
		num++;
	}
}

void SomeVisitor::visit(class TerminalVariable* node) {
	cout << *(node->variable_name);
}

void SomeVisitor::visit(class ArrayTerminalVariable* node) {
	node->arr_name->accept(this);

	cout << " (With index: ";
	
	if (node->index_type == "int") cout << node->index_int << ")";
	else if (node->index_type == "expr") {
		node->index->accept(this);
		cout << ")";
	}
}

void SomeVisitor::visit(class FieldDeclList* node) {
	int decl_num = 1;
	for (auto decleration: node->all_declerations) {
		cout << "Field Decleration #" << decl_num << ": ";
		decleration->accept(this);
		decl_num++;
	}
}

void SomeVisitor::visit(class VariableList* node) {
	cout << "type: " << *(node->decleration_type) << " : ";
	
	for (auto normal: node->declarations) {
		normal->accept(this); cout << ", ";
	}
	for (auto normal: node->declarations_array) {
		normal->accept(this); cout << ", ";
	}
	cout << endl;
}

void SomeVisitor::visit(class MethodDeclList* node) {
	cout << "Encountered Method Decleration List node" << endl;
	
	int decl_num = 1;
	for (auto decleration: node->method_declerations_list) {
		cout << blue << "Method Decleration #" << decl_num << ": " << def;
		decleration->accept(this);
		decl_num++;
	}
}

void SomeVisitor::visit(class MethodDecl* node) {	
	cout << "Method name: ";
	node->method_name->accept(this);
	cout << ", return type: " << *(node->return_type);
	cout << ", parameter list: ";
	node->param_list->accept(this);
	cout << red << "Code block starts:\n" << def;
	node->code_block->accept(this);
	cout << red << "Code block ends\n\n" << def;
}

void SomeVisitor::visit(class ParamList* node) {
	for (auto param: node->parameters_list) {
		cout << *(param.first) << " ";
		param.second->accept(this);
		cout << ", ";
	}
	cout << endl;
}
void SomeVisitor::visit(class Block* node) {
	node->decleration_list->accept(this);
	node->statement_list->accept(this);
}
void SomeVisitor::visit(class StatementList* node) {
	int statement_num = 1;
	for (auto statement: node->statement_list) {
		cout << green << "Statement #" << statement_num << ":" << def << endl;
		statement->accept(this);
		statement_num++;
	}
}

void SomeVisitor::visit(class AssignStmt* node) {
	cout << "Assign statement: ";
	cout << "left: "; node->left_part->accept(this); cout << endl;
	cout << "op: " << *(node->op) << endl;
	cout << "right: "; node->right_part->accept(this); cout << endl;
}

void SomeVisitor::visit(class IfElseStmt* node) {
	cout << "If-else statement:" << endl;
	cout << "condition: "; node->cond->accept(this); cout << endl;
	cout << "if-block: " << endl; node->if_block->accept(this); cout << endl;
	cout << "else-block: " << endl; node->else_block->accept(this); cout << endl;
}

void SomeVisitor::visit(class IfStmt* node) {
	cout << "If statement (No else): " << endl;
	cout << "condition: "; node->cond->accept(this);
	cout << "if-block: " << endl; node->if_block->accept(this); cout << endl;
}

void SomeVisitor::visit(class ForStmt* node) {
	cout << "For statement: ";
	cout << "loop variable: "; node->loop_var->accept(this); cout << ", ";
	cout << "start condition: "; node->start_cond->accept(this); cout << ", ";
	cout << "end condition: "; node->right_cond->accept(this); cout << ", ";
	cout << "code block: "; node->code_block->accept(this); cout << endl;
}

void SomeVisitor::visit(class RetExpr* node) {
	cout << "Return statement: ";
	cout << "expression: "; node->expr->accept(this); cout << endl;
}

void SomeVisitor::visit(class StringRetBrkContStatement* node) {
	cout << *(node->type) << " statement" << endl;
}

void SomeVisitor::visit(class Location* node) {
	cout << "Location: ";
	if (node->location_type == "variable")
		node->var_name->accept(this);
	else if (node->location_type == "array") {
		node->var_name->accept(this); cout << "(With index: "; node->index->accept(this); cout << ")" << endl;
	}
}

void SomeVisitor::visit(class CalloutArg* node) {
	cout << "Callout statement: ";
	if (node->arg_type == "string")
		cout << *(node->arg_string) << endl;
	else if (node->arg_type == "expr") {
		node->arg_expr->accept(this); cout << endl;
	}
}

void SomeVisitor::visit(class Literal* node) {
	cout << "Literal: ";
	if (node->literal_type == "int") {
		cout << node->lit_int;
	}
	else if (node->literal_type == "string") {
		cout << *(node->lit_string);
	}
}

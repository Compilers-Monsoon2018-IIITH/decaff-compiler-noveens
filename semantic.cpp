#include <bits/stdc++.h>
#include "class_definition.h"

using namespace std;

SemanticVisitor::SemanticVisitor(class LogErrorClass* logger_class) {
	this->logger_class = logger_class;
};

void SemanticVisitor::visit(class Program* node) {
	node->field_decl->accept(this);
	node->method_decl->accept(this);
}

void SemanticVisitor::visit(class FieldDeclList* node) {
	int decl_num = 1;

	for (auto decleration: node->all_declerations) {

		decleration->accept(this);
		decl_num++;
	}
}

void SemanticVisitor::visit(class VariableList* node) {
	for (auto normal: node->declarations) {
		normal->accept(this);
	}

	for (auto normal: node->declarations_array) {
		normal->accept(this);
	}
}

void SemanticVisitor::visit(class TerminalVariable* node) {
}

void SemanticVisitor::visit(class ArrayTerminalVariable* node) {
	if (node->index_type == "int" && node->index_int <= 0) {
		this->logger_class->add("Array Capacity for '" + *(node->arr_name->variable_name) + "' should be greater than 0.");
	}
}

void SemanticVisitor::visit(class MethodDeclList* node) {
	bool main_defined = false;
	
	for (auto decleration: node->method_declerations_list) {
		if (*(decleration->method_name->variable_name) == "main") {
			main_defined = true;
			break;
		}
	}

	if (main_defined == false) {
		this->logger_class->add("Method 'main' not found.");
	}
}

void SemanticVisitor::visit(class MethodDecl* node) {	
	node->method_name->accept(this);
	node->param_list->accept(this);
	node->code_block->accept(this);
}

void SemanticVisitor::visit(class ParamList* node) {
	for (auto param: node->parameters_list) {
		param.second->accept(this);
	}
}

void SemanticVisitor::visit(class BinaryOpExpression* node) {
	node->left->accept(this);
	node->right->accept(this);
}

void SemanticVisitor::visit(class UnaryOpExpression* node) {
	node->expr->accept(this);
}

void SemanticVisitor::visit(class MethodCall* node) {
	node->method_name->accept(this);
	node->args->accept(this);
}

void SemanticVisitor::visit(class MethodArgInpList* node) {
	for (auto arg: node->arg_list) {
		arg->accept(this);
	}
}

void SemanticVisitor::visit(class CalloutCall* node) {
	node->args->accept(this);
}

void SemanticVisitor::visit(class CalloutArgList* node) {
	int num = 1;
	for (auto arg: node->arg_list) {
		arg->accept(this);
		num++;
	}
}

void SemanticVisitor::visit(class Block* node) {
	node->decleration_list->accept(this);
	node->statement_list->accept(this);
}

void SemanticVisitor::visit(class StatementList* node) {
	int statement_num = 1;
	for (auto statement: node->statement_list) {
		statement->accept(this);
		statement_num++;
	}
}

void SemanticVisitor::visit(class AssignStmt* node) {
	node->left_part->accept(this);
	node->right_part->accept(this);
}

void SemanticVisitor::visit(class IfElseStmt* node) {
	node->cond->accept(this);
	node->if_block->accept(this);
	node->else_block->accept(this);
}

void SemanticVisitor::visit(class IfStmt* node) {
	node->cond->accept(this);
	node->if_block->accept(this);
}

void SemanticVisitor::visit(class ForStmt* node) {
	node->loop_var->accept(this);
	node->start_cond->accept(this);
	node->right_cond->accept(this);
	node->code_block->accept(this);
}

void SemanticVisitor::visit(class RetExpr* node) {
	node->expr->accept(this);
}

void SemanticVisitor::visit(class StringRetBrkContStatement* node) {
}

void SemanticVisitor::visit(class Location* node) {
	if (node->location_type == "variable") {
		node->var_name->accept(this);
	}

	else if (node->location_type == "array") {
		node->var_name->accept(this);
		node->index->accept(this);
	}
}

void SemanticVisitor::visit(class CalloutArg* node) {
	if (node->arg_type == "expr") {
		node->arg_expr->accept(this);
	}
}

void SemanticVisitor::visit(class Literal* node) {
}
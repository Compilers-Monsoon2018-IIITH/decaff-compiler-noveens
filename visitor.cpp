#include <bits/stdc++.h>
#include "class_definition.h"

using namespace std;

SomeVisitor::SomeVisitor() {};

void SomeVisitor::visit(class Program* node) {
	cout << "Encountered Program node" << endl;
	node->field_decl->accept(this);
	node->method_decl->accept(this);
}
void SomeVisitor::visit(class BinaryOpExpression* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class UnaryOpExpression* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class MethodCall* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class MethodArgInpList* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class CalloutCall* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class CalloutArgList* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class TerminalVariable* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class ArrayTerminalVariable* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class FieldDeclList* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class VariableList* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class MethodDeclList* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class MethodDecl* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class ParamList* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class Block* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class StatementList* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class AssignStmt* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class IfElseStmt* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class IfStmt* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class ForStmt* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class RetExpr* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class StringRetBrkContStatement* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class Location* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class CalloutArg* node) {
	cout << "Encountered node" << endl;
}
void SomeVisitor::visit(class Literal* node) {
	cout << "Encountered node" << endl;
}
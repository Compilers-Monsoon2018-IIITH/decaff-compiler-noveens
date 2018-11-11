#include <bits/stdc++.h>
#include "class_definition.h"

using namespace std;

SomeVisitor::SomeVisitor() {};
void SomeVisitor::visit(class Program* node) {
	cout << "YAY!" << endl;
	// node->accept(*this);
}
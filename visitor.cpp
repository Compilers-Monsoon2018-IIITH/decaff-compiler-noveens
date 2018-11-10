#include <bits/stdc++.h>
#include "class_definition.h"

using namespace std;

class SomeVisitor: public ASTVisitor{
	public:
		void visit(class BaseAst& node) {
			node.accept(*this);
		}
};
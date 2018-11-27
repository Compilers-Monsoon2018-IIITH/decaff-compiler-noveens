#include <bits/stdc++.h>
#include "class_definition.h"

using namespace std;
using namespace llvm;

struct loop_struct {
    BasicBlock *afterBB, *checkBB, *beforeBB;
    Value *condition;
    string loopVariable;
    PHINode *phiVariable;
};

static LLVMContext Context;
static Module *LLVMmodule = new Module("Noveen's compiler for decaf", Context);
static IRBuilder<> MagicalBuilder(Context);
static map<string, AllocaInst *> CurrentScopeVariables; // Manages the scope
static stack<loop_struct*> loops;
static set<string> array_list;
static int current_function_ret_bits = -1;
class LogErrorClass* logger_class;

int call_stack_size = 0;
bool debug = false;

string debug_info() {
	string ret = "";
	for (int i=0;i<call_stack_size;i++) ret += "    "; // 4 spaces
	for (int i=0;i<4*call_stack_size;i+=4) ret[i] = '|';
	return ret;
}

CodeGenVisitor::CodeGenVisitor(class LogErrorClass* logger_class_in) {
    logger_class = logger_class_in;
};

void Program::print_llvm_ir() {
	LLVMmodule->print(llvm::errs(), nullptr);
}

AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, string VarName, string type) {
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    AllocaInst *alloca_instruction = nullptr;
    if (type == "int") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt32Ty(Context), 0, VarName);
    } 
	else if (type == "boolean") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt1Ty(Context), 0, VarName);
    }
    return alloca_instruction;
}

Value *CodeGenVisitor::visit(Program *node) {
// Value *Program::codegen(class LogErrorClass* logger_class_carried_on) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: Program" << endl << flush;
		call_stack_size ++;
	}

	// Just to pass to the function, no use
	map<string, AllocaInst *> _;
    
    Value *V = node->field_decl->codegen(true, _);
    if (V == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: Program" << endl << flush;
	    }
        return nullptr;
    }
    
    V = node->method_decl->accept(this);
    if (V == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: Program" << endl << flush;
	    }
        return nullptr;
    }
    
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: Program" << endl << flush;
    }
    
    if (logger_class->all_errors.size() == 0) {
    	node->print_llvm_ir();
    }
    
    return V;
}

Value *FieldDeclList::codegen(bool is_global_scope, map<string, AllocaInst *> &Old_vals) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: FieldDeclList" << endl << flush;
		call_stack_size ++;
	}

	Value *v = ConstantInt::get(Context, APInt(32, 1));
    for (auto decleration : all_declerations) {
        v = decleration->codegen(is_global_scope, Old_vals);
        if (v == nullptr) {
        	if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: FieldDeclList" << endl << flush;
		    }
        	return v;
        }
    }
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: FieldDeclList" << endl << flush;
    }
    return v;
}

Value *VariableList::codegen(bool is_global_scope, map<string, AllocaInst *> &Old_vals) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: VariableList" << endl << flush;
		call_stack_size ++;
	}

    llvm::Type *ty = nullptr;
    if (*(decleration_type) == "int") {
		ty = Type::getInt32Ty(Context);
	}
	else if (*(decleration_type) == "boolean") {
    	ty = Type::getInt1Ty(Context);
    }
    else {
    	logger_class->add("Allowed declerations are only 'int' and 'boolean'\n'" + *(decleration_type) + "' is not allowed.", this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: VariableList" << endl << flush;
	    }
    	return (Value *) nullptr;
    }

    for (auto var : declarations) {

    	if (is_global_scope == true) {
            // Global Variable
			GlobalVariable *gv = LLVMmodule->getNamedGlobal(*(var->variable_name));
			if (gv != nullptr) {
				logger_class->add("Variable '" + *(var->variable_name) + "' redefined.", this->lineno);
				continue;
			}
    		
    		gv = new GlobalVariable(
    			*(LLVMmodule), ty, false,
                GlobalValue::ExternalLinkage, nullptr,
                *(var->variable_name)
            );
            gv->setInitializer(Constant::getNullValue(ty));
    	}
    	else {
    		// Local Variable
    		if (CurrentScopeVariables.find(*(var->variable_name)) != CurrentScopeVariables.end()) {
    			logger_class->add("Variable '" + *(var->variable_name) + "' redefined.", this->lineno);
    			if (debug == true) {
			    	call_stack_size --;
			    	cout << debug_info() << "Out codegen of: VariableList" << endl << flush;
			    }
				return nullptr;
    		}
    		Function *TheFunction = MagicalBuilder.GetInsertBlock()->getParent();
    		Value *initval;
    		if (*(decleration_type) == "int") {
	    		initval = ConstantInt::get(Context, APInt(32, 0));
    		}
    		else if (*(decleration_type) == "boolean") {
    			initval = ConstantInt::get(Context, APInt(1, 0));
    		}
            AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, *(var->variable_name), *(decleration_type));

            MagicalBuilder.CreateStore(initval, Alloca);
	        Old_vals[*(var->variable_name)] = CurrentScopeVariables[*(var->variable_name)];
	        CurrentScopeVariables[*(var->variable_name)] = Alloca;
    	}
    }

    for (auto arr: declarations_array) {

        if (is_global_scope) {
            // Global Array
            array_list.insert(*(arr->arr_name->variable_name));

        	GlobalVariable *gv = LLVMmodule->getNamedGlobal(*(arr->arr_name->variable_name));
			if (gv != nullptr) {
				logger_class->add("Array '" + *(arr->arr_name->variable_name) + "' redefined.", this->lineno);
				continue;
			}
            
            ArrayType *arrType = ArrayType::get(ty, arr->get_length());
            gv = new GlobalVariable(
            	*(LLVMmodule), arrType, false,
                GlobalValue::ExternalLinkage, nullptr,
                *(arr->arr_name->variable_name)
            );
            gv->setInitializer(ConstantAggregateZero::get(arrType));
        } 
        else {
        	// Local Array (Not Allowed)
        	logger_class->add("Array declerations are only allowed in the global scope.", this->lineno);
        	if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: VariableList" << endl << flush;
		    }
	    	return nullptr;
        }
    }
    Value *v = ConstantInt::get(Context, APInt(32, 1));
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: VariableList" << endl << flush;
    }
    return v;
}

Value * CodeGenVisitor::visit(class MethodDeclList * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: MethodDeclList" << endl << flush;
		call_stack_size ++;
	}

    Value *V = ConstantInt::get(Context, APInt(32, 0));
    for (auto method : node->method_declerations_list) {
        V = method->accept(this);
        if (V == nullptr) {
        	if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: MethodDeclList" << endl << flush;
		    }
        	return V;
        }
    }
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: MethodDeclList" << endl << flush;
    }
    return V;
}

Function * CodeGenVisitor::visit(MethodDecl * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: MethodDecl" << endl << flush;
		call_stack_size ++;
	}

    if (*(node->return_type) == "void") current_function_ret_bits = 0;
    if (*(node->return_type) == "int") current_function_ret_bits = 32;
    if (*(node->return_type) == "boolean") current_function_ret_bits = 1;

    vector<string> param_var_names;
    vector<string> param_var_types;
    vector<Type *> arguments;
    Type *returnType;

    for (auto param : node->param_list->parameters_list) {
        if (*(param.first) == "int") {
            arguments.push_back(Type::getInt32Ty(Context));
        } 
        else if (*(param.first) == "boolean") {
            arguments.push_back(Type::getInt1Ty(Context));
        } 
        else {
            logger_class->add("Allowed Function Arguments are only 'int' and 'boolean'\n'" + *(param.first) + "' is not allowed.", node->lineno);
            if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: MethodDecl" << endl << flush;
		    }

            current_function_ret_bits = -1;

            return nullptr;
        }
        param_var_types.push_back(*(param.first));
        param_var_names.push_back(*(param.second->variable_name));
    }

    if (*(node->return_type) == "int") {
        returnType = Type::getInt32Ty(Context);
    } 
    else if (*(node->return_type) == "boolean") {
        returnType = Type::getInt1Ty(Context);
    } 
    else if (*(node->return_type) == "void") {
        returnType = Type::getVoidTy(Context);
    } 
    else {
    	logger_class->add("Function " + *(node->method_name->variable_name) + "'s return type: '" + *(node->return_type) + "' is not allowed.", node->lineno);
        if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: MethodDecl" << endl << flush;
	    }

        current_function_ret_bits = -1;

        return nullptr;
    }

    FunctionType *FT = llvm::FunctionType::get(returnType, arguments, false);
    Function *F = llvm::Function::Create(FT, Function::ExternalLinkage, *(node->method_name->variable_name), LLVMmodule);

    int Idx = 0;
    for (Function::arg_iterator AI = F->arg_begin(); Idx != node->param_list->parameters_list.size(); ++AI, ++Idx) {
        AI->setName(param_var_names[Idx]);
    }

    BasicBlock *BB = BasicBlock::Create(Context, "entry", F);
    MagicalBuilder.SetInsertPoint(BB);
    Idx = 0;

    // Adding the method arguments to the current scope
    map<string, AllocaInst *> Old_vals;
    for (auto v: CurrentScopeVariables) {
    	Old_vals[v.first] = v.second;
    }

    for (auto &Arg : F->args()) {
        AllocaInst *Alloca = CreateEntryBlockAlloca(F, param_var_names[Idx], param_var_types[Idx]);
        MagicalBuilder.CreateStore(&Arg, Alloca);
        CurrentScopeVariables[param_var_names[Idx]] = Alloca;
        Idx++;
    }

    Value *RetVal = node->code_block->accept(this);

    // Resetting the scope
    CurrentScopeVariables.clear();
    for (auto v: Old_vals) {
    	CurrentScopeVariables[v.first] = Old_vals[v.first];
    }

    if (RetVal) {
        verifyFunction(*F);
        if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: MethodDecl" << endl << flush;
	    }

        current_function_ret_bits = -1;

        return F;
    }

    F->eraseFromParent();
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: MethodDecl" << endl << flush;
    }

    current_function_ret_bits = -1;

    return nullptr;
}

Value * CodeGenVisitor::visit(class Block * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: Block" << endl << flush;
		call_stack_size ++;
	}

    Value *V;
    map<string, AllocaInst *> Old_vals;
    
    V = node->decleration_list->codegen(false, Old_vals);
    if (V == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: Block" << endl << flush;
	    }
        return V;
    }
    
    V = node->statement_list->accept(this);
    if (V == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: Block" << endl << flush;
	    }
        return V;
    }

    for (auto val: Old_vals) {
    	CurrentScopeVariables[val.first] = Old_vals[val.first];
    }
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: Block" << endl << flush;
    }
    return V;
}

Value * CodeGenVisitor::visit(class StatementList * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: StatementList" << endl << flush;
		call_stack_size ++;
	}

	Value *v = ConstantInt::get(Context, llvm::APInt(32, 1));
    for (auto statement : node->statement_list) {
        v = statement->accept(this);
        if (statement->get_statement_type() == "Break") break;
        if (statement->get_statement_type() == "Continue") break;
    }
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: StatementList" << endl << flush;
    }
	return v;
}

Value * CodeGenVisitor::visit(class AssignStmt * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: AssignStmt" << endl << flush;
		call_stack_size ++;
	}

    Value *cur = CurrentScopeVariables[*(node->left_part->var_name->variable_name)];
    if (cur == nullptr) {
        cur = LLVMmodule->getGlobalVariable(*(node->left_part->var_name->variable_name));
    }
    if (cur == nullptr) {
    	logger_class->add("Unknown Variable Name '" + *(node->left_part->var_name->variable_name) + "' while assigning.", node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: AssignStmt" << endl << flush;
	    }
    	return nullptr;
    }

    Value *val = node->right_part->accept(this);
    if (node->right_part->get_expr_type() == "MethodCall") {
        // Ensure the corresponding method returns something (int / bool)
        Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) node->right_part)->method_name->variable_name));
        if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
            logger_class->add("Function return type should not be void", node->lineno);
        }
    }
    if (node->right_part->get_expr_type() == "Location") {
    	val = MagicalBuilder.CreateLoad(val);
    }

    Value *lhs = node->left_part->accept(this);
    cur = MagicalBuilder.CreateLoad(lhs);

    if (val == nullptr) {
    	logger_class->add("Error in RHS of assignment statement.", node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: AssignStmt" << endl << flush;
	    }
    	return nullptr;
    }

    if(*(node->op) == "="){
        auto l = lhs->getType();
        auto r = val->getType();
        if(l->isPointerTy()) l = l->getContainedType(0);
        if(r->isPointerTy()) r = r->getContainedType(0);
        if (l == r){
            // This is okay.
        }   
        else{
            logger_class->add("Invalid Operand for Assignment operation: '"+ *(node->op) + "', lhs and rhs must have same type.", node->lineno);
            return nullptr;
        }
    }

    Value *temp = ConstantInt::get(Context,APInt(32,0));
    if(*(node->op) == "+=" || *(node->op) == "-="){
        auto l = lhs->getType();
        auto r = val->getType();
        if(l->isPointerTy()) l = l->getContainedType(0);
        if(r->isPointerTy()) r = r->getContainedType(0);
        if (l == r && l == temp->getType()){
            // This is okay.
        }   
        else{
            logger_class->add("Invalid Operand for Assignment operation: '"+ *(node->op) + "', rhs must have 'int' type.", node->lineno);
            return nullptr;
        }
    }

    if (*(node->op) == "+=") {
        val = MagicalBuilder.CreateAdd(cur, val, "addEqualToTmp");
    } 
    else if (*(node->op) == "-=") {
        val = MagicalBuilder.CreateSub(cur, val, "subEqualToTmp");
    }
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: AssignStmt" << endl << flush;
    }
    return MagicalBuilder.CreateStore(val, lhs);
}

Value * CodeGenVisitor::visit(class Literal * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: Literal" << endl << flush;
		call_stack_size ++;
	}

	Value *v;
    if (node->literal_type == "int") {
	    v = ConstantInt::get(Context, llvm::APInt(32, static_cast<uint64_t>(node->lit_int)));
	}
	else if (node->literal_type == "boolean") {
	    v = ConstantInt::get(Context, llvm::APInt(1, node->lit_bool));
	}
	else if (node->literal_type == "string") {
	    v = MagicalBuilder.CreateGlobalStringPtr(*(node->lit_string));
	}
	
    if (debug == true) {
		call_stack_size --;
		cout << debug_info() << "Out codegen of: Literal" << endl << flush;
	}
    
    return v;
}

Value * CodeGenVisitor::visit(class Location * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: Location" << endl << flush;
		call_stack_size ++;
	}

    Value *V = CurrentScopeVariables[*(node->var_name->variable_name)];
    if (V == nullptr) {
        V = LLVMmodule->getNamedGlobal(*(node->var_name->variable_name));
    }
    if (V == nullptr) {
        logger_class->add("Unknown Variable Name '" + *(node->var_name->variable_name) + "' while assigning.", node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: Location" << endl << flush;
	    }
    	return nullptr;
    }
    if (node->location_type == "variable") {
    	if (debug == true) {
    		call_stack_size --;
    		cout << debug_info() << "Out codegen of: Location" << endl << flush;
    	}
        return V;
    }

    if (node->index == nullptr) {
    	logger_class->add("Invalid array index", node->lineno);
        return nullptr;
    }

    if (array_list.find(*(node->var_name->variable_name)) == array_list.end()) {
        logger_class->add("'" + (*(node->var_name->variable_name)) + "' is not an array variable", node->lineno);
        if (debug == true) {
            call_stack_size --;
            cout << debug_info() << "Out codegen of: Location" << endl << flush;
        }
        return nullptr;
    }
    
    Value *index_val = node->index->accept(this);

    int final_ans = index_val->getType()->getPrimitiveSizeInBits();
    if (final_ans == 0) {
        // Means is a variable / expression type
        final_ans = index_val->getType()->getContainedType(0)->getPrimitiveSizeInBits();
    }
    if (final_ans != 32) {
        logger_class->add("Array index should be an integer", node->lineno);
    }
    
    if (node->index->get_expr_type() == "MethodCall") {
        // Ensure the corresponding method returns something (int / bool)
        Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) node->index)->method_name->variable_name));
        if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
            logger_class->add("Function return type should not be void", node->lineno);
        }
    }
    if (node->index->get_expr_type() == "Location") {
    	index_val = MagicalBuilder.CreateLoad(index_val);
    }
    
    if (index_val == nullptr) {
    	logger_class->add("Invalid array index", node->lineno);
    }
    vector<Value *> array_index;
    array_index.push_back(MagicalBuilder.getInt32(0));
    array_index.push_back(index_val);
    V = MagicalBuilder.CreateGEP(V, array_index, (*(node->var_name->variable_name)) + "_Index");
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: Location" << endl << flush;
    }
    return V;
}

Value * CodeGenVisitor::visit(class IfElseStmt * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: IfElseStmt" << endl << flush;
		call_stack_size ++;
	}

    Value *val_cond = node->cond->accept(this);
    if (val_cond == nullptr) {
    	logger_class->add("Invalid condition in the IF statement.", node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: IfElseStmt" << endl << flush;
	    }
    	return nullptr;
    }

    Function *TheFunction = MagicalBuilder.GetInsertBlock()->getParent();
    BasicBlock *ifBlock = BasicBlock::Create(Context, "if", TheFunction);
    BasicBlock *elseBlock = BasicBlock::Create(Context, "else");
    BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont");
    BasicBlock *otherBlock = elseBlock;
    
    bool ret_if = node->if_block->has_return(), ret_else = false;
    bool break_if = node->if_block->has_break(), break_else = node->else_block->has_break();
    
    if (node->else_block == nullptr) {
        otherBlock = nextBlock;
    }
    MagicalBuilder.CreateCondBr(val_cond, ifBlock, otherBlock);
    MagicalBuilder.SetInsertPoint(ifBlock);

    Value *if_val = node->if_block->accept(this);
    if (if_val == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: IfElseStmt" << endl << flush;
	    }
        return nullptr;
    }

    if (!ret_if && !break_if && !node->if_block->has_continue()) {
        MagicalBuilder.CreateBr(nextBlock);
    }

    ifBlock = MagicalBuilder.GetInsertBlock();

    Value *else_val = nullptr;
    if (node->else_block != nullptr) {
        TheFunction->getBasicBlockList().push_back(elseBlock);
        MagicalBuilder.SetInsertPoint(elseBlock);
        else_val = node->else_block->accept(this);
        if (else_val == nullptr) {
        	if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: IfElseStmt" << endl << flush;
		    }
            return nullptr;
        }

        ret_else = node->else_block->has_return();
        if (!ret_else && !break_else && !node->else_block->has_continue()) {
            MagicalBuilder.CreateBr(nextBlock);
        }
    }

    TheFunction->getBasicBlockList().push_back(nextBlock);
    MagicalBuilder.SetInsertPoint(nextBlock);
    if (ret_else && ret_if) {
        Type *retType = MagicalBuilder.GetInsertBlock()->getParent()->getReturnType();
        if (retType == Type::getVoidTy(Context))
            MagicalBuilder.CreateRetVoid();
        else {
            MagicalBuilder.CreateRet(ConstantInt::get(Context, APInt(32, 0)));
        }
    }

    Value *V = ConstantInt::get(Context, APInt(32, 0));
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: IfElseStmt" << endl << flush;
    }
    return V;
}

Value * CodeGenVisitor::visit(class IfStmt * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: IfStmt" << endl << flush;
		call_stack_size ++;
	}

	Value *val_cond = node->cond->accept(this);
    if (val_cond == nullptr) {
    	logger_class->add("Invalid condition in the IF statement.", node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: IfStmt" << endl << flush;
	    }
    	return nullptr;
    }
    int final_ans = val_cond->getType()->getPrimitiveSizeInBits();
    if (final_ans == 0) {
        // Means is a variable / expression type
        final_ans = val_cond->getType()->getContainedType(0)->getPrimitiveSizeInBits();
    }
    if (final_ans != 1) {
        logger_class->add("Condition inside an if-else statement must be a boolean.", node->lineno);
        return nullptr;
    }

    Function *TheFunction = MagicalBuilder.GetInsertBlock()->getParent();
    BasicBlock *ifBlock = BasicBlock::Create(Context, "if", TheFunction);
    BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont");
    
    bool ret_if = node->if_block->has_return();
    bool break_if = node->if_block->has_break();
    
    MagicalBuilder.CreateCondBr(val_cond, ifBlock, nextBlock);
    MagicalBuilder.SetInsertPoint(ifBlock);

    Value *if_val = node->if_block->accept(this);
    if (if_val == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: IfStmt" << endl << flush;
	    }
        return nullptr;
    }

    if (!ret_if && !break_if && !node->if_block->has_continue()) {
        MagicalBuilder.CreateBr(nextBlock);
    }

    ifBlock = MagicalBuilder.GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(nextBlock);
    MagicalBuilder.SetInsertPoint(nextBlock);

    Value *V = ConstantInt::get(Context, APInt(32, 0));
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: IfStmt" << endl << flush;
    }
    return V;
}

Value * CodeGenVisitor::visit(class ForStmt * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: ForStmt" << endl << flush;
		call_stack_size ++;
	}
	
	// Checking if the loop var is redeclared
	if (CurrentScopeVariables.find(*(node->loop_var->variable_name)) != CurrentScopeVariables.end()) {
		if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
	    }
	    logger_class->add("Loop variable '" + (*(node->loop_var->variable_name)) + "' is redeclared.", node->lineno);
        return nullptr;
	}

    Function *TheFunction = MagicalBuilder.GetInsertBlock()->getParent();
    
    // Creating the loop variable
    llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, *(node->loop_var->variable_name), string("int"));
    llvm::AllocaInst *OldVal = CurrentScopeVariables[*(node->loop_var->variable_name)];
    CurrentScopeVariables[*(node->loop_var->variable_name)] = Alloca;

    Value *start = node->start_cond->accept(this);
    if (start == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
	    }
	    logger_class->add("For loop start condition error.", node->lineno);
        return nullptr;
    }

    // Check if start is int
    int final_ans = start->getType()->getPrimitiveSizeInBits();
    if (final_ans == 0) {
        final_ans = start->getType()->getContainedType(0)->getPrimitiveSizeInBits();
    }
    if (final_ans != 32) {
        logger_class->add("Loop start condition should be of type 'int'.", node->lineno);
        return nullptr;
    }

    if (node->start_cond->get_expr_type() == "MethodCall") {
        // Ensure the corresponding method returns something (int / bool)
        Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) node->start_cond)->method_name->variable_name));
        if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
            logger_class->add("Function return type should not be void", node->lineno);
            return nullptr;
        }
    }
    if (node->start_cond->get_expr_type() == "Location") {
        start = MagicalBuilder.CreateLoad(start);
    }

    // Loop var
    MagicalBuilder.CreateStore(start, Alloca);

    Value *step_val = ConstantInt::get(Context, APInt(32, 1));
    BasicBlock *pre_header_basic_block = MagicalBuilder.GetInsertBlock();

    BasicBlock *beforeBB = BasicBlock::Create(Context, "beforeloop", TheFunction);
    BasicBlock *loop_body = BasicBlock::Create(Context, "loop", TheFunction);
    BasicBlock *afterBB = BasicBlock::Create(Context, "afterloop", TheFunction);

    MagicalBuilder.CreateBr(beforeBB);
    MagicalBuilder.SetInsertPoint(beforeBB);

    PHINode *Variable = MagicalBuilder.CreatePHI(Type::getInt32Ty(Context), 2, *(node->loop_var->variable_name));
    Variable->addIncoming(start, pre_header_basic_block);
    
    Value *cond = node->right_cond->accept(this);
    if (cond == nullptr) {
    	logger_class->add("Invalid ending condition provided - for loop.", node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
	    }
    	return nullptr;
    }

    // Check if end is int
    final_ans = cond->getType()->getPrimitiveSizeInBits();
    if (final_ans == 0) {
        final_ans = cond->getType()->getContainedType(0)->getPrimitiveSizeInBits();
    }
    if (final_ans != 32) {
        logger_class->add("Loop end condition should be of type 'int'.", node->lineno);
        return nullptr;
    }

    if (node->right_cond->get_expr_type() == "MethodCall") {
        // Ensure the corresponding method returns something (int / bool)
        Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) node->right_cond)->method_name->variable_name));
        if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
            logger_class->add("Function return type should not be void", node->lineno);
        }
    }
    if (node->right_cond->get_expr_type() == "Location") {
        cond = MagicalBuilder.CreateLoad(cond);
    }
    
    // Pushing to the loop stack
    auto this_loop = new loop_struct();
    this_loop->beforeBB = beforeBB;
    this_loop->afterBB = afterBB;
    this_loop->checkBB = loop_body;
    this_loop->condition = cond;
    this_loop->loopVariable = *(node->loop_var->variable_name);
    this_loop->phiVariable = Variable;
    loops.push(this_loop);

    // Manually enforcing the loop stop condition
    cond = MagicalBuilder.CreateICmpSLT(Variable, cond, "loopcondition");
    MagicalBuilder.CreateCondBr(cond, loop_body, afterBB);
    MagicalBuilder.SetInsertPoint(loop_body);

    if (node->code_block->accept(this) == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
	    }
        return nullptr;
    }

    if (!node->code_block->has_break() && !node->code_block->has_continue()) {
        Value *cur = Variable;
        Value *next_val = MagicalBuilder.CreateAdd(cur, step_val, "NextVal");
        MagicalBuilder.CreateStore(next_val, Alloca);
        // cond = MagicalBuilder.CreateICmpSLT(next_val, cond, "loopcondition");
        BasicBlock *loopEndBlock = MagicalBuilder.GetInsertBlock();
        MagicalBuilder.CreateBr(beforeBB);
        Variable->addIncoming(next_val, loopEndBlock);
    }

    MagicalBuilder.SetInsertPoint(afterBB);

    if (OldVal) {
        CurrentScopeVariables[*(node->loop_var->variable_name)] = OldVal;
    } else {
        CurrentScopeVariables.erase(*(node->loop_var->variable_name));
    }

    loops.pop();

    llvm::Value *V = ConstantInt::get(Context, APInt(32, 1));
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
    }
    return V;
}

Value * CodeGenVisitor::visit(class RetExpr * node) {

	if (debug == true) {
		cout << debug_info() << "In codegen of: RetExpr" << endl << flush;
		call_stack_size ++;
	}

    Value *V = node->expr->accept(this);

    int final_ans = V->getType()->getPrimitiveSizeInBits();
    if (final_ans == 0) {
        // Means is a variable / expression type
        final_ans = V->getType()->getContainedType(0)->getPrimitiveSizeInBits();
    }

    if (current_function_ret_bits != final_ans) {
        logger_class->add("Return statement doesn't match function's return type.", node->lineno);

        if (debug == true) {
            call_stack_size --;
            cout << debug_info() << "Out codegen of: RetExpr" << endl << flush;
        }

        return nullptr;
    }

    if (node->expr->get_expr_type() == "MethodCall") {
        // Ensure the corresponding method returns something (int / bool)
        Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) node->expr)->method_name->variable_name));
        if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
            logger_class->add("Function return type should not be void", node->lineno);
        }
    }
    if (node->expr->get_expr_type() == "Location") {
        V = MagicalBuilder.CreateLoad(V);
    }
    MagicalBuilder.CreateRet(V);
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: RetExpr" << endl << flush;
    }
    return V;
}

Value * CodeGenVisitor::visit(class StringRetBrkContStatement * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: StringRetBrkContStatement" << endl << flush;
		call_stack_size ++;
	}

	Value *V;
	if (*(node->type) == "return") {
		MagicalBuilder.CreateRetVoid();
	}
	else if (*(node->type) == "break") {
		V = ConstantInt::get(Context, llvm::APInt(32, 1));
		if (loops.size() == 0) {
			logger_class->add("Invalid 'break' statement - not inside a loop.", node->lineno);
			if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: StringRetBrkContStatement" << endl << flush;
		    }
	    	return nullptr;
		}
	    loop_struct *currentLoop = loops.top();
	    MagicalBuilder.CreateBr(currentLoop->afterBB);
	}
	else if (*(node->type) == "continue") {
		V = ConstantInt::get(Context, llvm::APInt(32, 1));
		if (loops.size() == 0) {
			logger_class->add("Invalid 'continue' statement - not inside a loop.", node->lineno);
			if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: StringRetBrkContStatement" << endl << flush;
		    }
	    	return nullptr;
		}
	    loop_struct *currentLoop = loops.top();
	            
        string var = currentLoop->loopVariable;
        AllocaInst *Alloca = CurrentScopeVariables[var];
        Value *step_val = ConstantInt::get(Context, APInt(32, 1));
        Value *cur = MagicalBuilder.CreateLoad(Alloca, var);
        Value *next_val = MagicalBuilder.CreateAdd(cur, step_val, "NextVal");
        MagicalBuilder.CreateStore(next_val, Alloca);
        
        MagicalBuilder.CreateBr(currentLoop->beforeBB);
        currentLoop->phiVariable->addIncoming(next_val, currentLoop->checkBB);
	}
    
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: StringRetBrkContStatement" << endl << flush;
    }
    return V;
}

Value * CodeGenVisitor::visit(class BinaryOpExpression * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: BinaryOpExpression" << endl << flush;
		call_stack_size ++;
	}

    Value *value_left = node->left->accept(this);
    Value *value_right = node->right->accept(this);

    // arith op, rel op
    Value *temp = ConstantInt::get(Context,APInt(32,0));
    if (*(node->op) == "+" || *(node->op) == "-" || *(node->op) == "*" || *(node->op) == "/" || *(node->op) == "%" ||*(node->op) == "<" || *(node->op) == ">" || *(node->op) == ">=" || *(node->op) == "<=") {
        auto l = value_left->getType();
        auto r = value_right->getType();
        if(l->isPointerTy()) l = l->getContainedType(0);
        if(r->isPointerTy()) r = r->getContainedType(0);
        if (l != temp->getType() || r != temp->getType()){
            logger_class->add("Invalid Operand for binary operation: '"+ *(node->op) + "' , should be int", node->lineno);
            return nullptr;
        }
    }

    // eq_ops
    Value * temp1 = ConstantInt::get(Context,APInt(1,0));
    if (*(node->op) == "==" || *(node->op) == "!=") {
        auto l = value_left->getType();
        auto r = value_right->getType();
        if(l->isPointerTy()) l = l->getContainedType(0);
        if(r->isPointerTy()) r = r->getContainedType(0);
        if (l == r && (l==temp1->getType() || r==temp->getType())) {
            // This is okay.
        }    
        else{
            logger_class->add("Invalid Operand for Equal operation: '"+ *(node->op) + "' , should be int or boolean", node->lineno);
            return nullptr;
        }
    }

    // cond_ops
    if(*(node->op) == "&&" || *(node->op) == "||"){
        auto l = value_left->getType();
        auto r = value_right->getType();
        if(l->isPointerTy()) l = l->getContainedType(0);
        if(r->isPointerTy()) r = r->getContainedType(0);
        if (l == r && l==temp1->getType()) {
            // This is okay.
        }    
        else{
            logger_class->add("Invalid Operand for Conditional operation: '"+ *(node->op) + "', should be boolean", node->lineno);
            return nullptr;
        }
    }

    if (node->left->get_expr_type() == "MethodCall") {
        // Ensure the corresponding method returns something (int / bool)
        Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) left)->method_name->variable_name));
        if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
            logger_class->add("Function return type should not be void", node->lineno);
        }
    }
    if (node->left->get_expr_type() == "Location") {
        value_left = MagicalBuilder.CreateLoad(value_left);
    }
    if (node->right->get_expr_type() == "MethodCall") {
        // Ensure the corresponding method returns something (int / bool)
        Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) right)->method_name->variable_name));
        if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
            logger_class->add("Function return type should not be void", node->lineno);
        }
    }
    if (node->right->get_expr_type() == "Location") {
        value_right = MagicalBuilder.CreateLoad(value_right);
    }

    if (value_left == 0) {
    	logger_class->add("Error in LHS of binary op expression.", node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: BinaryOpExpression" << endl << flush;
	    }
    	return nullptr;
    } 
    else if (value_right == 0) {
    	logger_class->add("Error in RHS of binary op expression.", node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: BinaryOpExpression" << endl << flush;
	    }
    	return nullptr;
    }
    
    Value *v = nullptr;
    if (*(node->op) == "+") {
        v = MagicalBuilder.CreateAdd(value_left, value_right, "addtmp");
    } 
    else if (*(node->op) == "-") {
        v = MagicalBuilder.CreateSub(value_left, value_right, "subtmp");
    } 
    else if (*(node->op) == "*") {
        v = MagicalBuilder.CreateMul(value_left, value_right, "multmp");
    } 
    else if (*(node->op) == "/") {
        v = MagicalBuilder.CreateSDiv(value_left, value_right, "divtmp");
    } 
    else if (*(node->op) == "%") {
        v = MagicalBuilder.CreateSRem(value_left, value_right, "modtmp");
    } 
    else if (*(node->op) == "<") {
        v = MagicalBuilder.CreateICmpSLT(value_left, value_right, "ltcomparetmp");
    } 
    else if (*(node->op) == ">") {
        v = MagicalBuilder.CreateICmpSGT(value_left, value_right, "gtcomparetmp");
    } 
    else if (*(node->op) == "<=") {
        v = MagicalBuilder.CreateICmpSLE(value_left, value_right, "lecomparetmp");
    } 
    else if (*(node->op) == ">=") {
        v = MagicalBuilder.CreateICmpSGE(value_left, value_right, "gecomparetmp");
    } 
    else if (*(node->op) == "==") {
        v = MagicalBuilder.CreateICmpEQ(value_left, value_right, "equalcomparetmp");
    } 
    else if (*(node->op) == "!=") {
        v = MagicalBuilder.CreateICmpNE(value_left, value_right, "notequalcomparetmp");
    }
    else if (*(node->op) == "&&") {
        v = MagicalBuilder.CreateAnd(value_left, value_right, "andcomparetmp");
    } 
    else if (*(node->op) == "||") {
        v = MagicalBuilder.CreateOr(value_left, value_right, "orcomparetmp");
    }

    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: BinaryOpExpression" << endl << flush;
    }
    return v;
}

Value * CodeGenVisitor::visit(class UnaryOpExpression * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: UnaryOpExpression" << endl << flush;
		call_stack_size ++;
	}

    Value *v = node->expr->accept(this);
    if (node->expr->get_expr_type() == "MethodCall") {
        // Ensure the corresponding method returns something (int / bool)
        Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) node->expr)->method_name->variable_name));
        if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
            logger_class->add("Function return type should not be void", node->lineno);
        }
    }
    if (node->expr->get_expr_type() == "Location") {
        v = MagicalBuilder.CreateLoad(v);
    }

    if (*(node->op) == "-") {
    	if (debug == true) {
    		call_stack_size --;
    		cout << debug_info() << "Out codegen of: UnaryOpExpression" << endl << flush;
    	}
        return MagicalBuilder.CreateNeg(v, "negtmp");
    } 
    else if (*(node->op) == "!") {
    	if (debug == true) {
    		call_stack_size --;
    		cout << debug_info() << "Out codegen of: UnaryOpExpression" << endl << flush;
    	}
        return MagicalBuilder.CreateNot(v, "nottmp");
    }
}

Value * CodeGenVisitor::visit(class MethodCall * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: MethodCall" << endl << flush;
		call_stack_size ++;
	}

    Function *callee = LLVMmodule->getFunction(*(node->method_name->variable_name));
    if (callee == nullptr) {
    	logger_class->add("Unknown function name '" + *(node->method_name->variable_name) + "'", node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: MethodCall" << endl << flush;
	    }
    	return nullptr;
    }

    Type* retType = callee->getReturnType();

    vector<class Expr *> args_list = node->args->arg_list;
    if (callee->arg_size() != args_list.size()) {
    	ostringstream req; req << (int) callee->arg_size();
    	ostringstream giv; giv << (int) args_list.size();
    	logger_class->add("Method '" + *(node->method_name->variable_name) + "' requires " + req.str() + " parameters. Given " + giv.str(), node->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: MethodCall" << endl << flush;
	    }
    	return nullptr;
    }

    int index_rn = 0;
    vector<Value *> Args;
    for (auto &arg : args_list) {
        Value *argVal = arg->accept(this);

        int index_here = 0;
        auto arg_rn = callee->arg_begin();
        for (auto a = callee->arg_begin(); a != callee->arg_end(); a ++) {
            arg_rn = a;
            if (index_rn == index_here) break;
            index_here++;
        }
        
        int final_ans = argVal->getType()->getPrimitiveSizeInBits();
        if (final_ans == 0) {
            // Means is a variable / expression type
            final_ans = argVal->getType()->getContainedType(0)->getPrimitiveSizeInBits();
        }
        
        if (final_ans != arg_rn->getType()->getPrimitiveSizeInBits()) {
            logger_class->add("Method call doesn't match the function signature.", node->lineno);
            if (debug == true) {
                call_stack_size --;
                cout << debug_info() << "Out codegen of: MethodCall" << endl << flush;
            }
            return nullptr;
        }

        // Incrementing the index
        index_rn ++;
        
        if (arg->get_expr_type() == "MethodCall") {
            // Ensure the corresponding method returns something (int / bool)
            Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) arg)->method_name->variable_name));
            if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
                logger_class->add("Function return type should not be void", node->lineno);
            }
        }
        if (arg->get_expr_type() == "Location") {
            argVal = MagicalBuilder.CreateLoad(argVal);
        }
        if (argVal == nullptr) {
            logger_class->add("Method Argument passed is not valid.", node->lineno);
            if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: MethodCall" << endl << flush;
		    }
            return nullptr;
        }
        Args.push_back(argVal);
    }

    std::reverse(Args.begin(), Args.end());

    Value *v = MagicalBuilder.CreateCall(callee, Args);
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: MethodCall" << endl << flush;
    }
    return v;
}

Value * CodeGenVisitor::visit(class CalloutCall * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: CalloutCall" << endl << flush;
		call_stack_size ++;
	}

    vector<Type *> argTypes;
    vector<Value *> Args;
    
    for (auto &i : node->args->arg_list) {
        Value *tmp = i->accept(this);
        if (tmp == nullptr) {
            return nullptr;
        }
        Args.push_back(tmp);
        argTypes.push_back(tmp->getType());
    }
    
    ArrayRef<Type *> argsRef(argTypes);
    ArrayRef<Value *> funcargs(Args);
    FunctionType *FType = FunctionType::get(Type::getInt32Ty(Context), argsRef, false);
    Constant *func = LLVMmodule->getOrInsertFunction(*(node->function_name), FType);
    if (!func) {
    	logger_class->add("Callout: Error in inbuilt function call. Unknown Function name '" + (*(node->function_name)) + "'", node->lineno);
    	if (debug == true) {
			call_stack_size --;
			cout << debug_info() << "Out codegen of: CalloutCall" << endl << flush;
		}
        return nullptr;
    }

    Value *v = MagicalBuilder.CreateCall(func, funcargs);
    if (debug == true) {
		call_stack_size --;
		cout << debug_info() << "Out codegen of: CalloutCall" << endl << flush;
	}
    return v;
}

Value * CodeGenVisitor::visit(class CalloutArg * node) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: CalloutArg" << endl << flush;
		call_stack_size ++;
	}

    if (node->arg_string == nullptr && node->arg_expr == nullptr) {
        logger_class->add("Invalid Callout Argument", node->lineno);
        if (debug == true) {
			call_stack_size --;
			cout << debug_info() << "Out codegen of: CalloutArg" << endl << flush;
		}
        return nullptr;
    }

    if (node->arg_string != nullptr) {
    	if (debug == true) {
			call_stack_size --;
			cout << debug_info() << "Out codegen of: CalloutArg" << endl << flush;
		}
    	return MagicalBuilder.CreateGlobalStringPtr(*(node->arg_string));
    }

    Value *v = node->arg_expr->accept(this);
    if (node->arg_expr->get_expr_type() == "MethodCall") {
        // Ensure the corresponding method returns something (int / bool)
        Function * to_load_function = LLVMmodule->getFunction(*(((MethodCall *) node->arg_expr)->method_name->variable_name));
        if (to_load_function->getReturnType()->getPrimitiveSizeInBits() == 0) {
            logger_class->add("Function return type should not be void", node->lineno);
        }
    }
    if (node->arg_expr->get_expr_type() == "Location") {
        v = MagicalBuilder.CreateLoad(v);
    }
    if (debug == true) {
		call_stack_size --;
		cout << debug_info() << "Out codegen of: CalloutArg" << endl << flush;
	}
    return v;
}

Value * CodeGenVisitor::visit(class MethodArgInpList * node) {
    return nullptr;
}

Value * CodeGenVisitor::visit(class CalloutArgList * node) {
    return nullptr;
}

Value * CodeGenVisitor::visit(class TerminalVariable * node) {
    return nullptr;
}

Value * CodeGenVisitor::visit(class ArrayTerminalVariable * node) {
    return nullptr;
}

Value * CodeGenVisitor::visit(class FieldDeclList * node) {
    return nullptr;
}

Value * CodeGenVisitor::visit(class VariableList * node) {
    return nullptr;
}

Value * CodeGenVisitor::visit(class ParamList * node) {
    return nullptr;
}
#include <bits/stdc++.h>
#include "class_definition.h"

using namespace std;
using namespace llvm;

struct loop_struct {
    BasicBlock *afterBB, *checkBB;
    Value *condition;
    string loopVariable;
    PHINode *phiVariable;
};

static LLVMContext Context;
static Module *LLVMmodule = new Module("Noveen's compiler for decaf", Context);
static IRBuilder<> MagicalBuilder(Context);
static map<string, AllocaInst *> CurrentScopeVariables; // Manages the scope
static stack<loop_struct*> loops;
class LogErrorClass* logger_class;

int call_stack_size = 0;
bool debug = false;

string debug_info() {
	string ret = "";
	for (int i=0;i<call_stack_size;i++) ret += "    "; // 4 spaces
	for (int i=0;i<4*call_stack_size;i+=4) ret[i] = '|';
	return ret;
}

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

Value *Program::codegen(class LogErrorClass* logger_class_carried_on) {
	if (debug == true) {
		cout << debug_info() << "In codegen of: Program" << endl << flush;
		call_stack_size ++;
	}
	logger_class = logger_class_carried_on;

	// Just to pass to the function, no use
	map<string, AllocaInst *> _;
    
    Value *V = field_decl->codegen(true, _);
    if (V == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: Program" << endl << flush;
	    }
        return nullptr;
    }
    
    V = method_decl->codegen();
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
    	this->print_llvm_ir();
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

Value *MethodDeclList::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: MethodDeclList" << endl << flush;
		call_stack_size ++;
	}

    Value *V = ConstantInt::get(Context, APInt(32, 0));
    for (auto method : method_declerations_list) {
        V = method->codegen();
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

Function *MethodDecl::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: MethodDecl" << endl << flush;
		call_stack_size ++;
	}

    vector<string> param_var_names;
    vector<string> param_var_types;
    vector<Type *> arguments;
    Type *returnType;

    // Semantic
    // if (*(return_type) != "void" && code_block->has_return_expr() == false) {
    // 	logger_class->add("Return type of '" + *(method_name->variable_name) + "' is '" + *return_type + "' but no corresponding return statement found.", this->lineno);
    //     if (debug == true) {
	   //  	call_stack_size --;
	   //  	cout << debug_info() << "Out codegen of: MethodDecl" << endl << flush;
	   //  }
    //     return nullptr;
    // }

    for (auto param : param_list->parameters_list) {
        if (*(param.first) == "int") {
            arguments.push_back(Type::getInt32Ty(Context));
        } 
        else if (*(param.first) == "boolean") {
            arguments.push_back(Type::getInt1Ty(Context));
        } 
        else {
            logger_class->add("Allowed Function Arguments are only 'int' and 'boolean'\n'" + *(param.first) + "' is not allowed.", this->lineno);
            if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: MethodDecl" << endl << flush;
		    }
            return nullptr;
        }
        param_var_types.push_back(*(param.first));
        param_var_names.push_back(*(param.second->variable_name));
    }

    if (*(return_type) == "int") {
        returnType = Type::getInt32Ty(Context);
    } 
    else if (*(return_type) == "boolean") {
        returnType = Type::getInt1Ty(Context);
    } 
    else if (*(return_type) == "void") {
        returnType = Type::getVoidTy(Context);
    } 
    else {
    	logger_class->add("Function " + *(method_name->variable_name) + "'s return type: '" + *(return_type) + "' is not allowed.", this->lineno);
        if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: MethodDecl" << endl << flush;
	    }
        return nullptr;
    }

    FunctionType *FT = llvm::FunctionType::get(returnType, arguments, false);
    Function *F = llvm::Function::Create(FT, Function::ExternalLinkage, *(method_name->variable_name), LLVMmodule);

    int Idx = 0;
    for (Function::arg_iterator AI = F->arg_begin(); Idx != param_list->parameters_list.size(); ++AI, ++Idx) {
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

    Value *RetVal = code_block->codegen();

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
        return F;
    }

    F->eraseFromParent();
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: MethodDecl" << endl << flush;
    }
    return nullptr;
}

Value *Block::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: Block" << endl << flush;
		call_stack_size ++;
	}

    Value *V;
    map<string, AllocaInst *> Old_vals;
    
    V = decleration_list->codegen(false, Old_vals);
    if (V == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: Block" << endl << flush;
	    }
        return V;
    }
    
    V = statement_list->codegen();
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

Value *StatementList::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: StatementList" << endl << flush;
		call_stack_size ++;
	}

	Value *v = ConstantInt::get(Context, llvm::APInt(32, 1));
    for (auto statement : statement_list) {
        v = statement->codegen();
    }
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: StatementList" << endl << flush;
    }
	return v;
}

Value *AssignStmt::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: AssignStmt" << endl << flush;
		call_stack_size ++;
	}

    Value *cur = CurrentScopeVariables[*(left_part->var_name->variable_name)];
    if (cur == nullptr) {
        cur = LLVMmodule->getGlobalVariable(*(left_part->var_name->variable_name));
    }
    if (cur == nullptr) {
    	logger_class->add("Unknown Variable Name '" + *(left_part->var_name->variable_name) + "' while assigning.", this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: AssignStmt" << endl << flush;
	    }
    	return nullptr;
    }

    Value *val = right_part->codegen();
    if (right_part->get_expr_type() == "Location") {
    	val = MagicalBuilder.CreateLoad(val);
    }

    Value *lhs = left_part->codegen();
    cur = MagicalBuilder.CreateLoad(lhs);

    if (val == nullptr) {
    	logger_class->add("Error in RHS of assignment statement.", this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: AssignStmt" << endl << flush;
	    }
    	return nullptr;
    }

    if (*op == "+=") {
        val = MagicalBuilder.CreateAdd(cur, val, "addEqualToTmp");
    } 
    else if (*op == "-=") {
        val = MagicalBuilder.CreateSub(cur, val, "subEqualToTmp");
    }
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: AssignStmt" << endl << flush;
    }
    return MagicalBuilder.CreateStore(val, lhs);
}

Value *Literal::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: Literal" << endl << flush;
		call_stack_size ++;
	}

	Value *v;
    if (literal_type == "int") {
	    v = ConstantInt::get(Context, llvm::APInt(32, static_cast<uint64_t>(lit_int)));
	}
	else if (literal_type == "boolean") {
	    v = ConstantInt::get(Context, llvm::APInt(1, lit_bool));
	}
	else if (literal_type == "string") {
	    v = MagicalBuilder.CreateGlobalStringPtr(*lit_string);
	}
	
    if (debug == true) {
		call_stack_size --;
		cout << debug_info() << "Out codegen of: Literal" << endl << flush;
	}
    
    return v;
}

Value *Location::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: Location" << endl << flush;
		call_stack_size ++;
	}

    Value *V = CurrentScopeVariables[*(var_name->variable_name)];
    if (V == nullptr) {
        V = LLVMmodule->getNamedGlobal(*(var_name->variable_name));
    }
    if (V == nullptr) {
        logger_class->add("Unknown Variable Name '" + *(var_name->variable_name) + "' while assigning.", this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: Location" << endl << flush;
	    }
    	return nullptr;
    }
    if (location_type == "variable") {
    	if (debug == true) {
    		call_stack_size --;
    		cout << debug_info() << "Out codegen of: Location" << endl << flush;
    	}
        return V;
    }

    if (index == nullptr) {
    	logger_class->add("Invalid array index", this->lineno);
    }
    Value *index_val = index->codegen();
    
    if (index->get_expr_type() == "Location") {
    	index_val = MagicalBuilder.CreateLoad(index_val);
    }
    
    if (index_val == nullptr) {
    	logger_class->add("Invalid array index", this->lineno);
    }
    vector<Value *> array_index;
    array_index.push_back(MagicalBuilder.getInt32(0));
    array_index.push_back(index_val);
    V = MagicalBuilder.CreateGEP(V, array_index, (*(var_name->variable_name)) + "_Index");
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: Location" << endl << flush;
    }
    return V;
}

Value *IfElseStmt::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: IfElseStmt" << endl << flush;
		call_stack_size ++;
	}

    Value *val_cond = cond->codegen();
    if (val_cond == nullptr) {
    	logger_class->add("Invalid condition in the IF statement.", this->lineno);
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
    
    bool ret_if = if_block->has_return(), ret_else = false;
    
    if (else_block == nullptr) {
        otherBlock = nextBlock;
    }
    MagicalBuilder.CreateCondBr(val_cond, ifBlock, otherBlock);
    MagicalBuilder.SetInsertPoint(ifBlock);

    Value *if_val = if_block->codegen();
    if (if_val == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: IfElseStmt" << endl << flush;
	    }
        return nullptr;
    }

    if (!ret_if) {
        MagicalBuilder.CreateBr(nextBlock);
    }

    ifBlock = MagicalBuilder.GetInsertBlock();

    Value *else_val = nullptr;
    if (else_block != nullptr) {
        TheFunction->getBasicBlockList().push_back(elseBlock);
        MagicalBuilder.SetInsertPoint(elseBlock);
        else_val = else_block->codegen();
        if (else_val == nullptr) {
        	if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: IfElseStmt" << endl << flush;
		    }
            return nullptr;
        }

        ret_else = else_block->has_return();
        if (!ret_else) {
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

Value *IfStmt::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: IfStmt" << endl << flush;
		call_stack_size ++;
	}

	Value *val_cond = cond->codegen();
    if (val_cond == nullptr) {
    	logger_class->add("Invalid condition in the IF statement.", this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: IfStmt" << endl << flush;
	    }
    	return nullptr;
    }

    Function *TheFunction = MagicalBuilder.GetInsertBlock()->getParent();
    BasicBlock *ifBlock = BasicBlock::Create(Context, "if", TheFunction);
    BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont");
    
    bool ret_if = if_block->has_return();
    
    MagicalBuilder.CreateCondBr(val_cond, ifBlock, nextBlock);
    MagicalBuilder.SetInsertPoint(ifBlock);

    Value *if_val = if_block->codegen();
    if (if_val == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: IfStmt" << endl << flush;
	    }
        return nullptr;
    }

    if (!ret_if) {
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

Value *ForStmt::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: ForStmt" << endl << flush;
		call_stack_size ++;
	}
	
	// Checking if the loop var is redeclared
	if (CurrentScopeVariables.find(*(loop_var->variable_name)) != CurrentScopeVariables.end()) {
		if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
	    }
	    logger_class->add("Loop variable '" + (*(loop_var->variable_name)) + "' is redeclared.", this->lineno);
        return nullptr;
	}

    Function *TheFunction = MagicalBuilder.GetInsertBlock()->getParent();
    
    // Creating the loop variable
    llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, *(loop_var->variable_name), string("int"));
    llvm::AllocaInst *OldVal = CurrentScopeVariables[*(loop_var->variable_name)];
    CurrentScopeVariables[*(loop_var->variable_name)] = Alloca;

    Value *start = start_cond->codegen();
    if (start == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
	    }
	    logger_class->add("start error - i don't know.", this->lineno);
        return nullptr;
    }
    if (start_cond->get_expr_type() == "Location") {
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

    PHINode *Variable = MagicalBuilder.CreatePHI(Type::getInt32Ty(Context), 2, *(loop_var->variable_name));
    Variable->addIncoming(start, pre_header_basic_block);
    
    Value *cond = right_cond->codegen();
    if (cond == nullptr) {
    	logger_class->add("Invalid ending condition provided - for loop.", this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
	    }
    	return nullptr;
    }

    if (right_cond->get_expr_type() == "Location") {
        cond = MagicalBuilder.CreateLoad(cond);
    }
    
    // Pushing to the loop stack
    auto this_loop = new loop_struct();
    this_loop->afterBB = afterBB;
    this_loop->checkBB = loop_body;
    this_loop->condition = cond;
    this_loop->loopVariable = *(loop_var->variable_name);
    this_loop->phiVariable = Variable;
    loops.push(this_loop);

    MagicalBuilder.CreateCondBr(cond, loop_body, afterBB);
    MagicalBuilder.SetInsertPoint(loop_body);

    if (code_block->codegen() == nullptr) {
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
	    }
        return nullptr;
    }

    Value *cur = Variable;
    Value *next_val = MagicalBuilder.CreateAdd(cur, step_val, "NextVal");
    MagicalBuilder.CreateStore(next_val, Alloca);
    // cond = MagicalBuilder.CreateICmpSLT(next_val, cond, "loopcondition");
    BasicBlock *loopEndBlock = MagicalBuilder.GetInsertBlock();
    
    MagicalBuilder.CreateBr(beforeBB);
    Variable->addIncoming(next_val, loopEndBlock);

    MagicalBuilder.SetInsertPoint(afterBB);

    if (OldVal) {
        CurrentScopeVariables[*(loop_var->variable_name)] = OldVal;
    } else {
        CurrentScopeVariables.erase(*(loop_var->variable_name));
    }

    loops.pop();

    llvm::Value *V = ConstantInt::get(Context, APInt(32, 1));
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: ForStmt" << endl << flush;
    }
    return V;
}

Value *RetExpr::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: RetExpr" << endl << flush;
		call_stack_size ++;
	}

    Value *V = expr->codegen();
    if (expr->get_expr_type() == "Location") {
        V = MagicalBuilder.CreateLoad(V);
    }
    MagicalBuilder.CreateRet(V);
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: RetExpr" << endl << flush;
    }
    return V;
}

Value *StringRetBrkContStatement::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: StringRetBrkContStatement" << endl << flush;
		call_stack_size ++;
	}

	Value *V;
	if (*type == "return") {
		MagicalBuilder.CreateRetVoid();
	}
	else if (*type == "break") {
		V = ConstantInt::get(Context, llvm::APInt(32, 1));
		if (loops.size() == 0) {
			logger_class->add("Invalid 'break' statement - not inside a loop.", this->lineno);
			if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: StringRetBrkContStatement" << endl << flush;
		    }
	    	return nullptr;
		}
	    loop_struct *currentLoop = loops.top();
	    MagicalBuilder.CreateBr(currentLoop->afterBB);
	}
	else if (*type == "continue") {
		V = ConstantInt::get(Context, llvm::APInt(32, 1));
		if (loops.size() == 0) {
			logger_class->add("Invalid 'continue' statement - not inside a loop.", this->lineno);
			if (debug == true) {
		    	call_stack_size --;
		    	cout << debug_info() << "Out codegen of: StringRetBrkContStatement" << endl << flush;
		    }
	    	return nullptr;
		}
	    loop_struct *currentLoop = loops.top();
	    
        // Check
        MagicalBuilder.CreateBr(currentLoop->checkBB);
	    
	    // Expr *condition = nullptr;
	    // string var = currentLoop->loopVariable;
	    // AllocaInst *Alloca = CurrentScopeVariables[var];
	    // Value *step_val = ConstantInt::get(Context, APInt(32, 1));
	    // Value *cur = MagicalBuilder.CreateLoad(Alloca, var);
	    // Value *next_val = MagicalBuilder.CreateAdd(cur, step_val, "NextVal");
	    // MagicalBuilder.CreateStore(next_val, Alloca);
	    // Value *cond = currentLoop->condition;
	    // // Value *cond = MagicalBuilder.CreateICmpULE(next_val, currentLoop->condition, "loopcondition");
	    // BasicBlock *loopEndBlock = MagicalBuilder.GetInsertBlock();
	    // MagicalBuilder.CreateCondBr(cond, currentLoop->checkBB, currentLoop->afterBB);
	}
    
    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: StringRetBrkContStatement" << endl << flush;
    }
    return V;
}

Value *BinaryOpExpression::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: BinaryOpExpression" << endl << flush;
		call_stack_size ++;
	}

    Value *value_left = left->codegen();
    Value *value_right = right->codegen();

    if (left->get_expr_type() == "Location") {
        value_left = MagicalBuilder.CreateLoad(value_left);
    }
    if (right->get_expr_type() == "Location") {
        value_right = MagicalBuilder.CreateLoad(value_right);
    }

    if (value_left == 0) {
    	logger_class->add("Error in LHS of binary op expression.", this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: BinaryOpExpression" << endl << flush;
	    }
    	return nullptr;
    } 
    else if (value_right == 0) {
    	logger_class->add("Error in RHS of binary op expression.", this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: BinaryOpExpression" << endl << flush;
	    }
    	return nullptr;
    }
    
    Value *v = nullptr;
    if (*op == "+") {
        v = MagicalBuilder.CreateAdd(value_left, value_right, "addtmp");
    } 
    else if (*op == "-") {
        v = MagicalBuilder.CreateSub(value_left, value_right, "subtmp");
    } 
    else if (*op == "*") {
        v = MagicalBuilder.CreateMul(value_left, value_right, "multmp");
    } 
    else if (*op == "/") {
        v = MagicalBuilder.CreateSDiv(value_left, value_right, "divtmp");
    } 
    else if (*op == "%") {
        v = MagicalBuilder.CreateSRem(value_left, value_right, "modtmp");
    } 
    else if (*op == "<") {
        v = MagicalBuilder.CreateICmpSLT(value_left, value_right, "ltcomparetmp");
    } 
    else if (*op == ">") {
        v = MagicalBuilder.CreateICmpSGT(value_left, value_right, "gtcomparetmp");
    } 
    else if (*op == "<=") {
        v = MagicalBuilder.CreateICmpSLE(value_left, value_right, "lecomparetmp");
    } 
    else if (*op == ">=") {
        v = MagicalBuilder.CreateICmpSGE(value_left, value_right, "gecomparetmp");
    } 
    else if (*op == "==") {
        v = MagicalBuilder.CreateICmpEQ(value_left, value_right, "equalcomparetmp");
    } 
    else if (*op == "!=") {
        v = MagicalBuilder.CreateICmpNE(value_left, value_right, "notequalcomparetmp");
    }
    else if (*op == "&&") {
        v = MagicalBuilder.CreateAnd(value_left, value_right, "andcomparetmp");
    } 
    else if (*op == "||") {
        v = MagicalBuilder.CreateOr(value_left, value_right, "orcomparetmp");
    }

    if (debug == true) {
    	call_stack_size --;
    	cout << debug_info() << "Out codegen of: BinaryOpExpression" << endl << flush;
    }
    return v;
}

Value *UnaryOpExpression::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: UnaryOpExpression" << endl << flush;
		call_stack_size ++;
	}

    Value *v = expr->codegen();
    if (expr->get_expr_type() == "Location") {
        v = MagicalBuilder.CreateLoad(v);
    }

    if (*op == "-") {
    	if (debug == true) {
    		call_stack_size --;
    		cout << debug_info() << "Out codegen of: UnaryOpExpression" << endl << flush;
    	}
        return MagicalBuilder.CreateNeg(v, "negtmp");
    } 
    else if (*op == "!") {
    	if (debug == true) {
    		call_stack_size --;
    		cout << debug_info() << "Out codegen of: UnaryOpExpression" << endl << flush;
    	}
        return MagicalBuilder.CreateNot(v, "nottmp");
    }
}

Value *MethodCall::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: MethodCall" << endl << flush;
		call_stack_size ++;
	}

    Function *callee = LLVMmodule->getFunction(*(method_name->variable_name));
    if (callee == nullptr) {
    	logger_class->add("Unknown function name '" + *(method_name->variable_name) + "'", this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: MethodCall" << endl << flush;
	    }
    	return nullptr;
    }

    Type* retType = callee->getReturnType();

    vector<class Expr *> args_list = args->arg_list;
    if (callee->arg_size() != args_list.size()) {
    	ostringstream req; req << (int) callee->arg_size();
    	ostringstream giv; giv << (int) args_list.size();
    	logger_class->add("Method '" + *(method_name->variable_name) + "' requires " + req.str() + " parameters. Given " + giv.str(), this->lineno);
    	if (debug == true) {
	    	call_stack_size --;
	    	cout << debug_info() << "Out codegen of: MethodCall" << endl << flush;
	    }
    	return nullptr;
    }

    vector<Value *> Args;
    for (auto &arg : args_list) {
        Value *argVal = arg->codegen();
        if (arg->get_expr_type() == "Location") {
            argVal = MagicalBuilder.CreateLoad(argVal);
        }
        if (argVal == nullptr) {
            logger_class->add("Method Argument passed is not valid.", this->lineno);
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

Value *CalloutCall::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: CalloutCall" << endl << flush;
		call_stack_size ++;
	}

    vector<Type *> argTypes;
    vector<Value *> Args;
    
    for (auto &i : args->arg_list) {
        Value *tmp = i->codegen();
        if (tmp == nullptr) {
            return nullptr;
        }
        Args.push_back(tmp);
        argTypes.push_back(tmp->getType());
    }
    
    ArrayRef<Type *> argsRef(argTypes);
    ArrayRef<Value *> funcargs(Args);
    FunctionType *FType = FunctionType::get(Type::getInt32Ty(Context), argsRef, false);
    Constant *func = LLVMmodule->getOrInsertFunction(*function_name, FType);
    if (!func) {
    	logger_class->add("Callout: Error in inbuilt function call. Unknown Function name '" + (*function_name) + "'", this->lineno);
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

Value *CalloutArg::codegen() {
	if (debug == true) {
		cout << debug_info() << "In codegen of: CalloutArg" << endl << flush;
		call_stack_size ++;
	}

    if (arg_string == nullptr && arg_expr == nullptr) {
        logger_class->add("Invalid Callout Argument", this->lineno);
        if (debug == true) {
			call_stack_size --;
			cout << debug_info() << "Out codegen of: CalloutArg" << endl << flush;
		}
        return nullptr;
    }

    if (arg_string != nullptr) {
    	if (debug == true) {
			call_stack_size --;
			cout << debug_info() << "Out codegen of: CalloutArg" << endl << flush;
		}
    	return MagicalBuilder.CreateGlobalStringPtr(*arg_string);
    }

    Value *v = arg_expr->codegen();
    if (arg_expr->get_expr_type() == "Location") {
        v = MagicalBuilder.CreateLoad(v);
    }
    if (debug == true) {
		call_stack_size --;
		cout << debug_info() << "Out codegen of: CalloutArg" << endl << flush;
	}
    return v;
}

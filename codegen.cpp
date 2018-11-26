#include <bits/stdc++.h>
#include "class_definition.h"
// #include "flag_parsed_correct.h"

using namespace std;
using namespace llvm;

bool debug = false;

static LLVMContext Context;
static Module *TheModule = new Module("Compiler for decaf", Context);
static IRBuilder<> Builder(Context);
static map<string, AllocaInst *> NamedValues;
struct loopInfo {
	BasicBlock *afterBB, *checkBB;
    Value *condition;
    string loopVariable;
	PHINode *phiVariable;
};
static stack<loopInfo*> loops;

class LogErrorClass* logger_class;

void Program::print_llvm_ir() {
	TheModule->print(llvm::errs(), nullptr);
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
	if (debug == true) cout << "In codegen of: Program" << endl << flush;
	logger_class = logger_class_carried_on;

	// Just to pass to the function, no use
	map<string, AllocaInst *> _;
    Value *V = field_decl->codegen(true, _);
    if (V == nullptr) {
        return nullptr;
    }
    
    V = method_decl->codegen();
    if (V == nullptr) {
        return nullptr;
    }
    
    if (debug == true) cout << "Out codegen of: Program" << endl << flush;
    
    if (logger_class->all_errors.size() == 0) {
    	this->print_llvm_ir();
    }
    
    return V;
}

Value *FieldDeclList::codegen(bool is_global_scope, map<string, AllocaInst *> &Old_vals) {
	if (debug == true) cout << "In codegen of: FieldDeclList" << endl << flush;

	Value *v = ConstantInt::get(Context, APInt(32, 1));
    for (auto decleration : all_declerations) {
        v = decleration->codegen(is_global_scope, Old_vals);
        if (v == nullptr) {
        	return v;
        }
    }
    if (debug == true) cout << "Out codegen of: FieldDeclList" << endl << flush;
    return v;
}

Value *VariableList::codegen(bool is_global_scope, map<string, AllocaInst *> &Old_vals) {
	if (debug == true) cout << "In codegen of: VariableList" << endl << flush;

    llvm::Type *ty = nullptr;
    if (*(decleration_type) == "int") {
		ty = Type::getInt32Ty(Context);
	}
	else if (*(decleration_type) == "boolean") {
    	ty = Type::getInt1Ty(Context);
    }
    else {
    	// Mine
    	logger_class->add("Allowed declerations are only 'int' and 'boolean'\n'" + *(decleration_type) + "' is not allowed.");
    	return (Value *) nullptr;
    }

    for (auto var : declarations) {

    	if (is_global_scope == true) {
			GlobalVariable *gv = TheModule->getNamedGlobal(*(var->variable_name));
			if (gv != nullptr) {
				logger_class->add("Variable '" + *(var->variable_name) + "' redefined.");
				continue;
			}
    		
    		gv = new GlobalVariable(
    			*(TheModule), ty, false,
                GlobalValue::ExternalLinkage, nullptr,
                *(var->variable_name)
            );
            gv->setInitializer(Constant::getNullValue(ty));
    	}
    	else {
    		// Local Variable
    		// TODO: Need to make a vector of scopes
    		// if (NamedValues.find(*(var->variable_name)) != NamedValues.end()) {
    			// logger_class->add("Variable '" + *(var->variable_name) + "' redefined.");
				// continue;
    		// }
    		Function *TheFunction = Builder.GetInsertBlock()->getParent();
    		Value *initval;
    		if (*(decleration_type) == "int") {
	    		initval = ConstantInt::get(Context, APInt(32, 0));
    		}
    		else if (*(decleration_type) == "boolean") {
    			initval = ConstantInt::get(Context, APInt(1, 0));
    		}
            AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, *(var->variable_name), *(decleration_type));

            Builder.CreateStore(initval, Alloca);
	        Old_vals[*(var->variable_name)] = NamedValues[*(var->variable_name)];
	        NamedValues[*(var->variable_name)] = Alloca;
    	}
    }

    for (auto arr: declarations_array) {

        if (is_global_scope) {
        	GlobalVariable *gv = TheModule->getNamedGlobal(*(arr->arr_name->variable_name));
			if (gv != nullptr) {
				logger_class->add("Array '" + *(arr->arr_name->variable_name) + "' redefined.");
				continue;
			}
            
            ArrayType *arrType = ArrayType::get(ty, arr->get_length());
            gv = new GlobalVariable(
            	*(TheModule), arrType, false,
                GlobalValue::ExternalLinkage, nullptr,
                *(arr->arr_name->variable_name)
            );
            gv->setInitializer(ConstantAggregateZero::get(arrType));
        } 
        else {
        	// Local Array (Not Allowed)
        	logger_class->add("Array declerations are only allowed in the global scope.");
	    	return nullptr;
        }
    }
    Value *v = ConstantInt::get(Context, APInt(32, 1));
    if (debug == true) cout << "Out codegen of: VariableList" << endl << flush;
    return v;
}

Value *MethodDeclList::codegen() {
	if (debug == true) cout << "In codegen of: MethodDeclList" << endl << flush;

    Value *V;// = ConstantInt::get(Context, APInt(32, 0));
    for (auto method : method_declerations_list) {
        V = method->codegen();
        if (V == nullptr) return V;
    }
    if (debug == true) cout << "Out codegen of: MethodDeclList" << endl << flush;
    return V;
}

Function *MethodDecl::codegen() {
	if (debug == true) cout << "In codegen of: MethodDecl" << endl << flush;

    vector<string> param_var_names;
    vector<string> param_var_types;
    vector<Type *> arguments;
    Type *returnType;

    if (*(return_type) != "void" && code_block->has_return_expr() == false) {
    	logger_class->add("Return type of '" + *(method_name->variable_name) + "' is '" + *return_type + "' but no corresponding return statement found.");
        return nullptr;
    }

    for (auto param : param_list->parameters_list) {
        if (*(param.first) == "int") {
            arguments.push_back(Type::getInt32Ty(Context));
        } 
        else if (*(param.first) == "boolean") {
            arguments.push_back(Type::getInt1Ty(Context));
        } 
        else {
            logger_class->add("Allowed Function Arguments are only 'int' and 'boolean'\n'" + *(param.first) + "' is not allowed.");
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
    	logger_class->add("Function " + *(method_name->variable_name) + "'s return type: '" + *(return_type) + "' is not allowed.");
        return nullptr;
    }

    FunctionType *FT = llvm::FunctionType::get(returnType, arguments, false);
    Function *F = llvm::Function::Create(FT, Function::ExternalLinkage, *(method_name->variable_name), TheModule);

    int Idx = 0;
    for (Function::arg_iterator AI = F->arg_begin(); Idx != param_list->parameters_list.size(); ++AI, ++Idx) {
        AI->setName(param_var_names[Idx]);
    }

    BasicBlock *BB = BasicBlock::Create(Context, "entry", F);
    Builder.SetInsertPoint(BB);
    Idx = 0;

    for (auto &Arg : F->args()) {
        AllocaInst *Alloca = CreateEntryBlockAlloca(F, param_var_names[Idx], param_var_types[Idx]);
        Builder.CreateStore(&Arg, Alloca);
        NamedValues[param_var_names[Idx]] = Alloca;
        Idx++;
    }

    Value *RetVal = code_block->codegen();
    if (RetVal) {
        if (*(return_type) != "void")
            Builder.CreateRet(RetVal);
        else
            Builder.CreateRetVoid();
        
        verifyFunction(*F);
        return F;
    }

    F->eraseFromParent();
    if (debug == true) cout << "Out codegen of: MethodDecl" << endl << flush;
    return nullptr;
}

Value *Block::codegen() {
	if (debug == true) cout << "In codegen of: Block" << endl << flush;

    Value *V;
    map<string, AllocaInst *> Old_vals;
    
    V = decleration_list->codegen(false, Old_vals);
    if (V == nullptr) {
        return V;
    }
    
    V = statement_list->codegen();
    if (V == nullptr) {
        return V;
    }

    for (auto val: Old_vals) {
    	NamedValues[val.first] = Old_vals[val.first];
    }
    if (debug == true) cout << "Out codegen of: Block" << endl << flush;
    return V;
}

Value *StatementList::codegen() {
	if (debug == true) cout << "In codegen of: StatementList" << endl << flush;

	Value *v = ConstantInt::get(Context, llvm::APInt(32, 1));
    for (auto statement : statement_list) {
        v = statement->codegen();
    }
    if (debug == true) cout << "Out codegen of: StatementList" << endl << flush;
	return v;
}

Value *AssignStmt::codegen() {
	if (debug == true) cout << "In codegen of: AssignStmt" << endl << flush;

    Value *cur = NamedValues[*(left_part->var_name->variable_name)];
    if (cur == nullptr) {
        cur = TheModule->getGlobalVariable(*(left_part->var_name->variable_name));
    }
    if (cur == nullptr) {
    	logger_class->add("Unknown Variable Name '" + *(left_part->var_name->variable_name) + "' while assigning.");
    	return nullptr;
    }
    Value *val = right_part->codegen();
    // Mine
    if (right_part->get_expr_type() == "Location") {
    	val = Builder.CreateLoad(val);
    }

    Value *lhs = left_part->codegen();
    cur = Builder.CreateLoad(lhs);

    if (val == nullptr) {
    	logger_class->add("Error in RHS of assignment statement.");
    	return nullptr;
    }

    if (*op == "+=") {
        val = Builder.CreateAdd(cur, val, "addEqualToTmp");
    } 
    else if (*op == "-=") {
        val = Builder.CreateSub(cur, val, "subEqualToTmp");
    }
    if (debug == true) cout << "Out codegen of: AssignStmt" << endl << flush;
    return Builder.CreateStore(val, lhs);
}

Value *Literal::codegen() {
	if (debug == true) cout << "In codegen of: Literal" << endl << flush;
	Value *v;
	if (literal_type == "int") {
	    v = ConstantInt::get(Context, llvm::APInt(32, static_cast<uint64_t>(lit_int)));
	    // cout << "Int ban gaya! val = " << lit_int << endl << flush;
	}
	if (literal_type == "boolean") {
	    v = ConstantInt::get(Context, llvm::APInt(1, lit_bool));
	    // cout << "boolean ban gaya! val = " << lit_bool << endl << flush;
	}
	if (literal_type == "string") {
	    v = Builder.CreateGlobalStringPtr(*lit_string);
	    // cout << "string ban gaya! val = " << lit_string << endl << flush;
	}
	if (debug == true) cout << "Out codegen of: Literal" << endl << flush;
    return v;
}

Value *Location::codegen() {
	if (debug == true) cout << "In codegen of: Location" << endl << flush;

    Value *V = NamedValues[*(var_name->variable_name)];
    if (V == nullptr) {
        V = TheModule->getNamedGlobal(*(var_name->variable_name));
    }
    if (V == nullptr) {
        logger_class->add("Unknown Variable Name '" + *(var_name->variable_name) + "' while assigning.");
    	return nullptr;
    }
    if (location_type == "variable") {
    	if (debug == true) cout << "Out codegen of: Location" << endl << flush;
        return V;
    }

    //////////////////////////////////// NEED TO CHECK, NOT TESTED

    if (index == nullptr) {
    	logger_class->add("Invalid array index");
    }
    Value *index_val = index->codegen();
    
    if (index->get_expr_type() == "Location") {
    	index_val = Builder.CreateLoad(index_val);
    }
    
    if (index_val == nullptr) {
    	logger_class->add("Invalid array index");
    }
    vector<Value *> array_index;
    array_index.push_back(Builder.getInt32(0));
    array_index.push_back(index_val);
    V = Builder.CreateGEP(V, array_index, (*(var_name->variable_name)) + "_Index");
    if (debug == true) cout << "Out codegen of: Location" << endl << flush;
    return V;

    ///////////////////////////////////// UPTIL HERE
}

Value *IfElseStmt::codegen() {
	if (debug == true) cout << "In codegen of: IfElseStmt" << endl << flush;

    Value *val_cond = cond->codegen();
    if (val_cond == nullptr) {
    	logger_class->add("Invalid condition in the IF statement.");
    	return nullptr;
    }

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *ifBlock = BasicBlock::Create(Context, "if", TheFunction);
    BasicBlock *elseBlock = BasicBlock::Create(Context, "else");
    BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont");
    BasicBlock *otherBlock = elseBlock;
    
    bool ret_if = if_block->has_return(), ret_else = false;
    
    if (else_block == nullptr) {
        otherBlock = nextBlock;
    }
    Builder.CreateCondBr(val_cond, ifBlock, otherBlock);
    Builder.SetInsertPoint(ifBlock);

    Value *if_val = if_block->codegen();
    if (if_val == nullptr) {
        return nullptr;
    }

    if (!ret_if) {
        Builder.CreateBr(nextBlock);
    }

    ifBlock = Builder.GetInsertBlock();

    Value *else_val = nullptr;
    if (else_block != nullptr) {
        TheFunction->getBasicBlockList().push_back(elseBlock);
        Builder.SetInsertPoint(elseBlock);
        else_val = else_block->codegen();
        if (else_val == nullptr) {
            return nullptr;
        }

        ret_else = else_block->has_return();
        if (!ret_else) {
            Builder.CreateBr(nextBlock);
        }
    }

    TheFunction->getBasicBlockList().push_back(nextBlock);
    Builder.SetInsertPoint(nextBlock);
    if (ret_else && ret_if) {
        Type *retType = Builder.GetInsertBlock()->getParent()->getReturnType();
        if (retType == Type::getVoidTy(Context))
            Builder.CreateRetVoid();
        else {
            Builder.CreateRet(ConstantInt::get(Context, APInt(32, 0)));
        }
    }

    Value *V = ConstantInt::get(Context, APInt(32, 0));
    if (debug == true) cout << "Out codegen of: IfElseStmt" << endl << flush;
    return V;
}

Value *IfStmt::codegen() {
	if (debug == true) cout << "In codegen of: IfStmt" << endl << flush;

	Value *val_cond = cond->codegen();
    if (val_cond == nullptr) {
    	logger_class->add("Invalid condition in the IF statement.");
    	return nullptr;
    }

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    BasicBlock *ifBlock = BasicBlock::Create(Context, "if", TheFunction);
    BasicBlock *nextBlock = BasicBlock::Create(Context, "ifcont");
    
    bool ret_if = if_block->has_return();
    
    // Builder.CreateCondBr(val_cond, ifBlock, otherBlock);
    Builder.SetInsertPoint(ifBlock);

    Value *if_val = if_block->codegen();
    if (if_val == nullptr) {
        return nullptr;
    }

    if (!ret_if) {
        Builder.CreateBr(nextBlock);
    }

    ifBlock = Builder.GetInsertBlock();

    // Value *else_val = nullptr;
    // if (else_block != nullptr) {
    //     TheFunction->getBasicBlockList().push_back(elseBlock);
    //     Builder.SetInsertPoint(elseBlock);
    //     else_val = else_block->codegen();
    //     if (else_val == nullptr) {
    //         return nullptr;
    //     }

    //     ret_else = else_block->has_return();
    //     if (!ret_else) {
    //         Builder.CreateBr(nextBlock);
    //     }
    // }

    TheFunction->getBasicBlockList().push_back(nextBlock);
    Builder.SetInsertPoint(nextBlock);
    // if (ret_else && ret_if) {
        // Type *retType = Builder.GetInsertBlock()->getParent()->getReturnType();
        // if (retType == Type::getVoidTy(Context))
            // Builder.CreateRetVoid();
        // else {
            // Builder.CreateRet(ConstantInt::get(Context, APInt(32, 0)));
        // }
    // }

    Value *V = ConstantInt::get(Context, APInt(32, 0));
    if (debug == true) cout << "Out codegen of: IfStmt" << endl << flush;
    return V;
}

Value *ForStmt::codegen() {
	if (debug == true) cout << "In codegen of: ForStmt" << endl << flush;

    Value *start = start_cond->codegen();
    if (start == nullptr) {
        return nullptr;
    }
    if (start_cond->get_expr_type() == "Location") {
        start = Builder.CreateLoad(start);
    }

    Function *TheFunction = Builder.GetInsertBlock()->getParent();

    // Loading the loop variable
    AllocaInst *Alloca = NamedValues[*(loop_var->variable_name)];
    if (Alloca == nullptr) {
        Alloca = (AllocaInst *) TheModule->getGlobalVariable(*(loop_var->variable_name));
    }
    if (Alloca == nullptr) {
    	logger_class->add("Please declare the looping variable '" + *(loop_var->variable_name) + "' - for loop.");
    	return nullptr;
    }

    // Creating the loop variable
    // llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, *(loop_var->variable_name), string("int"));
    // Builder.CreateStore(start, Alloca);

    Value *step_val = ConstantInt::get(Context, APInt(32, 1));
    BasicBlock *pre_header_basic_block = Builder.GetInsertBlock();
    BasicBlock *loop_body = BasicBlock::Create(Context, "loop", TheFunction);
    BasicBlock *afterBB = BasicBlock::Create(Context, "afterloop", TheFunction);
    Builder.CreateBr(loop_body);
    Builder.SetInsertPoint(loop_body);

    PHINode *Variable = Builder.CreatePHI(Type::getInt32Ty(Context), 2, *(loop_var->variable_name));
    Variable->addIncoming(start, pre_header_basic_block);
    
    Value *cond = right_cond->codegen();
    if (cond == nullptr) {
    	logger_class->add("Invalid ending condition provided - for loop.");
    	return nullptr;
    }

    if (right_cond->get_expr_type() == "Location") {
        cond = Builder.CreateLoad(cond);
    }
    
    auto loop_struct = new loopInfo();
    loop_struct->afterBB = afterBB;
    loop_struct->checkBB = loop_body;
    loop_struct->condition = cond;
    loop_struct->loopVariable = *(loop_var->variable_name);
    loop_struct->phiVariable = Variable;
    loops.push(loop_struct);
    
    llvm::AllocaInst *OldVal = NamedValues[*(loop_var->variable_name)];
    NamedValues[*(loop_var->variable_name)] = Alloca;

    if (code_block->codegen() == nullptr) {
        return nullptr;
    }

    Value *cur = Builder.CreateLoad(Alloca, *(loop_var->variable_name));
    Value *next_val = Builder.CreateAdd(cur, step_val, "NextVal");
    Builder.CreateStore(next_val, Alloca);
    cond = Builder.CreateICmpSLT(next_val, cond, "loopcondition");
    BasicBlock *loopEndBlock = Builder.GetInsertBlock();
    Builder.CreateCondBr(cond, loop_body, afterBB);
    Builder.SetInsertPoint(afterBB);
    Variable->addIncoming(next_val, loopEndBlock);

    if (OldVal) {
        NamedValues[*(loop_var->variable_name)] = OldVal;
    } else {
        NamedValues.erase(*(loop_var->variable_name));
    }

    loops.pop();

    llvm::Value *V = ConstantInt::get(Context, APInt(32, 1));
    if (debug == true) cout << "Out codegen of: ForStmt" << endl << flush;
    return V;
}

Value *RetExpr::codegen() {
	if (debug == true) cout << "In codegen of: RetExpr" << endl << flush;

    Value *V = expr->codegen();
    if (expr->get_expr_type() == "Location") {
        V = Builder.CreateLoad(V);
    }
    Builder.CreateRet(V);
    if (debug == true) cout << "Out codegen of: RetExpr" << endl << flush;
    return V;
}

Value *StringRetBrkContStatement::codegen() {
	if (debug == true) cout << "In codegen of: StringRetBrkContStatement" << endl << flush;

	Value *V;
	if (*type == "return") {
		Builder.CreateRetVoid();
	}
	else if (*type == "break") {
		V = ConstantInt::get(Context, llvm::APInt(32, 1));
		if (loops.size() == 0) {
			logger_class->add("Invalid 'break' statement - not inside a loop.");
	    	return nullptr;
		}
	    loopInfo *currentLoop = loops.top();
	    Builder.CreateBr(currentLoop->afterBB);
	}
	else if (*type == "continue") {
		V = ConstantInt::get(Context, llvm::APInt(32, 1));
		if (loops.size() == 0) {
			logger_class->add("Invalid 'continue' statement - not inside a loop.");
	    	return nullptr;
		}
	    loopInfo *currentLoop = loops.top();
	    Expr *condition = nullptr;
	    string var = currentLoop->loopVariable;
	    AllocaInst *Alloca = NamedValues[var];
	    Value *step_val = ConstantInt::get(Context, APInt(32, 1));
	    Value *cur = Builder.CreateLoad(Alloca, var);
	    Value *next_val = Builder.CreateAdd(cur, step_val, "NextVal");
	    Builder.CreateStore(next_val, Alloca);
	    Value *cond = Builder.CreateICmpULE(next_val, currentLoop->condition, "loopcondition");
	    BasicBlock *loopEndBlock = Builder.GetInsertBlock();
	    Builder.CreateCondBr(cond, currentLoop->checkBB, currentLoop->afterBB);
	}
    
    if (debug == true) cout << "Out codegen of: StringRetBrkContStatement" << endl << flush;
    return V;
}

Value *BinaryOpExpression::codegen() {
	if (debug == true) cout << "In codegen of: BinaryOpExpression" << endl << flush;

    Value *value_left = left->codegen();
    Value *value_right = right->codegen();

    if (left->get_expr_type() == "Location") {
        value_left = Builder.CreateLoad(value_left);
    }
    if (right->get_expr_type() == "Location") {
        value_right = Builder.CreateLoad(value_right);
    }

    if (value_left == 0) {
    	logger_class->add("Error in LHS of binary op expression.");
    	return nullptr;
    } 
    else if (value_right == 0) {
    	logger_class->add("Error in RHS of binary op expression.");
    	return nullptr;
    }
    
    Value *v = nullptr;
    if (*op == "+") {
        v = Builder.CreateAdd(value_left, value_right, "addtmp");
    } 
    else if (*op == "-") {
        v = Builder.CreateSub(value_left, value_right, "subtmp");
    } 
    else if (*op == "*") {
        v = Builder.CreateMul(value_left, value_right, "multmp");
    } 
    else if (*op == "/") {
        v = Builder.CreateSDiv(value_left, value_right, "divtmp");
    } 
    else if (*op == "%") {
        v = Builder.CreateSRem(value_left, value_right, "modtmp");
    } 
    else if (*op == "<") {
        v = Builder.CreateICmpSLT(value_left, value_right, "ltcomparetmp");
    } 
    else if (*op == ">") {
        v = Builder.CreateICmpSGT(value_left, value_right, "gtcomparetmp");
    } 
    else if (*op == "<=") {
        v = Builder.CreateICmpSLE(value_left, value_right, "lecomparetmp");
    } 
    else if (*op == ">=") {
        v = Builder.CreateICmpSGE(value_left, value_right, "gecomparetmp");
    } 
    else if (*op == "==") {
        v = Builder.CreateICmpEQ(value_left, value_right, "equalcomparetmp");
    } 
    else if (*op == "!=") {
        v = Builder.CreateICmpNE(value_left, value_right, "notequalcomparetmp");
    }
    else if (*op == "&&") {
        v = Builder.CreateAnd(value_left, value_right, "andcomparetmp");
    } 
    else if (*op == "||") {
        v = Builder.CreateOr(value_left, value_right, "orcomparetmp");
    }

    if (debug == true) cout << "Out codegen of: BinaryOpExpression" << endl << flush;
    return v;
}

Value *UnaryOpExpression::codegen() {
	if (debug == true) cout << "In codegen of: UnaryOpExpression" << endl << flush;

    Value *v = expr->codegen();
    if (expr->get_expr_type() == "Location") {
        v = Builder.CreateLoad(v);
    }

    if (*op == "-") {
    	if (debug == true) cout << "Out codegen of: UnaryOpExpression" << endl << flush;
        return Builder.CreateNeg(v, "negtmp");
    } 
    else if (*op == "!") {
    	if (debug == true) cout << "Out codegen of: UnaryOpExpression" << endl << flush;
        return Builder.CreateNot(v, "nottmp");
    }
}

Value *MethodCall::codegen() {
	if (debug == true) cout << "In codegen of: MethodCall" << endl << flush;

    Function *callee = TheModule->getFunction(*(method_name->variable_name));
    if (callee == nullptr) {
    	logger_class->add("Unknown function name '" + *(method_name->variable_name) + "'");
    	return nullptr;
    }

    vector<class Expr *> args_list = args->arg_list;
    if (callee->arg_size() != args_list.size()) {
    	ostringstream req; req << (int) callee->arg_size();
    	ostringstream giv; giv << (int) args_list.size();
    	logger_class->add("Method '" + *(method_name->variable_name) + "' requires " + req.str() + " parameters. Given " + giv.str());
    	return nullptr;
    }

    vector<Value *> Args;
    for (auto &arg : args_list) {
        Value *argVal = arg->codegen();
        if (arg->get_expr_type() == "Location") {
            argVal = Builder.CreateLoad(argVal);
        }
        if (argVal == nullptr) {
            logger_class->add("Method Argument passed is not valid.");
            return nullptr;
        }
        Args.push_back(argVal);
    }

    ////////////////// NOTE: Confirm
    std::reverse(Args.begin(), Args.end());

    Value *v = Builder.CreateCall(callee, Args);
    if (debug == true) cout << "Out codegen of: MethodCall" << endl << flush;
    return v;
}

Value *CalloutCall::codegen() {
	if (debug == true) cout << "In codegen of: CalloutCall" << endl << flush;

	Value *v = ConstantInt::get(Context, APInt(32, 1));
	if (debug == true) cout << "Out codegen of: CalloutCall" << endl << flush;
	return v;
}

Value *CalloutArgList::codegen() {
	if (debug == true) cout << "In codegen of: CalloutArgList" << endl << flush;

	Value *v = ConstantInt::get(Context, APInt(32, 1));
	return v;
}

Value *CalloutArg::codegen() {
	if (debug == true) cout << "In codegen of: CalloutArg" << endl << flush;

	Value *v = ConstantInt::get(Context, APInt(32, 1));
	return v;
}

// Value *ParamList::codegen() {
// 	Value *v = ConstantInt::get(Context, APInt(32, 1));
// 	return v;
// }

// Value *MethodArgInpList::codegen() {
// 	Value *v = ConstantInt::get(Context, APInt(32, 1));
// 	return v;
// }

// Value *TerminalVariable::codegen() {
// 	Value *v = ConstantInt::get(Context, APInt(32, 1));
// 	return v;
// }

// Value *ArrayTerminalVariable::codegen() {
// 	Value *v = ConstantInt::get(Context, APInt(32, 1));
// 	return v;
// }

#include "structs.hpp"
#include "functiontable.hpp"
#include "tokens.h"
#include <iostream>

bool containsValue(const std::vector<char*> vec, char* value) {
    for (const auto& element : vec) {
        if (element == value) {
            return true;
        }
    }
    return false;
}


ReturnHandler::ReturnHandler(){

}

Exp_::Exp_(){};

ExpList::ExpList(Exp h, ExpList* t) {
        head = h;
        next = t;
    };

ExpList::ExpList(){

};


IdList::IdList(char* h, IdList* t) {
    head = h;
    next = t;
};


StmList::StmList(Stm h, StmList* s){


    head = h;
    next = s;
}

StmList::StmList(){}


ParamList::ParamList(Param_declaration h, ParamList* n){
        head = h;
        next = n;
}

ParamList::ParamList(){}


Param_declaration::Param_declaration(char* n, int t){
        name = n;
        type = t;
}

Param_declaration::Param_declaration(){}


PrintStm::PrintStm(ExpList* expl){
    explist = expl;
}

void PrintStm::interp(){
     while(explist != nullptr){

            ReturnValue returnValue = explist->head->interp();
            //Check the type of ReturnValue

            if(returnValue.boolValue == nullptr){
                std::cout << std::to_string(*returnValue.intValue) << " ";
            }
            else{
                std::cout << std::to_string(*returnValue.boolValue) << " ";
            }
  
            explist = explist->next;
        }
        std::cout << "\n";
}


Function_signature::Function_signature(){

}

Function_signature::Function_signature(ParamList p, int t){
    params = p;
    type = t;
}


Function_DeclarationStm::Function_DeclarationStm(Function_signature sig, StmList stml, char* id){
    signature = sig;
    stmlist = stml;
    identifier = id;
}

Function_DeclarationStm::Function_DeclarationStm(){}

void Function_DeclarationStm::interp(){
    int returnType = signature.type;
    ParamList* paramlist = &signature.params;

    std::vector<int> paramtypes;
    std::vector<char*> paramnames;

    while(paramlist != nullptr){
        paramtypes.push_back(paramlist->head.type);
        paramnames.push_back(paramlist->head.name);

        paramlist = paramlist->next;
    }

    Function function(identifier, paramnames, paramtypes, returnType, stmlist);
    
    //Add function to table
    functionhandler.addFunction(identifier, &function);
}


DeclarationStm::DeclarationStm(int dcltype, IdList* idl, ExpList* expl){
    declaredType = dcltype;
    idlist = idl;
    explist = expl;
}

DeclarationStm::DeclarationStm(){

}

void DeclarationStm::interp(){
    std::vector<char*> declared_ids;
    if(explist == nullptr){
        //Default assignment of value, but only if a type is specified
        while(idlist != nullptr){
            
            if(containsValue(declared_ids, idlist->head)){
                //error
            }
            declared_ids.push_back(idlist->head);


            if(declaredType == INT){
                symbolhandler.addSymbol(idlist->head, 0);
            }
            else if(declaredType == BOOL){
                symbolhandler.addSymbol(idlist->head, true);
            }
            else{
                //Throw error
            }
        }
    }
    else{
            while(idlist != nullptr){
            
            if(containsValue(declared_ids, idlist->head)){
                //error
            }
            declared_ids.push_back(idlist->head);

            if((idlist != nullptr && explist == nullptr) || (idlist == nullptr && explist != nullptr) ){
                //throw error
            }
            
            ReturnValue returnValue =  explist->head->interp();

            //Since a declaration without a specified type is possible it needs runtime typechecking.
            if(declaredType == INT){
                if(returnValue.boolValue == nullptr){
                    symbolhandler.addSymbol(idlist->head, returnValue.intValue);
                }
                else{
                    //throw error
                }
            }
            else if(declaredType == BOOL){
                if(returnValue.boolValue == nullptr){
                    //throw error
                }else{
                    symbolhandler.addSymbol(idlist->head, returnValue.boolValue);
                }
            }
            else if(declaredType == -1){
                if(returnValue.boolValue == nullptr){
                    symbolhandler.addSymbol(idlist->head, returnValue.intValue);
                }else{
                    symbolhandler.addSymbol(idlist->head, returnValue.boolValue);
                }
            }
            else{
                //throw error
            }
            
            idlist = idlist->next;
            explist = explist->next;             
        }
    }
}


AssignStm::AssignStm(IdList* id, ExpList* e){
    idlist = id;
    explist = e;
}

AssignStm::AssignStm(){

}

void AssignStm::interp(){
    std::vector<char*> assigned_ids;

    while(idlist != nullptr){

        if(containsValue(assigned_ids, idlist->head)){
            //error
        }
        
        assigned_ids.push_back(idlist->head);

        if((idlist != nullptr && explist == nullptr) || (idlist == nullptr && explist != nullptr) ){
            //throw error
        }
        
        ReturnValue lookupReturn = symbolhandler.lookupSymbol(idlist->head);
        ReturnValue interpReturn = explist->head->interp();

        if((lookupReturn.boolValue == nullptr && interpReturn.intValue != nullptr) || (lookupReturn.intValue == nullptr && interpReturn.boolValue != nullptr)){
            //type error
        }
        else{
            symbolhandler.updateSymbol(idlist->head, explist->head->interp());
        }

        idlist = idlist->next;
        explist = explist->next;
    }
}


ReturnStm::ReturnStm(Exp e){
    expr = e;
}


BlockStm::BlockStm(){

}

BlockStm::BlockStm(StmList *stl){
    stmlist = stl;
}

void BlockStm::interp(){
       
    symbolhandler.pushSymbolTable(SymbolTable());
    while(stmlist != nullptr){

        if(std::is_same<decltype(stmlist->head), ReturnStm>::value){
                ReturnStm* returnstm = static_cast<ReturnStm*>(stmlist->head);

                returnhandler.returnEncountered = true;
                returnhandler.returnExp =  returnstm->expr;
                //returnstm.interp();

                if(stmlist->next != nullptr){
                    //Unreachable code error
                }

                return;
        }          
    }
    symbolhandler.popSymbolTable();
}

VoidFunctionStm::VoidFunctionStm(ExpList args, char* id){
    arguments = args;
    identifier = id;
}

VoidFunctionStm::VoidFunctionStm(){};

void VoidFunctionStm::interp(){
    //Call the function from the function table 
    Function function = functionhandler.lookupFunction(identifier);
    int returntype = function.functionType;
    StmList* stmlist = &function.stmlist;

    //New scope definition
    symbolhandler.pushSymbolTable(SymbolTable());

    //Pushing the arguments onto the symbol table of the new scope
    ExpList* args = &arguments;
    std::vector<char*> paramNames = function.paramNames;
    std::vector<int> paramTypes = function.paramTypes;

    if(args != nullptr){

        if(paramNames.size() == 0 ){
            //Too many arguments error
            //(function has no arguments)
        }

        int i = 0;
        while (args->next != nullptr)
        {
            if(i == paramNames.size() && args->next != nullptr){
                //Too many arguments
            }
            else if(i != paramNames.size() && args->next == nullptr){
                //Not enough arguments
            }


            ReturnValue returnValue = args->head->interp();

            //Couldn't use typeinfo due to bogus inclusion error
            //So I have to do it the stupid way
            if(returnValue.intValue != nullptr){
                if(paramTypes[i] != INT){
                    //wrong type
                }
                else{
                    symbolhandler.addSymbol(paramNames[i], returnValue);
                }
            }
            else if(returnValue.boolValue != nullptr){
                if(paramTypes[i] != BOOL){                      
                    //wrong type
                }
                else{
                    symbolhandler.addSymbol(paramNames[i], returnValue);
                }
            }
                            
            i++;
            args = args->next;
        }
    }

    //Executing the function

    
    while(stmlist != nullptr){
        
        if(std::is_same<decltype(stmlist->head), ReturnStm>::value){
            
            ReturnStm* returnstm = static_cast<ReturnStm*>(stmlist->head);
            ReturnValue returnValue = returnstm->expr->interp();

            //returnstm.interp();

            if(returnstm->expr != nullptr && returntype == -1){
                //no return value in void defined function allowed
            }

            if(returnValue.boolValue != nullptr){
                if(returntype != BOOL){
                    //wrong return type error
                }
            }
            else if(returnValue.intValue != nullptr){
                if(returntype != INT){
                    //wrong return type error
                }
            }

            if(stmlist->next != nullptr){
                //Unreachable code error
            }

            return;
        }
        else {
            stmlist->head->interp(); // Execute the nested block
            if (returnhandler.returnEncountered) {
                
                ReturnValue returnValue = returnhandler.returnExp->interp();

                if(returnhandler.returnExp != nullptr && returntype == -1){
                    //no return in void function allowed
                }

                if(returnValue.boolValue != nullptr){
                    if(returntype != BOOL){
                        //wrong return type error
                    }
                }
                else if(returnValue.intValue != nullptr){
                    if(returntype != INT){
                        //wrong return type error
                    }
                }

                returnhandler.returnEncountered = false;

                // Bubble up the return statement
                return;
            }
        }

    }
}


IncDecStm::IncDecStm(){}

IncDecStm::IncDecStm(int ac, char* id){
    action = ac;
    identifier = id;
}

void IncDecStm::interp(){
    ReturnValue returnValue = symbolhandler.lookupSymbol(identifier);

    if(returnValue.intValue != nullptr){
        
        if(action == DEC){
            *returnValue.intValue--;
        }
        else if(action == INC){
            *returnValue.intValue++;
        }

        symbolhandler.updateSymbol(identifier, returnValue);
    }
    else{
        //Throw type error because it can't be bool
    }
}


If_stm::If_stm(){}

If_stm::If_stm(Exp ex, BlockStm bstm){
        exp = ex;
        blockStm = bstm;
}

void If_stm::interp(){
    ReturnValue returnValue = exp->interp();

    if(returnValue.boolValue != nullptr){
        if(returnValue.boolValue){
            blockStm.interp();
        }
    }
    else{
        //Wrong type error
    }
}


For_stm::For_stm(){}

For_stm::For_stm(Exp ex, BlockStm bstm){
    exp = ex;
    blockStm = bstm;
}

void For_stm::interp(){
    ReturnValue returnValue = exp->interp();

    if(returnValue.boolValue != nullptr){
        while(!returnValue.boolValue){
            blockStm.interp();
            returnValue = exp->interp();
        }
    }
    else{
    //Wrong type error
    }
}


IntlitExp::IntlitExp(){

}

IntlitExp::IntlitExp(int i){
    intlit = i;
}

ReturnValue IntlitExp::interp(){
    return ReturnValue(intlit);
}


BoollitExp::BoollitExp(){

}

BoollitExp::BoollitExp(bool b){
    boollit = b;
}

ReturnValue BoollitExp::interp() {
    return ReturnValue(boollit);
}

ArithmeticOpExp::ArithmeticOpExp(){

}

ArithmeticOpExp::ArithmeticOpExp(Exp l, int op, Exp r){
    left = l;
    right = r;
    oper = op;
}

ReturnValue ArithmeticOpExp::interp(){
    int value_return;
    ReturnValue result_left = left->interp();
    ReturnValue result_right = right->interp();

    if(result_left.intValue != nullptr && result_left.intValue != nullptr ){
        if(oper == PLUS) {
            value_return = *result_left.intValue + *result_right.intValue; 
        }
        else if(oper == MIN){
            value_return = *result_left.intValue - *result_right.intValue;
        }
        else if (oper == MUL) {
            value_return = *result_left.intValue * *result_right.intValue;
        }
        else if (oper == DIV){
            value_return = *result_left.intValue / *result_right.intValue;
        }
    }

    return ReturnValue(value_return);
}


ArithmeticAssignOpExp::ArithmeticAssignOpExp(){}

ArithmeticAssignOpExp::ArithmeticAssignOpExp(char* l, int op, Exp r) {
    left = l;
    right = r;
    oper = op;
};

ReturnValue ArithmeticAssignOpExp::interp(){
    ReturnValue returnValue = right->interp();

    if(returnValue.intValue != nullptr){
        int symbolVal = *symbolhandler.lookupSymbol(left).intValue;

        if (oper == PLUSASSIGN){
            symbolVal += *returnValue.intValue;
        }
        else if (oper == MINASSIGN){
            symbolVal -= *returnValue.intValue;
        }
        else if (oper == MULASSIGN){
            symbolVal *= *returnValue.intValue;
        }
        else if (oper == DIVASSIGN){
            symbolVal /= *returnValue.intValue;
        }

        symbolhandler.updateSymbol(left, ReturnValue(symbolVal));
    }
    else{
        //Type error
    }   
}


BooleanOpExp::BooleanOpExp(){}

BooleanOpExp::BooleanOpExp(Exp l, int op, Exp r) {
    left = l;
    right = r;
    oper = op;
};

ReturnValue BooleanOpExp::interp(){
    //Check if left and right types are equal
        //if not throw yyerror

        ReturnValue returnValueLeft = left->interp();
        ReturnValue returnValueRight = right->interp();

        if(returnValueLeft.boolValue != nullptr && returnValueRight.boolValue != nullptr)
        {
            if(oper == NE){
                return *returnValueLeft.boolValue != *returnValueRight.boolValue;           
            }
            else if(oper == EQ){
                return *returnValueLeft.boolValue == *returnValueRight.boolValue;
            }
            else if(oper == AND){
                return *returnValueLeft.boolValue && *returnValueRight.boolValue;
            }
            else if(oper == OR){
                return *returnValueLeft.boolValue || *returnValueRight.boolValue;
            }
        }
        else{
            //Type error
        }

        return false;
}


BooleanArithmeticOpExp::BooleanArithmeticOpExp(){}

BooleanArithmeticOpExp::BooleanArithmeticOpExp(Exp l, int op, Exp r){
    left = l;
    right = r;
    oper = op;
}

ReturnValue BooleanArithmeticOpExp::interp(){
    //Check if left and right types are both numeric
    //if not throw yyerror

    ReturnValue returnValueLeft = left->interp();
    ReturnValue returnValueRight = right->interp();

    if(returnValueLeft.intValue != nullptr && returnValueRight.intValue != nullptr){

        if(oper == GT){
            return *returnValueLeft.intValue > *returnValueRight.intValue;           
        }
        else if(oper == LT){
            return *returnValueLeft.intValue < *returnValueRight.intValue; 
        }
        else if(oper == GE){
            return *returnValueLeft.intValue >= *returnValueRight.intValue; 
        }
        else if(oper == GT){
            return *returnValueLeft.intValue <= *returnValueRight.intValue; 
        }
    }
    else{
        //Throw error
    }

    return false;
}


NotExp::NotExp(){}

NotExp::NotExp(Exp ex){
    expr = ex;
}

ReturnValue NotExp::interp(){
    if(expr->interp().boolValue == nullptr){
        //type error
    }

    return !(*expr->interp().boolValue);
}


FunctionExp::FunctionExp(){}

FunctionExp::FunctionExp(ExpList args, char* id){
    arguments = args;
    identifier = id;
}

ReturnValue FunctionExp::interp(){
    //Call the function from the function table 
    Function function = functionhandler.lookupFunction(identifier);
    int returntype = function.functionType;
    StmList* stmlist = &function.stmlist;

    //New scope definition
    symbolhandler.pushSymbolTable(SymbolTable());

    //Pushing the arguments onto the symbol table of the new scope
    ExpList* args = &arguments;
    std::vector<char*> paramNames = function.paramNames;
    std::vector<int> paramTypes = function.paramTypes;

    if(returntype == -1){
        //a void function expression is not allowed
    }

    if(args != nullptr){

        if(paramNames.size() == 0 ){
            //Too many arguments error
            //(function has no arguments)
        }

        int i = 0;
        while (args != nullptr)
        {

            ReturnValue returnValue = args->head->interp();

            if(i == paramNames.size() && args->next != nullptr){
                //Too many arguments
            }
            else if(i != paramNames.size() && args->next == nullptr){
                //Not enough arguments
            }

            if(returnValue.intValue != nullptr){
                if(paramTypes[i] != INT){
                    //wrong type
                }
            }
            else if(returnValue.boolValue != nullptr){
                if(paramTypes[i] != BOOL){
                    //wrong type
                }
            }
            
            symbolhandler.addSymbol(paramNames[i], returnValue);
            i++;
            args = args->next;
        }
    }

    //Executing the function

    if(stmlist != nullptr){
        while(stmlist != nullptr){
            
            if(std::is_same<decltype(stmlist->head), ReturnStm>::value){
                ReturnStm* returnstm = static_cast<ReturnStm*>(stmlist->head);
                ReturnValue returnValue = returnstm->expr->interp();

                //returnstm.interp();

                if(returnValue.boolValue != nullptr){
                    if(returntype != BOOL){
                        //wrong return type error
                    }
                }
                else if(returnValue.intValue != nullptr){
                    if(returntype != INT){
                        //wrong return type error
                    }
                }

                if(stmlist->next != nullptr){
                    //Unreachable code error
                }

                return returnValue;
            }
            else {
                stmlist->head->interp(); // Execute the nested block
                if (returnhandler.returnEncountered) {
                    
                    
                    if(returnhandler.returnExp != nullptr && returntype == -1){
                        //no return in void function allowed
                    }

                    ReturnValue returnValue = returnhandler.returnExp->interp();

                    if(returnValue.boolValue != nullptr){
                        if(returntype != BOOL){
                            //wrong return type error
                        }
                    }
                    else if(returnValue.intValue != nullptr){
                        if(returntype != INT){
                            //wrong return type error
                        }
                    }

                    returnhandler.returnEncountered = false;
                    // Bubble up the return statement
                    return returnValue;
                }
            }

        }
    } 
}



#include "structs.hpp"
#include "functiontable.hpp"
#include "symboltable.hpp"
#include "tokens.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <type_traits>

bool containsValue(const std::vector<char*> vec, char* value) {
    for (const auto& element : vec) {
        if (!strcmp(element, value)) {
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


ParamList::ParamList(Param_declaration* h, ParamList* n){
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

    std::vector<std::string> printStrings;

    while(explist != nullptr){

            ReturnValue returnValue = explist->head->interp();
            //Check the type of ReturnValue

            if(returnValue.boolValue == nullptr){
                printStrings.push_back(std::to_string(*returnValue.intValue));
            } 
            else{
                if(*returnValue.boolValue == 1){
                    printStrings.push_back("true");
                }
                else{
                    printStrings.push_back("false");
                }                
            }
  
            explist = explist->next;
    }
    
    std::reverse(printStrings.begin(), printStrings.end());
    
    for(auto&& i: printStrings){
        std::cout << i << " ";
    }

    std::cout << "\n";
}


Function_signature::Function_signature(){

}

Function_signature::Function_signature(ParamList* p, int t){
    params = p;
    type = t;
}


Function_DeclarationStm::Function_DeclarationStm(Function_signature* sig, StmList* stml, char* id){

    signature = sig;
    stmlist = stml;
    identifier = id;

    
    //RETURN TYPE TYPECHECKING, COMPARE EACH ELEMENT WITH SIGNATURE
    std::cout << "EVALUATING TYPES" << std::endl;
    for(int i = 0; i < returnTypesInStatement.size(); i++){
        if(returnTypesInStatement[i] != signature->type){
            std::cout << "ERROR: WRONG RETURN TYPE IN FUNCTION " << identifier << std::endl;
            break;
        }
    }

    //CLEARS FOR THE NEXT FUNCTION STATEMENT
    returnTypesInStatement.clear();



}

Function_DeclarationStm::Function_DeclarationStm(){}

void Function_DeclarationStm::interp(){

    int returnType = signature->type;
    ParamList* paramlist = signature->params;

    std::vector<int> paramtypes;
    std::vector<char*> paramnames;


    while(paramlist != nullptr){
        paramtypes.push_back(paramlist->head->type);
        paramnames.push_back(paramlist->head->name);

        paramlist = paramlist->next;
    }

    //Add function to table
    functionhandler.addFunction( new Function(identifier, paramnames, paramtypes, returnType, stmlist));
}


DeclarationStm::DeclarationStm(int dcltype, IdList* idl, ExpList* expl){
    declaredType = dcltype;
    idlist = idl;
    explist = expl;
}

DeclarationStm::DeclarationStm(){

}

void DeclarationStm::interp(){
 
    std::cout << "INTERPRETING DECLR STM" << std::endl;

    std::vector<char*> declared_ids;
    if(explist == nullptr){
        //Default assignment of value, but only if a type is specified
        while(idlist != nullptr){
            
            if(containsValue(declared_ids, idlist->head)){
                
                std::cout << idlist->head << std::endl;

                for(auto&& i: declared_ids){
                    std::cout << i << " ";
                }
                std::cout << std::endl;

                std::cout << "Error: duplicate indentifier in declaration" << std::endl;
                return;
            }


            if(declaredType == INT){
                symbolhandler.addSymbol(idlist->head, ReturnValue(0));
                std::cout << "Added int value " << idlist->head << " to symbol table" << std::endl;
            }
            else if(declaredType == BOOL){
                symbolhandler.addSymbol(idlist->head, ReturnValue(true));
                std::cout << "Added bool value " << idlist->head << " to symbol table" << std::endl;
            }
            else{
                std::cout << "Type error" << std::endl;
            }

             declared_ids.push_back(idlist->head);

             idlist = idlist->next;
        }
    }
    else{
        while(idlist != nullptr){
            
            if(containsValue(declared_ids, idlist->head)){
                std::cout << "Error: duplicate indentifier in declaration" << std::endl;
            }
            declared_ids.push_back(idlist->head);


            //TODO: fix too many arguments
            if((idlist->next != nullptr && explist->next == nullptr) ){
                std::cout << "Error: argument count not matching" << std::endl;
            }

            if(idlist->next == nullptr && explist->next != nullptr){
                std::cout << "Error: argument count not matching" << std::endl;
            }
            
            ReturnValue returnValue =  explist->head->interp();
            

            if(declaredType == INT){

                if(returnValue.boolValue == nullptr){
                    symbolhandler.addSymbol(idlist->head, returnValue);

                    std::cout << "Added int value " << idlist->head << " to symbol table with value " << *returnValue.intValue << std::endl;
                }
                else{
                    //throw error
                }
            }
            else if(declaredType == BOOL){

                if(returnValue.boolValue == nullptr){
                    //throw error
                }else{
                    symbolhandler.addSymbol(idlist->head, returnValue);
                    std::cout << "Added bool value " << idlist->head << " to symbol table with value " << *returnValue.boolValue<< std::endl;
                }
            }
            else if(declaredType == -1){
                if(returnValue.boolValue == nullptr){
                    symbolhandler.addSymbol(idlist->head, returnValue);
                    std::cout << "Added int value " << idlist->head << " to symbol table with value " << *returnValue.intValue << std::endl;

                }else{
                    symbolhandler.addSymbol(idlist->head, returnValue);
                    std::cout << "Added bool value " << idlist->head << " to symbol table" << std::endl;
                    std::cout << "Added bool value " << idlist->head << " to symbol table with value " << *returnValue.boolValue<< std::endl;
                }
            }
            else{
                std::cout << "type error " << declaredType << std::endl;
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

            std::cout << "Duplicate identifier in assign statement";
            return;
        }
        
        assigned_ids.push_back(idlist->head);

        if(idlist->next != nullptr && explist->next == nullptr){
            std::cout << "Error: argument count not matching" << std::endl;
        }

        if(idlist->next == nullptr && explist->next != nullptr){
            std::cout << "Error: argument count not matching" << std::endl;
        }
        
        ReturnValue lookupReturn = symbolhandler.lookupSymbol(idlist->head);
        ReturnValue interpReturn = explist->head->interp();

        std::cout << "INT VAL: " << *interpReturn.intValue << std::endl;

        if(lookupReturn.boolValue == nullptr && interpReturn.boolValue != nullptr || lookupReturn.intValue == nullptr && interpReturn.intValue != nullptr){
            std::cout << "Unmatching types" << std::endl;
        }
        else{
            std::cout << "Updating symbol" << std::endl;
            symbolhandler.updateSymbol(idlist->head, explist->head->interp());
        }

        idlist = idlist->next;
        explist = explist->next;
    }
}


ReturnStm::ReturnStm(Exp e){
    
    
    int i = -1;

    if(e != nullptr){
        if(e->interp().boolValue != nullptr){
            i = BOOL;
        }else{
            i = INT;
        }
    }

    returnTypesInStatement.push_back(i);

    expr = e;
}


BlockStm::BlockStm(){

}

BlockStm::BlockStm(StmList* stl){
    stmlist = stl;
}

void BlockStm::interp(){
    if(stmlist == nullptr) return;

    StmList* list = new StmList();
    list->head = stmlist->head;
    list->next = stmlist->next;

    symbolhandler.pushSymbolTable(SymbolTable());
    while(list != nullptr){
        std::cout << "EXECUTING BLOCKSTATEMENT" << " \n";
        if(dynamic_cast<ReturnStm*>(list->head) != nullptr){

                std::cout << "RETURN STATEMENT ENCOUNTERED" << " \n";

                ReturnStm* returnstm = static_cast<ReturnStm*>(list->head);

                returnhandler.returnEncountered = true;
                returnhandler.returnExp =  returnstm->expr;

                if(list->next != nullptr){
                    //Unreachable code error
                }

                return;
        }
        else{
            //returnsm encounter
            list->head->interp();
            if(returnhandler.returnEncountered){

                symbolhandler.popSymbolTable();
                return;
            }
        }

        list = list->next;      
    }
    symbolhandler.popSymbolTable();
}

VoidFunctionStm::VoidFunctionStm(ExpList* args, char* id){
    arguments = args;
    identifier = id;
}

VoidFunctionStm::VoidFunctionStm(){};

void VoidFunctionStm::interp(){
    std::cout << "interpreting void function stm " << std::endl;
    //Call the function from the function table 
    Function function = functionhandler.lookupFunction(identifier);
    int returntype = function.functionType;
    StmList* stmlist = function.stmlist;

     

    //New scope definition
    symbolhandler.pushSymbolTable(SymbolTable());

    //Pushing the arguments onto the symbol table of the new scope
    ExpList* args = arguments;
    std::vector<char*> paramNames = function.paramNames;
    std::vector<int> paramTypes = function.paramTypes;
    std::vector<Exp> paramArgs;

   
    std::cout << "Printing param names " << std::endl;
    for(auto&& i: paramNames){
        std::cout << i << " " << std::endl;
    }

    std::cout << "Printing param types " << std::endl;
    for(auto&& i: paramTypes){
        std::cout << i << " " << std::endl;
    }

    while(args != nullptr){
        paramArgs.push_back(args->head);
        args = args->next;
    }
    

    if(paramArgs.size() == paramNames.size()){
        if(paramArgs.size() != 0){
            for(int i=0; i < paramArgs.size(); i++)
            {
                
                ReturnValue returnValue = paramArgs[i]->interp();

                if(returnValue.intValue != nullptr){
                    if(paramTypes[i] != INT){
                        std::cout << "Type error " << std::endl;
                        break;
                    }
                    else{
                        symbolhandler.addSymbol(paramNames[i], returnValue);
                    }
                }
                else if(returnValue.boolValue != nullptr){
                    if(paramTypes[i] != BOOL){                      
                        std::cout << "Type error " << std::endl;
                    }
                    else{
                        symbolhandler.addSymbol(paramNames[i], returnValue);
                    }
                }
            }
        }
    }
    else if(paramArgs.size() < paramNames.size()){
        std::cout << "Not enough arguments " << std::endl;
    }
    else{
        std::cout << "Too many arguments " << std::endl;
    }
    
    //Executing the function
    while(stmlist != nullptr){
        
        if(dynamic_cast<ReturnStm*>(stmlist->head) != nullptr){

            std::cout << "Testpoint" << std::endl;

            
            ReturnStm* returnstm = dynamic_cast<ReturnStm*>(stmlist->head);

            
            if(returnstm->expr != nullptr && returntype == -1){
                std::cout << "Error: no return value in void defined function allowed" << std::endl;
                return;
            }

            if(returnstm->expr == nullptr && returntype != -1){
                std::cout << "Error: function needs a return type" << std::endl;
                return;
            }

            ReturnValue returnValue = returnstm->expr->interp();

            //returnstm.interp();


            if(returnValue.boolValue != nullptr){
                if(returntype != BOOL){           
                    std::cout << "wrong return type error" << std::endl;
                }
            }
            else if(returnValue.intValue != nullptr){
                if(returntype != INT){
                    std::cout << "wrong return type error" << std::endl;
                }
            }

            if(stmlist->next != nullptr){
                std::cout << "Unreachable code" << std::endl;
            }

            return;
        }
        else {
            stmlist->head->interp(); // Execute the nested block
            if (returnhandler.returnEncountered) {
                
                ReturnValue returnValue = returnhandler.returnExp->interp();

                if(returnhandler.returnExp != nullptr && returntype == -1){
                    std::cout << "No return statement in void function allowed" << std::endl;
                }

                if(returnValue.boolValue != nullptr){
                    if(returntype != BOOL){
                        std::cout << "Wrong return type error" << std::endl;
                    }
                }
                else if(returnValue.intValue != nullptr){
                    if(returntype != INT){
                        std::cout << "Wrong return type error" << std::endl;
                    }
                }

                returnhandler.returnEncountered = false;

                // Bubble up the return statement
                return;
            }
        }

        stmlist = stmlist->next;

    }

    if(returntype != -1 && !returnhandler.returnEncountered){
        std::cout << "Error: function needs a return type" << std::endl;
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
        
        int value = *returnValue.intValue;

        if(action == DEC){
            value -= 1;
        }
        else if(action == INC){
            value += 1;
        }

        symbolhandler.updateSymbol(identifier, ReturnValue(value));
    }
    else{
        //Throw type error because it can't be bool
    }
}


If_stm::If_stm(){}

If_stm::If_stm(Exp ex, Stm bstm){
        exp = ex;
        blockStm = static_cast<BlockStm*>(bstm);
}

void If_stm::interp(){

    ReturnValue returnValue = exp->interp();
    
    // std::cout << *returnValue.boolValue << " " << returnValue.intValue << " ";



    if(returnValue.boolValue != nullptr){

        if(*returnValue.boolValue == 1){            
            blockStm->interp();
        }
    }
    else{
        std::cout << "\nType error\n";
    }
}


For_stm::For_stm(){}

For_stm::For_stm(Exp ex, Stm bstm){
    exp = ex;
    blockStm = static_cast<BlockStm*>(bstm);
}

void For_stm::interp(){
    ReturnValue returnValue = exp->interp();

    if(returnValue.boolValue != nullptr){
        std::cout << "GOING INTO LOOP" << " \n";
        while(*returnValue.boolValue){
            std::cout << "EXECUTING LOOP" << " \n";

            blockStm->interp();
            returnValue = exp->interp();
            std::cout << "Value of a: " << *returnValue.boolValue;
        }
    }
    else{
    //Wrong type error
    }
}


ArithmeticAssignOpStm::ArithmeticAssignOpStm() {  };

ArithmeticAssignOpStm::ArithmeticAssignOpStm(char* l, int op, Exp r) {
    left = l;
    right = r;
    oper = op;
};

void ArithmeticAssignOpStm::interp() {
    ReturnValue returnValue = right->interp();

    if (returnValue.intValue != nullptr) {
        int symbolVal = *symbolhandler.lookupSymbol(left).intValue;

        if (oper == PLUSASSIGN) {
            symbolVal += *returnValue.intValue;
        }
        else if (oper == MINASSIGN) {
            symbolVal -= *returnValue.intValue;
        }
        else if (oper == MULASSIGN) {
            symbolVal *= *returnValue.intValue;
        }
        else if (oper == DIVASSIGN) {
            symbolVal /= *returnValue.intValue;
        }

        symbolhandler.updateSymbol(left, ReturnValue(symbolVal));
    }
    else {
        //Type error
    }
}


ProgramStm::ProgramStm(StmList* stml){
    stmlist = stml;
}

ProgramStm::ProgramStm(){};

void ProgramStm::interp(){

    while(stmlist != nullptr){

        if(dynamic_cast<ReturnStm*>(stmlist->head) == nullptr && dynamic_cast<ReturnStm*>(stmlist->head) == nullptr){
            std::cout << "Non-declaration statement outside function body" << std::endl;
        }
        else{
            stmlist->head->interp();
            stmlist = stmlist->next;
        }
    }

    VoidFunctionStm mainfunc = VoidFunctionStm(nullptr, "main");
    mainfunc.interp();
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
    ReturnValue result_right = right->interp();
    ReturnValue result_left = left->interp();
    

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
        else if(returnValueLeft.intValue != nullptr && returnValueRight.intValue != nullptr){
            if(oper == NE){
                return *returnValueLeft.intValue != *returnValueRight.intValue;           
            }
            else if(oper == EQ){
                return *returnValueLeft.intValue == *returnValueRight.intValue;
            }
        }
        else{
            std::cout << "Error: types not matching" << std::endl;
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
        else if(oper == LE){
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

FunctionExp::FunctionExp(ExpList* args, char* id){
    arguments = args;
    identifier = id;
}

ReturnValue FunctionExp::interp(){
   std::cout << "interpreting void function stm " << std::endl;
    //Call the function from the function table 
    Function function = functionhandler.lookupFunction(identifier);
    int returntype = function.functionType;
    StmList* stmlist = function.stmlist;

     

    //New scope definition
    symbolhandler.pushSymbolTable(SymbolTable());

    //Pushing the arguments onto the symbol table of the new scope
    ExpList* args = arguments;
    std::vector<char*> paramNames = function.paramNames;
    std::vector<int> paramTypes = function.paramTypes;
    std::vector<Exp> paramArgs;

   
    std::cout << "Printing param names " << std::endl;
    for(auto&& i: paramNames){
        std::cout << i << " " << std::endl;
    }

    std::cout << "Printing param types " << std::endl;
    for(auto&& i: paramTypes){
        std::cout << i << " " << std::endl;
    }

    while(args != nullptr){
        paramArgs.push_back(args->head);
        args = args->next;
    }
    

    if(paramArgs.size() == paramNames.size()){
        
        if(paramArgs.size() != 0){
            for(int i=0; i < paramArgs.size(); i++)
            {
            
                ReturnValue returnValue = paramArgs[i]->interp();

                if(returnValue.intValue != nullptr){
                    if(paramTypes[i] != INT){
                        std::cout << "Type error " << std::endl;
                        break;
                    }
                    else{
                        symbolhandler.addSymbol(paramNames[i], returnValue);
                    }
                }
                else if(returnValue.boolValue != nullptr){
                    if(paramTypes[i] != BOOL){                      
                        std::cout << "Type error " << std::endl;
                    }
                    else{
                        symbolhandler.addSymbol(paramNames[i], returnValue);
                    }
                }
            }
        }
    }
    else if(paramArgs.size() < paramNames.size()){
        std::cout << "Not enough arguments " << std::endl;
    }
    else{
        std::cout << "Too many arguments " << std::endl;
    }
    
    //Executing the function
    while(stmlist != nullptr){
        
        if(dynamic_cast<ReturnStm*>(stmlist->head) != nullptr){

            std::cout << "Testpoint" << std::endl;

            
            ReturnStm* returnstm = dynamic_cast<ReturnStm*>(stmlist->head);

            
            if(returnstm->expr != nullptr && returntype == -1){
                std::cout << "Error: no return value in void defined function allowed" << std::endl;
            }

            if(returnstm->expr == nullptr && returntype != -1){
                std::cout << "Error: function needs a return type" << std::endl;
            }

            ReturnValue returnValue = returnstm->expr->interp();

            //returnstm.interp();


            if(returnValue.boolValue != nullptr){
                if(returntype != BOOL){           
                    std::cout << "wrong return type error" << std::endl;
                }
            }
            else if(returnValue.intValue != nullptr){
                if(returntype != INT){
                    std::cout << "wrong return type error" << std::endl;
                }
            }

            if(stmlist->next != nullptr){
                std::cout << "Unreachable code" << std::endl;
            }

            return returnValue;
        }
        else {
            stmlist->head->interp(); // Execute the nested block
            if (returnhandler.returnEncountered) {
                
                ReturnValue returnValue = returnhandler.returnExp->interp();

                if(returnhandler.returnExp != nullptr && returntype == -1){
                    std::cout << "No return statement in void function allowed" << std::endl;
                }

                if(returnValue.boolValue != nullptr){
                    if(returntype != BOOL){
                        std::cout << "Wrong return type error" << std::endl;
                    }
                }
                else if(returnValue.intValue != nullptr){
                    if(returntype != INT){
                        std::cout << "Wrong return type error" << std::endl;
                    }
                }

                returnhandler.returnEncountered = false;

                // Bubble up the return statement
                return returnhandler.returnExp->interp();
            }
        }

        stmlist = stmlist->next;

    }

    if(returntype != -1 && !returnhandler.returnEncountered){
        std::cout << "Error: function needs a return type" << std::endl;
    }

    return ReturnValue();
}
 

IdExp::IdExp(){

}

IdExp::IdExp(char* id){
    identifier = id;
    std::cout << "CONSTRUCTED IDENTIFIER "  << identifier << std::endl;

}

ReturnValue IdExp::interp(){
    std::cout << "INTERPRETING ID EXP " << identifier << std::endl;

    return symbolhandler.lookupSymbol(identifier);
}
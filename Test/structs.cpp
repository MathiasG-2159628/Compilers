#include "structs.hpp"
#include "functiontable.hpp"
#include "symboltable.hpp"
#include "tokens.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <type_traits>
#include "symboltypetable.hpp"
#include "functypetable.hpp"

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

ExpList::ExpList(){};


IdList::IdList(char* h, IdList* t) {
    head = h;
    next = t;
};

IdList::IdList(){};


StmList::StmList(Stm h, StmList* s){
    if(dynamic_cast<Function_DeclarationStm*>(h) == nullptr){
        head = h;
        next = s;
    }
    else{
        std::cout << "No function definition allowed inside block" << std::endl;
    }
    
}

StmList::StmList(){}


ParamList::ParamList(Param_declaration* h, ParamList* n){  
        head = h;
        next = n;
}

ParamList::ParamList(){}

DeclarationList::DeclarationList(Stm h, DeclarationList* n){

        if(dynamic_cast<DeclarationStm*>(h) == nullptr && dynamic_cast<Function_DeclarationStm*>(h) == nullptr && dynamic_cast<PackageStm*>(h) == nullptr){
             std::cout << "Error: non-declaration statement not allowed in global scope" << std::endl;
             
        }else{

            if(dynamic_cast<PackageStm*>(h) != nullptr){
                PackageStm* pckgstm = dynamic_cast<PackageStm*>(h);
                if(!strcmp(pckgstm->packageid, "main")){
                    std::cout << "package included!" << std::endl;
                    packageMainIncluded = true;
                }
            }
            else{
                if(!packageMainIncluded){
                    std::cout << "Error: expected package" << std::endl;
                }
            }

            head = h;
            next = n;
        }
}

DeclarationList::DeclarationList(){}


Param_declaration::Param_declaration(char* n, int t){
        name = n;
        type = t;
}

Param_declaration::Param_declaration(){}


ProgramStm::ProgramStm(DeclarationList* decl){
    declist = decl;
}

void ProgramStm::typecheck(){
    DeclarationList* decl = new DeclarationList(declist->head, declist->next);

    while(decl != nullptr){
        decl->head->typecheck();
        decl = decl->next;
    }
}

void ProgramStm::interp(){
    DeclarationList* decl = new DeclarationList(declist->head, declist->next);

    while(decl != nullptr){
        decl->head->interp();
        decl = decl->next;
    }
}


PrintStm::PrintStm(ExpList* expl){
    explist = expl;
}

void PrintStm::typecheck(){
    ExpList* expl = new ExpList(explist->head, explist->next);

    int i = 0;
    while(expl != nullptr){
        i = expl->head->typecheck();
        expl = expl->next;
    }
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
}

Function_DeclarationStm::Function_DeclarationStm(){}


void Function_DeclarationStm::typecheck(){

    symboltypehandler.pushSymbolTypeTable(SymbolTypeTable());

    std::vector<int> paramTypes;

    if(signature->params != nullptr){
       ParamList* list = new ParamList(signature->params->head, signature->params->next);


       while(list != nullptr){
            symboltypehandler.addSymbolType(list->head->name, list->head->type);
            paramTypes.push_back(list->head->type);
            list = list->next;
       }
    }


    //Copy for evaluation
    int functionType = signature->type;
    returnhandler.returnscopetype = functionType;
    bool isReturnInFunctionScope = false;

    //BEPERKING: KAN NIET ZIEN OF ELK CODEPAD EEN RETURN GEEFT

    if(stmlist != nullptr){
  
        StmList* stml = new StmList(stmlist->head, stmlist->next);
         
        while(stml != nullptr){

            if(dynamic_cast<ReturnStm*>(stml->head) != nullptr){
                returnhandler.returnEncountered = true;
                ReturnStm* returnstm = dynamic_cast<ReturnStm*>(stml->head);

                
                if(returnstm->expr != nullptr && functionType == -1){
                    std::cout << "Error: no return value in void defined function allowed" << std::endl;
                }

                if(returnstm->expr == nullptr && functionType != -1){
                    std::cout << "Error: function needs a return type" << std::endl;
                }
                
                int returntype = -1;
                
                if(returnstm->expr != nullptr){
                        returntype =  returnstm->expr->typecheck();
                } 

                std::cout << "RETURNTYPE: " << returntype << std::endl;
                    //returnstm.interp();
                

                if(functionType == BOOL){
                    if(returntype != BOOL){          
                        std::cout << "wrong return type error" << std::endl;
                    }
                }
                else if(functionType == INT){
                    if(returntype != INT){
                        std::cout << "wrong return type error" << std::endl;
                    }
                }

                if(stml->next != nullptr){
                    std::cout << "Unreachable code error" << std::endl;
                }

            }
            else{

                stml->head->typecheck();
            }

            stml = stml->next;

        }

        if(functionType != -1 && !returnhandler.returnEncountered){
            std::cout << "Error: function needs a return type" << std::endl;
        }
    }
    else{
        if(functionType != -1){
             std::cout << "Error: function needs a return type" << std::endl;
        }
    }


    FunctionType* ftype = new FunctionType();
    ftype->type = functionType;
    ftype->next = nullptr;
    ftype->name = identifier;
    ftype->paramtypes = paramTypes;
    functiontypehandler.addFunctionType(ftype);

    returnhandler.returnscopetype = -1;
    symboltypehandler.popSymbolTypeTable();
   
}

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

//"COMPILE TIME" TYPE AND ERROR CHECKING
void DeclarationStm::typecheck(){
    
    //Copy objects for evaluation
    IdList* idl = new IdList(idlist->head, idlist->next);

    ExpList* expl = new ExpList(explist->head, explist->next);


    //DO THIS IN CONSTRUCTOR
    std::vector<char*> declared_ids;
    if(expl == nullptr){
        //Default assignment of value, but only if a type is specified
        while(idl != nullptr){
            
            if(containsValue(declared_ids, idl->head)){
                
                std::cout << idl->head << std::endl;

                for(auto&& i: declared_ids){
                    std::cout << i << " ";
                }
                std::cout << std::endl;

                std::cout << "Error: duplicate indentifier in declaration" << std::endl;
                return;
            }

            symboltypehandler.addSymbolType(idl->head, declaredType);
        }
    }
    else{
        while(idl != nullptr){
            
            if(containsValue(declared_ids, idl->head)){
                std::cout << "Error: duplicate indentifier in declaration" << std::endl;
            }
            declared_ids.push_back(idl->head);


            //TODO: fix too many arguments
            if((idl->next != nullptr && expl->next == nullptr) ){
                std::cout << "Error: argument count not matching" << std::endl;
            }

            if(idl->next == nullptr && expl->next != nullptr){
                std::cout << "Error: argument count not matching" << std::endl;
            }
            
            int returnType =  expl->head->typecheck();
             
            

            if(declaredType == INT){
                if(returnType != INT){
                    std::cout << "Type error: can't assign non-int value to int variable" << std::endl;
                }

            }
            else if(declaredType == BOOL){

                if(returnType != BOOL){
                    std::cout << "Type error: can't assign non-bool value to bool variable" << std::endl;
                }
            }
            else if(declaredType == -1){
                if(returnType == -1){
                    std::cout << "Type error: can't assign type void to variables" << std::endl;
                }
                else{
                    declaredType = returnType;
                }
            }

           

            symboltypehandler.addSymbolType(idl->head, declaredType);


            idl = idl->next;
            expl = expl->next;             
        }
    }

}

//INCLUDES "RUNTIME" ERROR CHECKING
void DeclarationStm::interp(){
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

void AssignStm::typecheck(){

    //Copy objects for evaluation
    IdList* idl = new IdList(idlist->head, idlist->next);

    ExpList* expl = new ExpList(explist->head, explist->next);

    std::vector<char*> assigned_ids;

    while(idl != nullptr){

        if(containsValue(assigned_ids, idl->head)){
            std::cout << "Duplicate identifier in assign statement";
            return;
        }
        
        assigned_ids.push_back(idl->head);

        if(idl->next != nullptr && expl->next == nullptr){
            std::cout << "Error: argument count not matching" << std::endl;
        }

        if(idl->next == nullptr && expl->next != nullptr){
            std::cout << "Error: argument count not matching" << std::endl;
        }
        
        int lookupReturnType = symboltypehandler.lookupSymbolType(idlist->head);
        int typecheckReturnType = expl->head->typecheck();
        
        std::cout << "Lookup return type: " << lookupReturnType << std::endl;
        std::cout << "typecheckReturnType: " << typecheckReturnType << std::endl;
        if(lookupReturnType != typecheckReturnType){
            std::cout << "Argument type not matching variable" << std::endl;
        }

        idl = idl->next;
        expl = expl->next;
    }
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
    expr = e;
}


BlockStm::BlockStm(){

}

BlockStm::BlockStm(StmList* stl){
    stmlist = stl;
}

void BlockStm::typecheck(){

    if(stmlist == nullptr) return;

    StmList* list = new StmList(stmlist->head, stmlist->next);
   
    symboltypehandler.pushSymbolTypeTable(SymbolTypeTable());
    while(list != nullptr){
                                        
        if(dynamic_cast<ReturnStm*>(list->head) != nullptr){


                ReturnStm* returnstm = static_cast<ReturnStm*>(list->head);

                returnhandler.returnEncountered = true;

                int returntype = returnstm->expr->typecheck();

                if(returntype != returnhandler.returnscopetype){
                    std::cout << "Wrong return type in function" << std::endl;
                }

                if(list->next != nullptr){
                    std::cout << "Unreachable code error " << std::endl;
                }
        }
        else{
            //returnsm encounter
            list->head->typecheck();
        }

        list = list->next;      
    }

    symboltypehandler.popSymbolTypeTable();
}

void BlockStm::interp(){
    if(stmlist == nullptr) return;

    StmList* list = new StmList(stmlist->head, stmlist->next);    


    symbolhandler.pushSymbolTable(SymbolTable());
    while(list != nullptr){
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

void VoidFunctionStm::typecheck(){

  FunctionType functiontype = functiontypehandler.lookupFunctionType(identifier);
    if(arguments != nullptr && functiontype.paramtypes.size() != 0){
        ExpList* args = new ExpList(arguments->head, arguments->next);

        int i = 0;
        while(args != nullptr){
            if(functiontype.paramtypes[i] != args->head->typecheck()){
                std::cout << "Error: wrong argument type" << std::endl;
                return;
            }

            if(args->next == nullptr && i != functiontype.paramtypes.size() -1){
                std::cout << "Error: not enough arguments" << std::endl;
                return;
            }
            else if (args->next != nullptr && i == functiontype.paramtypes.size() -1){
                std::cout << "Error: too many arguments" << std::endl;
                return;
            }

            args = args->next;      
            i++;
        }
    }
    else if(arguments != nullptr && functiontype.paramtypes.size() == 0){
        std::cout << "Error: too many arguments" << std::endl;
    }
    else if(arguments == nullptr && functiontype.paramtypes.size() != 0){
        std::cout << "Error: not enough arguments" << std::endl;
    }
};

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
            stmlist->head->interp(); 
            // Execute the nested block
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
        std::cout << "Error: expected a return value" << std::endl;
    }

}


IncDecStm::IncDecStm(){}

IncDecStm::IncDecStm(int ac, char* id){
    action = ac;
    identifier = id;
}

void IncDecStm::typecheck(){
    if(symboltypehandler.lookupSymbolType(identifier) != INT) std::cout << "No non-int type allowed in incdec stm" << std::endl;
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

void If_stm::typecheck(){
    if(exp->typecheck() != BOOL) std::cout << "Boolean type expected in if-clause" << std::endl;
    blockStm->typecheck();
}

void If_stm::interp(){

    ReturnValue returnValue = exp->interp();
    
    // std::cout << *returnValue.boolValue << " " << returnValue.intValue << " ";



    if(returnValue.boolValue != nullptr){

        if(*returnValue.boolValue == true){   
            std::cout << "if condition is true" << std::endl;         
            blockStm->interp();
        }
        else{
            std::cout << "if condition is false" << std::endl;
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

void For_stm::typecheck(){
    if(exp->typecheck() != BOOL) std::cout << "Boolean type expected in for-clause" << std::endl;
    blockStm->typecheck();
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


void ArithmeticAssignOpStm::typecheck(){
    if(right->typecheck() != INT) std::cout << "Can't assign non-int value to integer value " << std::endl;
}

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


PackageStm::PackageStm(){

}

PackageStm::PackageStm(char* id){
    packageid = id;
}

void PackageStm::typecheck(){

}

void PackageStm::interp(){

}

IntlitExp::IntlitExp(){

}

IntlitExp::IntlitExp(int i){
    intlit = i;
}

int IntlitExp::typecheck(){
    return INT;
}

ReturnValue IntlitExp::interp(){
    return ReturnValue(intlit);
}


BoollitExp::BoollitExp(){

}

BoollitExp::BoollitExp(bool b){
    boollit = b;
}

int BoollitExp::typecheck(){
    return BOOL;
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

int ArithmeticOpExp::typecheck(){
    int type_right = right->typecheck();
    int type_left = left->typecheck();

    if(type_right != INT && type_left != INT){
        std::cout << "No non-integer values allowed in expression" << std::endl;
    }
    return INT;
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

int BooleanOpExp::typecheck(){
    int type_right = right->typecheck();
    int type_left = left->typecheck();

    if(type_right != BOOL && type_left != BOOL){
        std::cout << "No non-bool values allowed in expression" << std::endl;
    }
    return BOOL;
}

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

int BooleanArithmeticOpExp::typecheck(){
    int type_right = right->typecheck();
    int type_left = left->typecheck();

    if(type_right != INT && type_left != INT){
        std::cout << "No non-bool values allowed in expression" << std::endl;
    }
    return BOOL;
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

int NotExp::typecheck(){
    if(expr->typecheck() != BOOL) std::cout << "No non-boolean expression allowed in not expression" << std::endl;
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

int FunctionExp::typecheck(){

    
    FunctionType functiontype = functiontypehandler.lookupFunctionType(identifier);
    if(arguments != nullptr && functiontype.paramtypes.size() != 0){
        ExpList* args = new ExpList(arguments->head, arguments->next);

        int i = 0;
        while(args != nullptr){
            std::cout << "paramtype:" << functiontype.paramtypes[i] << std::endl;
            std::cout << "argtype:" << args->head->typecheck() << std::endl;
            if(functiontype.paramtypes[i] != args->head->typecheck()){
                std::cout << "Error: wrong argument type" << std::endl;
                return 0;
            }

            if(args->next == nullptr && i != functiontype.paramtypes.size() -1){
                std::cout << "Error: not enough arguments" << std::endl;
                return 0 ;
            }
            else if (args->next != nullptr && i == functiontype.paramtypes.size() -1){
                std::cout << "Error: too many arguments" << std::endl; 
                return 0;
            }

            args = args->next;      
            i++;
        }
    }
    else if(arguments != nullptr && functiontype.paramtypes.size() == 0){
        std::cout << "Error: too many arguments" << std::endl;
    }
    else if(arguments == nullptr && functiontype.paramtypes.size() != 0){
        std::cout << "Error: not enough arguments" << std::endl;
    }

    return functiontypehandler.lookupFunctionType(identifier).type;
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

int IdExp::typecheck(){
   int type = symboltypehandler.lookupSymbolType(identifier);
   return type;
}

ReturnValue IdExp::interp(){
    std::cout << "INTERPRETING ID EXP " << identifier << std::endl;

    return symbolhandler.lookupSymbol(identifier);
}


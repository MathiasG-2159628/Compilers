#include <stdio.h>
#include "symboltable.hpp"
#include "tokens.h"
#include "yyfunctions.h"
#include <vector>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <string>
#include "ReturnValue.hPP"

//TODO: error handling
//TODO: for block statement: push and pop new symbol table on the stack




struct Stm_ {
    virtual void interp() { return; };
};

struct Exp_ {
    virtual ReturnValue interp(){ return; };
};

typedef Stm_* Stm;

typedef Exp_* Exp;


bool returnEncountered = false;
Exp returnExp = nullptr;


//Lists
struct ExpList {
    Exp head;
    ExpList* next;

    ExpList(Exp h, ExpList* t) {
        head = h;
        next = t;
    };

    ExpList(){

    };
};

struct IdList{
    std::string head;
    IdList* next;

    IdList(std::string h, IdList* t) {
        head = h;
        next = t;
    };

    IdList(){

    };

};

struct StmList{
    Stm head;
    StmList* next;

    StmList(Stm h, StmList* s){
        head = h;
        next = s;
    }

    StmList(){

    };
};


struct ParamList{
    Param_declaration head;
    ParamList* next;

    ParamList(Param_declaration h, ParamList* n){
        head = h;
        next = n;
    }

    ParamList(){

    };
};

//Params

struct Param_declaration{
    std::string name;
    int type;

    Param_declaration(std::string n, int t){
        name = n;
        type = t;
    }

    Param_declaration(){

    };
};
struct Function_signature{
    ParamList params;
    int type;

    Function_signature(ParamList p, int t){
        params = p;
        type = t;
    }

    Function_signature(){

    };
};


//Statements

struct PrintStm : public Stm_{
    ExpList* explist;

    PrintStm(ExpList* expl){
        explist = expl;
    }

    PrintStm(){

    }

    void interp() override{

        
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
};

struct Function_DeclarationStm : public Stm_{
    Function_signature signature;
    StmList stmlist;
    std::string identifier;

    Function_DeclarationStm(Function_signature sig, StmList stml, std::string id){
        signature = sig;
        stmlist = stml;
        identifier = id;
    }

    Function_DeclarationStm();

    void interp() override{
        int returnType = signature.type;
        ParamList* paramlist = &signature.params;

        std::vector<int> paramtypes;
        std::vector<std::string> paramnames;

        while(paramlist != nullptr){
            paramtypes.push_back(paramlist->head.type);
            paramnames.push_back(paramlist->head.name);

            paramlist = paramlist->next;
        }

        Function function(identifier, paramnames, paramtypes, returnType, stmlist);
        
        //Add function to table
        addFunction(identifier, &function);
    }
};

struct DeclarationStm : public Stm_{
    int declaredType; 
    IdList* idlist;
    ExpList* explist;

    DeclarationStm(int dcltype, IdList* idl, ExpList* expl){
        declaredType = dcltype;
        idlist = idl;
        explist = expl;
    }

    DeclarationStm(){};

    void interp() override{
        
        std::vector<std::string> declared_ids;

        if(explist == nullptr){
            //Default assignment of value, but only if a type is specified
            while(idlist != nullptr){
                
                if(containsValue(declared_ids, idlist->head)){
                    //error
                }
                declared_ids.push_back(idlist->head);


                if(declaredType == INT){
                    addSymbol(idlist->head, 0);
                }
                else if(declaredType == BOOL){
                    addSymbol(idlist->head, true);
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
                        addSymbol(idlist->head, returnValue.intValue);
                    }
                    else{
                        //throw error
                    }
                }
                else if(declaredType == BOOL){
                    if(returnValue.boolValue == nullptr){
                        //throw error
                    }else{
                        addSymbol(idlist->head, returnValue.boolValue);
                    }
                }
                else if(declaredType == -1){
                    if(returnValue.boolValue == nullptr){
                        addSymbol(idlist->head, returnValue.intValue);
                    }else{
                        addSymbol(idlist->head, returnValue.boolValue);
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
};

struct AssignStm : public Stm_
{
    IdList* idlist;
    ExpList* explist;
    AssignStm(IdList* id, ExpList* e) {
        idlist = id;
        explist = e;
    };

    AssignStm();

    void interp() {
       
        std::vector<std::string> assigned_ids;

        while(idlist != nullptr){

            if(containsValue(assigned_ids, idlist->head)){
                //error
            }
            
            assigned_ids.push_back(idlist->head);

            if((idlist != nullptr && explist == nullptr) || (idlist == nullptr && explist != nullptr) ){
                //throw error
            }
            
            ReturnValue lookupReturn = lookupSymbol(idlist->head);
            ReturnValue interpReturn = explist->head->interp();

            if((lookupReturn.boolValue == nullptr && interpReturn.intValue != nullptr) || (lookupReturn.intValue == nullptr && interpReturn.boolValue != nullptr)){
                //type error
            }
            else{
                updateSymbol(idlist->head, explist->head->interp());
            }

            idlist = idlist->next;
            explist = explist->next;
        }
  
    };
};

struct ReturnStm : public Stm_
{
    Exp expr;

    ReturnStm(Exp e){
        expr = e;
    }

    virtual void interp() override{
        
    }
};

struct BlockStm : public Stm_{
    
    StmList* stmlist;

    BlockStm(StmList *stl){
        stmlist = stl;
    }

    BlockStm();

    virtual void interp() override{
       
        pushSymbolTable(SymbolTable());
        while(stmlist != nullptr){

            if(std::is_same<decltype(stmlist->head), ReturnStm>::value){
                    ReturnStm* returnstm = static_cast<ReturnStm*>(stmlist->head);

                    returnEncountered = true;
                    returnExp = returnstm->expr;
                    //returnstm.interp();

                    if(stmlist->next != nullptr){
                        //Unreachable code error
                    }

                    return;
            }          
        }
        popSymbolTable();
    }
};

struct VoidFunctionStm : public Stm_{
    ExpList arguments;
    std::string identifier;

    VoidFunctionStm(ExpList args, std::string id){
        arguments = args;
        identifier = id;
    }

    virtual void interp() override{
        //Call the function from the function table 
        Function function = lookupFunction(identifier);
        int returntype = function.functionType;
        StmList* stmlist = &function.stmlist;

        //New scope definition
        pushSymbolTable(SymbolTable());

        //Pushing the arguments onto the symbol table of the new scope
        ExpList* args = &arguments;
        std::vector<std::string> paramNames = function.paramNames;
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
                        addSymbol(paramNames[i], returnValue);
                    }
                }
                else if(returnValue.boolValue != nullptr){
                    if(paramTypes[i] != BOOL){                      
                        //wrong type
                    }
                    else{
                        addSymbol(paramNames[i], returnValue);
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
                if (returnEncountered) {
                    
                    ReturnValue returnValue = returnExp->interp();

                    if(returnExp != nullptr && returntype == -1){
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

                    returnEncountered = false;

                    // Bubble up the return statement
                    return;
                }
            }

        }
              
    }

};


struct IncDecStm : public Stm_{
    int action;
    std::string identifier;

    IncDecStm(int ac, std::string id){
        action = ac;
        identifier = id;
    }

    virtual void interp() override{

        ReturnValue returnValue =  lookupSymbol(identifier);

        if(returnValue.intValue != nullptr){
            
            if(action == DEC){
                *returnValue.intValue--;
            }
            else if(action == INC){
                *returnValue.intValue++;
            }

            updateSymbol(identifier, returnValue);
        }
        else{
            //Throw type error because it can't be bool
        }

    }

};

struct If_stm : public Stm_{
    Exp exp;
    BlockStm blockStm;

    If_stm(Exp ex, BlockStm bstm){
        exp = ex;
        blockStm = bstm;
    }

    virtual void interp() override{

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
};

struct For_stm : public Stm_{
    Exp exp;
    BlockStm blockStm;

    For_stm(Exp ex, BlockStm bstm){
        exp = ex;
        blockStm = bstm;
    }

    virtual void interp() override{

        ReturnValue returnValue = exp->interp();

        if(returnValue.boolValue != nullptr){
            while(returnValue.boolValue == false){
                blockStm.interp();
                returnValue = exp->interp();
            }
        }
        else{
        //Wrong type error
        }
    }
};


//Expressions
struct IntlitExp : public Exp_
{
    int intlit;

    IntlitExp(int i) {
        intlit = i;
    };

    ~IntlitExp();

  
    virtual ReturnValue interp() override{
        return ReturnValue(intlit);
    }
};

struct BoollitExp : public Exp_
{
    bool boollit;

    BoollitExp(bool b){
        boollit = b;
    }

    virtual ReturnValue interp() override{
        return ReturnValue(b)
    }
};

struct ArithmeticOpExp : public Exp_
{
    Exp left, right;
    int oper;

    ArithmeticOpExp(Exp l, int op, Exp r) {
        left = l;
        right = r;
        oper = op;
    };

    ~ArithmeticOpExp();

    virtual ReturnValue interp() override{
        
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
};
struct ArithmeticAssignOpExp : public Exp_{

    std::string left;
    Exp right;
    int oper;

     ArithmeticAssignOpExp(std::string l, int op, Exp r) {
        left = l;
        right = r;
        oper = op;
    };

    virtual ReturnValue interp() override{

        ReturnValue returnValue = right->interp();

        if(returnValue.intValue != nullptr){
            int symbolVal = *lookupSymbol(left).intValue;

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

            updateSymbol(left, ReturnValue(symbolVal));
        }
        else{
            //Type error
        }   
    }

};

struct BooleanOpExp : public Exp_{

    Exp left;
    Exp right;
    int oper;

    BooleanOpExp(Exp l, int op, Exp r) {
        left = l;
        right = r;
        oper = op;
    };

    virtual ReturnValue interp() override{

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
};
struct BooleanArithmeticOpExp : public Exp_{

    Exp left;
    Exp right;
    int oper;

    BooleanArithmeticOpExp(Exp l, int op, Exp r) {
        left = l;
        right = r;
        oper = op;
    };

    virtual ReturnValue interp() override{

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

};
struct NotExp : public Exp_{
    Exp expr;
    
    NotExp(Exp ex){
        expr = ex;
    }

    virtual ReturnValue interp() override{

        if(expr->interp().boolValue == nullptr){
            //type error
        }

        return !(*expr->interp().boolValue);
    }
};

struct FunctionExp : public Exp_{


    ExpList arguments;
    std::string identifier;


    FunctionExp(ExpList args, std::string id){
        arguments = args;
        identifier = id;
    }


    virtual ReturnValue interp() override{

        //Call the function from the function table 
        Function function = lookupFunction(identifier);
        int returntype = function.functionType;
        StmList* stmlist = &function.stmlist;

        //New scope definition
        pushSymbolTable(SymbolTable());

        //Pushing the arguments onto the symbol table of the new scope
        ExpList* args = &arguments;
        std::vector<std::string> paramNames = function.paramNames;
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
                
                addSymbol(paramNames[i], returnValue);
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
                    if (returnEncountered) {
                        
                        
                        if(returnExp != nullptr && returntype == -1){
                            //no return in void function allowed
                        }

                        ReturnValue returnValue = returnExp->interp();

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

                        returnEncountered = false;
                        // Bubble up the return statement
                        return returnValue;
                    }
                }

            }
        }       
    }
};


//Methods
bool containsValue(const std::vector<std::string> vec, std::string value) {
    for (const auto& element : vec) {
        if (element == value) {
            return true;
        }
    }
    return false;
}


#include <stdio.h>
#include "symboltable.h"
#include "tokens.h"
#include "yyfunctions.h"
#include <vector>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <string>

//TODO: error handling
//TODO: for block statement: push and pop new symbol table on the stack



typedef Stm_* Stm;

typedef Exp_<void>* Exp;

struct Stm_ {
    virtual void interp() { return; };
};

template <typename T>
struct Exp_ {
    virtual T interp(){ return; };
};

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

    StmList(){};
};


struct ParamList{
    Param_declaration head;
    ParamList* next;

    ParamList(Param_declaration h, ParamList* n){
        head = h;
        next = n;
    }

    ParamList();
};

//Params

struct Param_declaration{
    std::string name;
    int type;

    Param_declaration(std::string n, int t){
        name = n;
        type = t;
    }

    Param_declaration();
};
struct Function_signature{
    ParamList params;
    int type;

    Function_signature(ParamList p, int t){
        params = p;
        type = t;
    }

    Function_signature();
};


//Statements

struct PrintStm : public Stm_{
    ExpList* explist;

    PrintStm(ExpList* expl){
        explist = expl;
    }

    void interp() override{
        while(explist != nullptr){
            std::cout << std::to_string(explist->head->interp()) << " ";
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

                //Since a declaration without a specified type is possible it needs runtime typechecking.
                if(declaredType == INT){
                    if(std::is_same<decltype(explist->head->interp()), int>::value){
                        addSymbol(idlist->head, explist->head->interp());
                    }
                    else{
                        //throw error
                    }
                }
                else if(declaredType == BOOL){
                    if(std::is_same<decltype(explist->head->interp()), bool>::value){
                        addSymbol(idlist->head, explist->head->interp());
                    }else{
                        //throw error
                    }
                }
                else if(declaredType == -1){
                    addSymbol(idlist->head, explist->head->interp());
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

            updateSymbol(idlist->head, explist->head->interp());

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
                    ReturnStm returnstm = (ReturnStm) stmlist->head;

                    returnEncountered = true;
                    returnExp = returnstm.expr;
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

                //Couldn't use typeinfo due to bogus inclusion error
                //So I have to do it the stupid way
                if(std::is_same<decltype(args->head->interp()), int>::value){
                    if(paramTypes[i] != INT){
                        //wrong type
                    }
                }
                else if(std::is_same<decltype(args->head->interp()), bool>::value){
                    if(paramTypes[i] != BOOL){
                        //wrong type

                    }
                }
                
                addSymbol(paramNames[i], args->head->interp());
                i++;
                args = args->next;
            }
        }

        //Executing the function

        if(stmlist != nullptr){
            while(stmlist != nullptr){
               
                if(std::is_same<decltype(stmlist->head), ReturnStm>::value){
                    ReturnStm returnstm = (ReturnStm) stmlist->head;

                    //returnstm.interp();

                    if(returnstm.expr != nullptr && returntype == -1){
                        //no return in void function allowed
                    }

                    if(std::is_same<decltype(returnstm.expr->interp()), bool>::value){
                        if(returntype != BOOL){
                            //wrong return type error
                        }
                    }
                    else if(std::is_same<decltype(returnstm.expr->interp()), int>::value){
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
                        

                        if(returnExp != nullptr && returntype == -1){
                            //no return in void function allowed
                        }

                        if(std::is_same<decltype(returnExp->interp()), bool>::value){
                            if(returntype != BOOL){
                                //wrong return type error
                            }
                        }
                        else if(std::is_same<decltype(returnExp->interp()), int>::value){
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
    }

};

template <typename T>

struct IncDecStm : public Stm_{
    int action;
    std::string identifier;

    IncDecStm(int ac, std::string id){
        action = ac;
        identifier = id;
    }

    virtual void interp() override{

        T value =  lookupSymbol(identifier);

        if(std::is_same<decltype(value), int>::value){
            int castedValue = (int) value;
            
            if(action == DEC){
                castedValue--;
            }
            else if(action == INC){
                castedValue++;
            }

            updateSymbol(identifier, castedValue);
        }
        else{
            //Throw type error
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
         if(std::is_same<decltype(exp->interp()), bool>::value){
            if(exp->interp()){
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
         if(std::is_same<decltype(exp->interp()), bool>::value){
            while(exp->interp()){
                blockStm.interp();
            }
         }
         else{
            //Wrong type error
         }
    }
};


//Expressions

template <typename T>
struct IdExp : public Exp_
{
    std::string id;

    IdExp(std::string i) {
        id = i;
    };

    ~IdExp();

    virtual T interp() override {        
        return lookupSymbol(id);
    }
};

struct IntlitExp : public Exp_<int>
{
    int integer;

    IntlitExp(int n) {
        integer = n;
    };

    ~IntlitExp();

  
    virtual int interp() override{
        return integer;
    }
};
struct BoollitExp : public Exp_<bool>
{
    bool boolean;

    BoollitExp(bool b){
        boolean = b;
    }

    virtual bool interp() override{
        return boolean;
    }
};
struct ArithmeticOpExp : public Exp_<int>
{
    Exp left, right;
    int oper;

    ArithmeticOpExp(Exp l, int op, Exp r) {
        left = l;
        right = r;
        oper = op;
    };

    ~ArithmeticOpExp();

    virtual int interp() override{
        
        float value_return;
        int result_left = left->interp();
        int result_right = right->interp();

        if(oper == PLUS) {
            value_return = result_left + result_right; 
        }
        else if(oper == MIN){
            value_return = result_left - result_right;
        }
        else if (oper == MUL) {
            value_return = result_left * result_right;
        }
        else if (oper == DIV){
            value_return = result_left / result_right;
        }

        return value_return;
    }
};
struct ArithmeticAssignOpExp : public Exp_<void>{

    std::string left;
    Exp right;
    int oper;

     ArithmeticAssignOpExp(std::string l, int op, Exp r) {
        left = l;
        right = r;
        oper = op;
    };

    virtual void interp() override{

        int result_right = right->interp();

        int symbolVal = lookupSymbol<int>(left);

        if (oper == PLUSASSIGN){
            symbolVal += result_right;
        }
        else if (oper == MINASSIGN){
            symbolVal -= result_right;
        }
        else if (oper == MULASSIGN){
            symbolVal *= result_right;
        }
        else if (oper == DIVASSIGN){
            symbolVal /= result_right;
        }

        updateSymbol(left, symbolVal);    
    }

};
struct BooleanOpExp : public Exp_<bool>{

    Exp left;
    Exp right;
    int oper;

    BooleanOpExp(Exp l, int op, Exp r) {
        left = l;
        right = r;
        oper = op;
    };

    virtual bool interp() override{

        //Check if left and right types are equal
        //if not throw yyerror

        if(oper == NE){
            return left->interp() != right->interp();           
        }
        else if(oper == EQ){
            return left->interp() == right->interp();
        }
        else if(oper == AND){
            return left->interp() && right->interp();
        }
        else if(oper == OR){
            return left->interp() || right->interp();
        }

        return false;
    }
};
struct BooleanArithmeticOpExp : public Exp_<bool>{

    Exp left;
    Exp right;
    int oper;

    BooleanArithmeticOpExp(Exp l, int op, Exp r) {
        left = l;
        right = r;
        oper = op;
    };

    virtual bool interp() override{

        //Check if left and right types are both numeric
        //if not throw yyerror

        if(oper == GT){
            return left->interp() > right->interp();           
        }
        else if(oper == LT){
            return left->interp() < right->interp();
        }
        else if(oper == GE){
            return left->interp() >= right->interp();
        }
        else if(oper == GT){
            return left->interp() <= right->interp();
        }

        return false;
    }

};
struct NotExp : public Exp_<bool>{
    Exp expr;
    
    NotExp(Exp ex){
        expr = ex;
    }

    virtual bool interp() override{

        if(!(std::is_same<decltype(expr->interp()), int>::value)){
            //type error
        }

        return !(expr->interp());
    }
};

template <typename T>
struct FunctionExp : public Exp_<T>{


    ExpList arguments;
    std::string identifier;


    FunctionExp(Explist args, std::string id){
        arguments = args;
        identifier = id;
    }


     virtual T interp() override{

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
                if(i == paramNames.size() && args->next != nullptr){
                    //Too many arguments
                }
                else if(i != paramNames.size() && args->next == nullptr){
                    //Not enough arguments
                }

                //Couldn't use typeinfo due to bogus inclusion error
                //So I have to do it the stupid way
                if(std::is_same<decltype(args->head->interp()), int>::value){
                    if(paramTypes[i] != INT){
                        //wrong type
                    }
                }
                else if(std::is_same<decltype(args->head->interp()), bool>::value){
                    if(paramTypes[i] != BOOL){
                        //wrong type

                    }
                }
                
                addSymbol(paramNames[i], args->head->interp());
                i++;
                args = args->next;
            }
        }

        //Executing the function

        if(stmlist != nullptr){
            while(stmlist != nullptr){
               
                if(std::is_same<decltype(stmlist->head), ReturnStm>::value){
                    ReturnStm returnstm = (ReturnStm) stmlist->head;

                    //returnstm.interp();

                    if(std::is_same<decltype(returnstm.expr->interp()), bool>::value){
                        if(returntype != BOOL){
                            //wrong return type error
                        }
                    }
                    else if(std::is_same<decltype(returnstm.expr->interp()), int>::value){
                        if(returntype != INT){
                            //wrong return type error
                        }
                    }

                    if(stmlist->next != nullptr){
                        //Unreachable code error
                    }

                    return returnstm.expr->interp();
                }
                else {
                    stmlist->head->interp(); // Execute the nested block
                    if (returnEncountered) {
                        

                        if(returnExp != nullptr && returntype == -1){
                            //no return in void function allowed
                        }

                        if(std::is_same<decltype(returnExp->interp()), bool>::value){
                            if(returntype != BOOL){
                                //wrong return type error
                            }
                        }
                        else if(std::is_same<decltype(returnExp->interp()), int>::value){
                            if(returntype != INT){
                                //wrong return type error
                            }
                        }

                        returnEncountered = false;
                        // Bubble up the return statement
                        return returnstm.expr->interp();
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

//Function table

struct Function{

    //call on this data whenever a function is called
    Function* next;
    std::string name;
    std::vector<std::string> paramNames;
    std::vector<int> paramTypes;
    int functionType;
    StmList stmlist;

    Function(std::string n, std::vector<std::string> names, std::vector<int> types, int functype, StmList slist){
        name = n;
        paramNames = names;
        paramTypes = types;
        functionType = functype;
        stmlist = slist;
    }
    
};

struct FunctionTable {
    Function* head; 
};

FunctionTable* functionTable;

Function lookupFunction(std::string name) {
    Function* current = functionTable->head;
    while (current != nullptr) {
        if (strcmp(current->name, name) == 0) {
            return *current;
        }
        current = current->next;
    }
    

    printf("Function '%s' is not present in the function table.\n", name);

    return;
}

void addFunction(std::string name, Function* newFunction) {

    newFunction->next = functionTable->head;
    functionTable->head = newFunction;
}
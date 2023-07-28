#include <stdio.h>
#include "symboltable.h"
#include "tokens.h"
#include "yyfunctions.h"
#include <vector>
#include <type_traits>

//TODO: error handling


typedef Stm_* Stm;

typedef Exp_<void>* Exp;

struct Stm_ {
    virtual void interp() { return; };
};

template <typename T>
struct Exp_ {
    virtual T interp(){ return; };
};





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
    char* head;
    IdList* next;

    IdList(char* h, IdList* t) {
        head = h;
        next = t;
    };

    IdList(){

    };

};

bool containsValue(const std::vector<char*> vec, char* value) {
    for (const auto& element : vec) {
        if (element == value) {
            return true;
        }
    }
    return false;
}

//Statements

struct DeclarationStm : public Stm_{
    int declaredType; 
    IdList* idlist;
    ExpList* explist;

    DeclarationStm(int dcltype, IdList* idl, ExpList* expl){
        declaredType = dcltype;
        idlist = idl;
        explist = expl;
    }


    void interp() override{
        
        std::vector<char*> declared_ids;

        if(explist == nullptr){
            //Default assignment of value, but only if a type is specified
            while(idlist->next != nullptr){
                
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
             while(idlist->next != nullptr){
                
                
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

template <typename E>
struct AssignStm : public Stm_
{
    IdList* idlist;
    ExpList* explist;
    AssignStm(char* i, Exp e) {
        id = i;
        exp = e;
    };
    ~AssignStm();

    void interp() {
       
        std::vector<char*> assigned_ids;

        while(idlist.next != nullptr){

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

struct CompoundStm : public Stm_
{
    Stm stm1, stm2;
    CompoundStm(Stm s1, Stm s2) {
        stm1 = s1;
        stm2 = s2;
    };
    ~CompoundStm();


    virtual void interp() {
        stm1->interp();
        stm2->interp();
    };
};

//Expressions

template <typename T>
struct IdExp : public Exp_
{
    char* id;

    IdExp(char* i) {
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

    char* left;
    Exp right;
    int oper;

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

    //Check if expr result is of type bool

    virtual bool interp() override{
        return !(expr->interp());
    }
};
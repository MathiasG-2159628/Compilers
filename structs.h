#include <stdio.h>
#include "symboltable.h"
#include "tokens.h"
#include "yyfunctions.h"

//TODO: error handling


typedef Stm_* Stm;

typedef Exp_<void>* Exp;

typedef ExpList_* ExpList;

struct Stm_ {
    virtual void interp() { return; };
};

template <typename T>
struct Exp_ {
    virtual T interp(){ return; };
};

struct ExpList_ {
    virtual void interp() { return; };
};

//Statements

template <typename T>
struct AssignStm : public Stm_
{
    char* id;
    Exp exp;
    AssignStm(char* i, Exp e) {
        id = i;
        exp = e;
    };
    ~AssignStm();

    void interp() {

        T value = exp->interp();
        addSymbol(id, value);
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

    }
}
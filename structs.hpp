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


extern bool returnEncountered = false;
extern Exp_ returnExpValue;


//Lists
struct ExpList {
    Exp head;
    ExpList* next;

    ExpList(Exp h, ExpList* t);

    ExpList();
};

struct IdList{
    std::string head;
    IdList* next;

    IdList(std::string h, IdList* t);

    IdList();

};

struct StmList{
    Stm head;
    StmList* next;

    StmList(Stm h, StmList* s);

    StmList();
};


struct ParamList{
    Param_declaration head;
    ParamList* next;

    ParamList(Param_declaration h, ParamList* n);

    ParamList();
};

//Params

struct Param_declaration{
    std::string name;
    int type;

    Param_declaration(std::string n, int t);

    Param_declaration(){

    };
};

struct Function_signature{
    ParamList params;
    int type;

    Function_signature(ParamList p, int t);

    Function_signature();
};


//Statements

struct PrintStm : public Stm_{
    ExpList* explist;

    PrintStm(ExpList* expl);

    PrintStm();

    void interp() override;
};

struct Function_DeclarationStm : public Stm_{
    Function_signature signature;
    StmList stmlist;
    std::string identifier;

    Function_DeclarationStm(Function_signature sig, StmList stml, std::string id);

    Function_DeclarationStm();

    void interp() override;
};

struct DeclarationStm : public Stm_{
    int declaredType; 
    IdList* idlist;
    ExpList* explist;

    DeclarationStm(int dcltype, IdList* idl, ExpList* expl);

    DeclarationStm(){};

    void interp() override;
};

struct AssignStm : public Stm_
{
    IdList* idlist;
    ExpList* explist;
    AssignStm(IdList* id, ExpList* e);

    AssignStm();

    void interp() override;
};

struct ReturnStm : public Stm_
{
    Exp expr;

    ReturnStm(Exp e);
};

struct BlockStm : public Stm_{
    
    StmList* stmlist;

    BlockStm(StmList *stl){
        stmlist = stl;
    }

    BlockStm();

    virtual void interp() override;
};

struct VoidFunctionStm : public Stm_{
    ExpList arguments;
    std::string identifier;

    VoidFunctionStm(ExpList args, std::string id);

    VoidFunctionStm();

    virtual void interp() override;

};


struct IncDecStm : public Stm_{
    int action;
    std::string identifier;

    IncDecStm();

    IncDecStm(int ac, std::string id);

    virtual void interp() override;

};

struct If_stm : public Stm_{
    Exp exp;
    BlockStm blockStm;

    If_stm(Exp ex, BlockStm bstm);

    If_stm();

    virtual void interp() override;
};

struct For_stm : public Stm_{
    Exp exp;
    BlockStm blockStm;

    For_stm(Exp ex, BlockStm bstm);

    For_stm();

    virtual void interp() override;
};


//Expressions
struct IntlitExp : public Exp_
{
    int intlit;

    IntlitExp(int i);

    IntlitExp();

    virtual ReturnValue interp() override;
};

struct BoollitExp : public Exp_
{
    bool boollit;

    BoollitExp(bool b);

    BoollitExp();

    virtual ReturnValue interp() override;
};

struct ArithmeticOpExp : public Exp_
{
    Exp left, right;
    int oper;

    ArithmeticOpExp(Exp l, int op, Exp r);

    ArithmeticOpExp();

    virtual ReturnValue interp() override;
};

struct ArithmeticAssignOpExp : public Exp_{

    std::string left;
    Exp right;
    int oper;

    ArithmeticAssignOpExp(std::string l, int op, Exp r);

    ArithmeticAssignOpExp();

    virtual ReturnValue interp() override;

};

struct BooleanOpExp : public Exp_{

    Exp left;
    Exp right;
    int oper;

    BooleanOpExp(Exp l, int op, Exp r);

    BooleanOpExp();

    virtual ReturnValue interp() override;
};

struct BooleanArithmeticOpExp : public Exp_{

    Exp left;
    Exp right;
    int oper;

    BooleanArithmeticOpExp(Exp l, int op, Exp r);

    BooleanArithmeticOpExp();

    virtual ReturnValue interp() override;

};

struct NotExp : public Exp_{
    Exp expr;
    
    NotExp(Exp ex);

    NotExp(){}

    virtual ReturnValue interp() override;
};

struct FunctionExp : public Exp_{


    ExpList arguments;
    std::string identifier;


    FunctionExp(ExpList args, std::string id);

    FunctionExp();


    virtual ReturnValue interp() override;
};





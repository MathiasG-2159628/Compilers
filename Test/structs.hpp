#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include "symboltable.hpp"
#include "yyfunctions.h"
#include <vector>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <string>
#include "ReturnValue.hpp"
#include <unordered_map>



//TODO: error handling
//TODO: for block statement: push and pop new symbol table on the stack

inline std::vector<int> returnTypesInStatement = std::vector<int>();


struct Stm_ {

    virtual void typecheck(){};
    virtual void interp() {};
};

struct Exp_ {

    Exp_();

    virtual int typecheck(){};
    virtual ReturnValue interp(){ return ReturnValue(); };
};

typedef Stm_* Stm;

typedef Exp_* Exp;

struct ReturnHandler{
    bool returnEncountered = false;
    Exp returnExp = nullptr;
    int returnscopetype = -1;

    ReturnHandler();
};

inline ReturnHandler returnhandler;


//Lists
struct ExpList {
    Exp head;
    ExpList* next;

    ExpList(Exp h, ExpList* t);

    ExpList();
};


struct IdList{
    char* head;
    IdList* next;

    IdList(char* h, IdList* t);

    IdList();

};

struct StmList{
    Stm head;
    StmList* next;

    StmList(Stm h, StmList* s);

    StmList();
};

//Params

struct Param_declaration{
    char* name;
    int type;

    Param_declaration(char* n, int t);

    Param_declaration();
};

struct ParamList{
    Param_declaration* head;
    ParamList* next;

    ParamList(Param_declaration* h, ParamList* n);

    ParamList();
};




struct Function_signature{
    ParamList* params;
    int type;

    Function_signature(ParamList* p, int t);

    Function_signature();
};


//Statements

struct PrintStm : public Stm_{
    ExpList* explist;

    PrintStm(ExpList* expl);

    PrintStm();

    virtual void typecheck() override;

    void interp() override;
};

struct Function_DeclarationStm : public Stm_{
    Function_signature* signature;
    StmList* stmlist;
    char* identifier;

    Function_DeclarationStm(Function_signature* sig, StmList* stml, char* id);

    Function_DeclarationStm();

    virtual void typecheck() override;

    virtual void interp() override;
};

struct DeclarationStm : public Stm_{
    int declaredType; 
    IdList* idlist;
    ExpList* explist;

    DeclarationStm(int dcltype, IdList* idl, ExpList* expl);

    DeclarationStm();

    virtual void typecheck() override;

    virtual void interp() override;
};

struct AssignStm : public Stm_
{
    IdList* idlist;
    ExpList* explist;
    AssignStm(IdList* id, ExpList* e);

    AssignStm();

    virtual void typecheck() override;

    virtual void interp() override;
};

struct ReturnStm : public Stm_
{
    Exp expr;

    ReturnStm(Exp e);
};


struct BlockStm : public Stm_{
    
    StmList* stmlist;

    BlockStm();

    BlockStm(StmList* stl);

    virtual void typecheck() override;

    virtual void interp() override;
};


struct VoidFunctionStm : public Stm_{
    ExpList* arguments;
    char* identifier;

    VoidFunctionStm(ExpList* args, char* id);

    VoidFunctionStm();

    virtual void typecheck() override;

    virtual void interp() override;

};


struct IncDecStm : public Stm_{
    int action;
    char* identifier;

    IncDecStm();

    IncDecStm(int ac, char* id);

    virtual void typecheck() override;

    virtual void interp() override;

};

struct If_stm : public Stm_{
    Exp exp;
    BlockStm* blockStm;

    If_stm(Exp ex, Stm bstm);

    If_stm();

    virtual void typecheck() override;

    virtual void interp() override;
};

struct For_stm : public Stm_{
    Exp exp;
    BlockStm* blockStm;

    For_stm(Exp ex, Stm bstm);

    For_stm();

    virtual void typecheck() override;

    virtual void interp() override;
};

struct ArithmeticAssignOpStm : public Stm_ {

    char* left;
    Exp right;
    int oper;

    ArithmeticAssignOpStm(char* l, int op, Exp r);

    ArithmeticAssignOpStm();

    virtual void typecheck() override;

    virtual void interp() override;

};
//Expressions
struct IntlitExp : public Exp_
{
    int intlit;

    IntlitExp(int i);

    IntlitExp();

    virtual int typecheck() override;
    virtual ReturnValue interp() override;
};

struct BoollitExp : public Exp_
{
    bool boollit;

    BoollitExp(bool b);

    BoollitExp();

    virtual int typecheck() override;
    virtual ReturnValue interp() override;
};

struct ArithmeticOpExp : public Exp_
{
    Exp left, right;
    int oper;

    ArithmeticOpExp(Exp l, int op, Exp r);

    ArithmeticOpExp();

    virtual int typecheck() override;

    virtual ReturnValue interp() override;
};
 

struct BooleanOpExp : public Exp_{

    Exp left;
    Exp right;
    int oper;

    BooleanOpExp(Exp l, int op, Exp r);

    BooleanOpExp();

    virtual int typecheck() override;

    virtual ReturnValue interp() override;
};

struct BooleanArithmeticOpExp : public Exp_{

    Exp left;
    Exp right;
    int oper;

    BooleanArithmeticOpExp(Exp l, int op, Exp r);

    BooleanArithmeticOpExp();

    virtual int typecheck() override;
    virtual ReturnValue interp() override;

};

struct NotExp : public Exp_{
    Exp expr;
    
    NotExp(Exp ex);

    NotExp();

    virtual int typecheck() override;
    virtual ReturnValue interp() override;
};

struct FunctionExp : public Exp_{
    ExpList* arguments;
    char* identifier;

    FunctionExp(ExpList* args, char* id);
  
    FunctionExp();

    virtual int typecheck() override;
    virtual ReturnValue interp() override;
};

struct IdExp: public Exp_{
    char* identifier;
    Exp expr;

    IdExp(char* id);

    IdExp();

    virtual int typecheck() override;
    virtual ReturnValue interp() override;
};

#endif
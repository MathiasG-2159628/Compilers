#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string> 
#include <typeinfo>
#include <vector>
#include "returnvalue.hpp"

struct Symbol {
    char* name;
    ReturnValue value;
    Symbol* next;

    Symbol(char* n, ReturnValue val);

    Symbol();
};
struct SymbolTable {
    Symbol* head;

    SymbolTable();
};

struct SymbolHandler{

    std::vector<SymbolTable> symbolTableStack;
    SymbolTable* symbolTable;

    SymbolHandler();

    void pushSymbolTable(SymbolTable st);

    void popSymbolTable();

    void addSymbol(char* name, ReturnValue value);

    void updateSymbol(char* name, ReturnValue value);

    ReturnValue lookupSymbol(char* name);
};

inline SymbolHandler symbolhandler;

#endif



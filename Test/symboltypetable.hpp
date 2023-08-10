#ifndef SYMBOLTYPETABLE_H
#define SYMBOLTYPETABLE_H

#include <string> 
#include <typeinfo>
#include <vector>
#include "returnvalue.hpp"

struct SymbolType {
    char* name;
    int type;
    SymbolType* next;

    SymbolType(char* n, int type);

    SymbolType();
};

struct SymbolTypeTable {
    SymbolType* head;

    SymbolTypeTable();
};

struct SymbolTypeHandler{

    std::vector<SymbolTypeTable> symbolTypeTableStack;
    SymbolTypeTable* symbolTypeTable;

    SymbolTypeHandler();

    void pushSymbolTypeTable(SymbolTypeTable st);

    void popSymbolTypeTable();

    void addSymbolType(char* name, int type);

    void updateSymbolType(char* name, int type);

    int lookupSymbolType(char* name);
};

inline SymbolTypeHandler symboltypehandler;

#endif



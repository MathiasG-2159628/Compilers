//FunctionType table

#ifndef FunctionTypeTYPE_TABLE
#define FunctionTypeTYPE_TABLE

#include <string>
#include <vector>
#include "structs.hpp"


struct FunctionType{

    FunctionType* next;
    char* name;
    int type;

    FunctionType(char* n, int t);

    FunctionType();
    
};

struct FunctionTypeTable {

    FunctionType* head; 

    FunctionTypeTable();
};


struct FunctionTypeHandler{

    FunctionTypeTable* functionTypeTable;

    FunctionTypeHandler();

    FunctionType lookupFunctionType(char* name);

    void addFunctionType(FunctionType* newFunctionType);
};

inline FunctionTypeHandler functiontypehandler;

#endif





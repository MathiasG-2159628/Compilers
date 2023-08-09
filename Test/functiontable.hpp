//Function table

#ifndef FUNCTION_TABLE
#define FUNCTION_TABLE

#include <string>
#include <vector>
#include "structs.hpp"


struct Function{

    Function* next;
    char* name;
    std::vector<char*> paramNames;
    std::vector<int> paramTypes;
    int functionType;
    StmList* stmlist;

    Function(char* n, std::vector<char*> names, std::vector<int> types, int functype, StmList* slist);

    Function();
    
};

struct FunctionTable {

    Function* head; 

    FunctionTable();
};


struct FunctionHandler{

    FunctionTable* functionTable;

    FunctionHandler();

    Function lookupFunction(char* name);

    void addFunction(Function* newFunction);
};

inline FunctionHandler functionhandler;

#endif





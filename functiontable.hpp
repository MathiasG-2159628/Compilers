//Function table

#include <string>
#include <vector>
#include "structs.hpp"

extern FunctionHandler functionhandler;

struct FunctionHandler{

    FunctionTable* functionTable;

    FunctionHandler();

    Function lookupFunction(std::string name);

    void addFunction(std::string name, Function* newFunction);
};

struct FunctionTable {

    Function* head; 

    FunctionTable();
};

struct Function{

    Function* next;
    std::string name;
    std::vector<std::string> paramNames;
    std::vector<int> paramTypes;
    int functionType;
    StmList stmlist;

    Function(std::string n, std::vector<std::string> names, std::vector<int> types, int functype, StmList slist);

    Function();
    
};






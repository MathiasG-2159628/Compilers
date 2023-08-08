#include "functiontable.hpp"
#include <cstring>

//Functionhandler definitions

void FunctionHandler::addFunction(char* name, Function* newFunction){
    newFunction->next = functionTable->head;
    functionTable->head = newFunction;
}

FunctionHandler::FunctionHandler(){
    FunctionTable funcTable;
    functionTable = &funcTable;
}


Function FunctionHandler::lookupFunction(char* name){
    Function* current = functionTable->head;
        while (current != nullptr) {
            if (!strcmp(current->name, name)) {
                return *current;
            }
            current = current->next;
        }
        

        printf("Function '%s' is not present in the function table.\n", name);

        return Function();
}


//Functiontable definitions

FunctionTable::FunctionTable(){
    head = nullptr;
}

//Function definitions

Function::Function(char* n, std::vector<char*> names, std::vector<int> types, int functype, StmList* slist){
        name = n;
        paramNames = names;
        paramTypes = types;
        functionType = functype;
        stmlist = slist;
}

Function::Function(){};
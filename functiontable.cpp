#include "functiontable.hpp"

//Functionhandler definitions

Function FunctionHandler::lookupFunction(std::string name){
    Function* current = functionTable->head;
        while (current != nullptr) {
            if (current->name == name) {
                return *current;
            }
            current = current->next;
        }
        

        printf("Function '%s' is not present in the function table.\n", name);

        return Function();
}

void FunctionHandler::addFunction(std::string name, Function* newFunction){
    newFunction->next = functionTable->head;
    functionTable->head = newFunction;
}

FunctionHandler::FunctionHandler(){
    functionTable = &FunctionTable();
}

//Functiontable definitions

FunctionTable::FunctionTable(){
    head = nullptr;
}

//Function definitions

Function::Function(std::string n, std::vector<std::string> names, std::vector<int> types, int functype, StmList slist){
        name = n;
        paramNames = names;
        paramTypes = types;
        functionType = functype;
        stmlist = slist;
}

Function::Function(){};
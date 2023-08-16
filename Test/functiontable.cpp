#include "functiontable.hpp"
#include <cstring>

//Functionhandler definitions

void FunctionHandler::addFunction(Function* newFunction){
    newFunction->next = functionTable->head;
    functionTable->head = newFunction;
    // std::cout << "Added function " << newFunction->name << " to function table" << std::endl;
}

FunctionHandler::FunctionHandler(){
    functionTable = new FunctionTable();
}


Function FunctionHandler::lookupFunction(char* name){

    // std::cout << "Looking up function " << name << std::endl;

    Function* current = functionTable->head;
        while (current != nullptr) {
            if (!strcmp(current->name, name)) {
                return *current;
            }
            current = current->next;
        }
        

        std::cout << "Function " << name << " is not present in the function table." << std::endl;
        exit(1);

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
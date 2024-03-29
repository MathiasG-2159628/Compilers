#include "functypetable.hpp"
#include <cstring>
#include "tokens.h"

//FunctionTypehandler definitions

void FunctionTypeHandler::addFunctionType(FunctionType* newFunctionType){

    // if(lookupFunctionType(newFunctionType->name).type != 0){
    //     std::cout << "Redefinition of function" << std::endl;
    // }

    newFunctionType->next = functionTypeTable->head;
    functionTypeTable->head = newFunctionType;
    // std::cout << "Added FunctionType " << newFunctionType->name << " to FunctionTypeType table" << std::endl;
}

FunctionTypeHandler::FunctionTypeHandler(){
    functionTypeTable = new FunctionTypeTable();
}


FunctionType FunctionTypeHandler::lookupFunctionType(char* name){

    // std::cout << "Looking up FunctionType " << name << std::endl;

    FunctionType* current = functionTypeTable->head;
        while (current != nullptr) {
            if (!strcmp(current->name, name)) {
                return *current;
            }
            current = current->next;
        }
        

        std::cout << "Function " << name << " is not present in the functiontype table." << std::endl;

        //can be ignored actually
        FunctionType functiontype;
        functiontype.type = 0; 

        return functiontype;
}


//FunctionTypetable definitions

FunctionTypeTable::FunctionTypeTable(){
    head = nullptr;
}

//FunctionType definitions

FunctionType::FunctionType(char* n, int t){
        name = n;
        type = t;
}

FunctionType::FunctionType(){};
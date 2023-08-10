#include "functypetable.hpp"
#include <cstring>
#include "tokens.h"

//FunctionTypehandler definitions

void FunctionTypeHandler::addFunctionType(FunctionType* newFunctionType){
    newFunctionType->next = functionTypeTable->head;
    functionTypeTable->head = newFunctionType;
    std::cout << "Added FunctionType " << newFunctionType->name << " to FunctionTypeType table" << std::endl;
}

FunctionTypeHandler::FunctionTypeHandler(){
    functionTypeTable = new FunctionTypeTable();
}


FunctionType FunctionTypeHandler::lookupFunctionType(char* name){

    std::cout << "Looking up FunctionType " << name << std::endl;

    FunctionType* current = functionTypeTable->head;
        while (current != nullptr) {
            if (!strcmp(current->name, name)) {
                return *current;
            }
            current = current->next;
        }
        

        printf("FunctionType '%s' is not present in the FunctionType table.\n", name);

        return FunctionType();
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
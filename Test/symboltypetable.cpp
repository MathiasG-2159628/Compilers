#include "symboltypetable.hpp"
#include <string>
#include <iostream>
#include <cstring>

extern SymbolTypeHandler symboltypehandler;

//SymbolTypehandler definitions

SymbolTypeHandler::SymbolTypeHandler(){
    symbolTypeTableStack = std::vector<SymbolTypeTable>();
}

void SymbolTypeHandler::pushSymbolTypeTable(SymbolTypeTable st) {
    std::cout << "SymbolType table pushed" << std::endl;
    symbolTypeTableStack.emplace_back(st);
    symbolTypeTable = &symbolTypeTableStack.back();
}

void SymbolTypeHandler::popSymbolTypeTable() {
    if (!symbolTypeTableStack.empty()) {
        symbolTypeTableStack.pop_back();
        if (!symbolTypeTableStack.empty()) {
            symbolTypeTable = &symbolTypeTableStack.back();
        } else {
            symbolTypeTable = nullptr;
        }
    }
     std::cout << "SymbolType table popped" << std::endl;
}

void SymbolTypeHandler::addSymbolType(char* name, int value) {
    SymbolType* newSymbolType = new SymbolType(name, value); 
    newSymbolType->next = symbolTypeTable->head;

    symbolTypeTable->head = newSymbolType;
};

void SymbolTypeHandler::updateSymbolType(char* name, int value) {
        for (int i = symbolTypeTableStack.size() - 1; i >= 0; --i) {
            SymbolType* current = symbolTypeTableStack[i].head;
            while (current != nullptr) {
                //strcmp returns 0 if succeded
                if (!strcmp(current->name, name)) 
                {
                    current->type = value;
                    return;
                }
                current = current->next;
            }
        }

        printf("Variable '%s' does not exist in the SymbolType table.\n", name);
};

int SymbolTypeHandler::lookupSymbolType(char* name){
        for (int i = symbolTypeTableStack.size() - 1; i >= 0; --i) {

            //TODO: IF SymbolType IS NOT FOUND IN CURRENT SCOPE, SEARCH THROUGH PREVIOUS SCOPES

            SymbolType* current =  symbolTypeTableStack[i].head;

            while (current != nullptr) {
              //strcmp returns 0 if succeded
                if (!strcmp(current->name, name)) {
                    return current->type;
                }
                current = current->next;
            }
        }

        printf("Variable '%s' is not present in the SymbolType table.\n", name);

        return 0;
};

//SymbolType table definitions

SymbolTypeTable::SymbolTypeTable(){
    head = nullptr;
}

//SymbolType definitions

SymbolType::SymbolType(char* n, int val){
        name = n;
        type = val;
}

SymbolType::SymbolType(){

}







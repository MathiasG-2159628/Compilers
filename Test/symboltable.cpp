#include "symboltable.hpp"
#include <string>
#include <iostream>
#include <cstring>

extern SymbolHandler symbolhandler;

//Symbolhandler definitions

SymbolHandler::SymbolHandler(){
    symbolTableStack = std::vector<SymbolTable>();
}

void SymbolHandler::pushSymbolTable(SymbolTable st) {
    // std::cout << "Symbol table pushed" << std::endl;
    symbolTableStack.emplace_back(st);
    symbolTable = &symbolTableStack.back();
}

void SymbolHandler::popSymbolTable() {
    if (!symbolTableStack.empty()) {
        symbolTableStack.pop_back();
        if (!symbolTableStack.empty()) {
            symbolTable = &symbolTableStack.back();
        } else {
            symbolTable = nullptr;
        }
    }
    //  std::cout << "Symbol table popped" << std::endl;
}

void SymbolHandler::addSymbol(char* name, ReturnValue value) {
    Symbol* newSymbol = new Symbol(name, value); 
    newSymbol->next = symbolTable->head;

    symbolTable->head = newSymbol;
};

void SymbolHandler::updateSymbol(char* name, ReturnValue value) {
        for (int i = symbolTableStack.size() - 1; i >= 0; --i) {
            Symbol* current = symbolTableStack[i].head;
            while (current != nullptr) {
                //strcmp returns 0 if succeded
                if (!strcmp(current->name, name)) 
                {
                    current->value = value;
                    return;
                }
                current = current->next;
            }
        }

        std::cout << "Variable " << name << " does not exist in the symbol table" << std::endl;
        exit(1);
};

ReturnValue SymbolHandler::lookupSymbol(char* name){
        for (int i = symbolTableStack.size() - 1; i >= 0; --i) {

            //TODO: IF SYMBOL IS NOT FOUND IN CURRENT SCOPE, SEARCH THROUGH PREVIOUS SCOPES

            Symbol* current =  symbolTableStack[i].head;

            while (current != nullptr) {
              //strcmp returns 0 if succeded
                if (!strcmp(current->name, name)) {
                    return current->value;
                }
                current = current->next;
            }
        }

        std::cout << "Variable " << name << " does not exist in the symbol table" << std::endl;
        exit(1);

        return ReturnValue();
};

//Symbol table definitions

SymbolTable::SymbolTable(){
    head = nullptr;
}

//Symbol definitions

Symbol::Symbol(char* n, ReturnValue val){
        name = n;
        value = val;
}

Symbol::Symbol(){

}







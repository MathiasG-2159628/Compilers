#include "symboltable.hpp"
#include <string>

extern SymbolHandler symbolhandler;

//Symbolhandler definitions

SymbolHandler::SymbolHandler(){
    symbolTableStack = std::vector<SymbolTable>();
}

void SymbolHandler::pushSymbolTable(SymbolTable st) {
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
}

void SymbolHandler::addSymbol(std::string name, ReturnValue value) {
    Symbol* newSymbol = new Symbol(name, value); 
    symbolTable->head = newSymbol;
};

void SymbolHandler::updateSymbol(std::string name, ReturnValue value) {
        for (int i = symbolTableStack.size() - 1; i >= 0; --i) {
            Symbol* current = symbolTableStack[i].head;
            while (current != nullptr) {
                if (current->name == name) 
                {
                    current->value = value;
                    return;
                }
                current = current->next;
            }
        }

        printf("Variable '%s' does not exist in the symbol table.\n", name);
};

ReturnValue SymbolHandler::lookupSymbol(std::string name){
        for (int i = symbolTableStack.size() - 1; i >= 0; --i) {
            Symbol* current =  symbolTableStack[i].head;
            while (current != nullptr) {
                if (current->name == name) {
                    return current->value;
                }
                current = current->next;
            }
        }

        printf("Variable '%s' is not present in the symbol table.\n", name);

        return ReturnValue();
};

//Symbol table definitions

SymbolTable::SymbolTable(){
    head = nullptr;
}

//Symbol definitions

Symbol::Symbol(std::string n, ReturnValue val){
        name = n;
        value = val;
}

Symbol::Symbol(){

}







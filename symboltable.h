#include <cstring> 
#include "yyfunctions.h"
#include <typeinfo>
#include <vector>
//TODO: error handling
//TODO: handle scoping, look at chatGPT as
struct Symbol {
    std::string name;
    ReturnValue value;
    Symbol* next;

    Symbol(std::string n, ReturnValue val){
        name = n;
        value = val;
    }

    Symbol(){
        
    }
};


struct SymbolTable {
    Symbol* head; 
};

std::vector<SymbolTable> symbolTableStack;
SymbolTable* symbolTable = nullptr;

void pushSymbolTable(SymbolTable st) {
    symbolTableStack.emplace_back(st);
    symbolTable = &symbolTableStack.back();
};

void popSymbolTable() {
    if (!symbolTableStack.empty()) {
        symbolTableStack.pop_back();
        if (!symbolTableStack.empty()) {
            symbolTable = &symbolTableStack.back();
        } else {
            symbolTable = nullptr;
        }
    }
}

void addSymbol(std::string name, ReturnValue value) {
    Symbol* newSymbol = new Symbol(name, value); 
    symbolTable->head = newSymbol;
}

void updateSymbol(std::string name, ReturnValue value) {
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
}

ReturnValue lookupSymbol(std::string name) {
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

    return;
}



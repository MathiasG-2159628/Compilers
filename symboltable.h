#include <cstring> 
#include "yyfunctions.h"
#include <typeinfo>
#include <vector>
//TODO: error handling
//TODO: handle scoping, look at chatGPT as
template <typename T>
struct Symbol {
    std::string name;
    T value;
    Symbol* next;

    Symbol(std::string n, T val, Symbol* nx){
        name = n;
        value = val;
        next = nx;
    }

    Symbol(){
        
    }
};


struct SymbolTable {
    Symbol<int>* head; 
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

template <typename T>
void addSymbol(std::string name, T value) {
    Symbol<T>* newSymbol = new Symbol<T>(name, value); 
    symbolTable->head = newSymbol;
}

//TODO: catch runtime error
template <typename T>
void updateSymbol(std::string name, T value) {
    for (int i = symbolTableStack.size() - 1; i >= 0; --i) {
        Symbol<T>* current = symbolTableStack[i]->head;
        while (current != nullptr) {
            if (strcmp(current->name, name) == 0) {
                current->value = value;
                return;
            }
            current = current->next;
        }
    }

    printf("Variable '%s' does not exist in the symbol table.\n", name);
}

// Templated function to lookup a symbol
template <typename T>
T lookupSymbol(std::string name) {
    for (int i = symbolTableStack.size() - 1; i >= 0; --i) {
        Symbol<T>* current = symbolTableStack[i]->head;
        while (current != nullptr) {
            if (strcmp(current->name, name) == 0) {
                return current->value;
            }
            current = current->next;
        }
    }

    printf("Variable '%s' is not present in the symbol table.\n", name);

    return;
}



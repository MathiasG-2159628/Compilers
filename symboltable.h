#include <cstring> 
#include "yyfunctions.h"
#include <typeinfo>
#include <vector>
//TODO: error handling

template <typename T>
struct Symbol {
    char* name;
    T value;
    struct Symbol* next;

    Symbol(char* n, T val, Symbol* nx){
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
void addSymbol(char* name, T value) {
    Symbol<T>* newSymbol = new Symbol<T>(); 
    strcpy(newSymbol->name, name);
    newSymbol->value = value;
    newSymbol->next = symbolTable->head;
    symbolTable->head = newSymbol;
}

//TODO: catch runtime error
template <typename T>
void updateSymbol(char* name, T value) {
    Symbol<T>* current = symbolTable->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->value = value;          
            return;
        }
        current = current->next;
    }

    printf("Variabele '%s' bestaat niet in the symbol table.\n", name);
}

// Templated function to lookup a symbol
template <typename T>
T lookupSymbol(char* name) {
    Symbol<T>* current = symbolTable->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }

    printf("Variabele '%s' is niet aanwezig in the symbol table.\n", name);
    return;
}



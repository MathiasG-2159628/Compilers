#include <cstring> 
#include "yyfunctions.h"
#include <typeinfo>
//TODO: error handling

template <typename T>
struct Symbol {
    char name[10];
    T value;
    struct Symbol* next;
};


struct SymbolTable {
    Symbol<void>* head; 
};

extern SymbolTable symbolTable;

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
    Symbol<T>* current = st->head;
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
    Symbol<T>* current = st->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }

    printf("Variabele '%s' is niet aanwezig in the symbol table.\n", name);
    return;
}


extern SymbolTable symbolTable;
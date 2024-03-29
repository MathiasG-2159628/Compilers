#include <string> 
#include <typeinfo>
#include <vector>
#include "ReturnValue.hpp"

struct Symbol {
    std::string name;
    ReturnValue value;
    Symbol* next;

    Symbol(std::string n, ReturnValue val);

    Symbol();
};
struct SymbolTable {
    Symbol* head;

    SymbolTable();
};

struct SymbolHandler{

    std::vector<SymbolTable> symbolTableStack;
    SymbolTable* symbolTable;

    SymbolHandler();

    void pushSymbolTable(SymbolTable st);

    void popSymbolTable();

    void addSymbol(std::string name, ReturnValue value);

    void updateSymbol(std::string name, ReturnValue value);

    ReturnValue lookupSymbol(std::string name);
};



extern SymbolHandler symbolhandler;




#include <cstring> 
#include "yyfunctions.h"
#include <typeinfo>
#include <vector>
#include "structs.h"



struct Function{

    std::vector<char*> paramNames;
    std::vector<int> paramTypes;
    int functionType;
    StmList stmlist;

    Function(std::vector<char*> names, std::vector<int> types, int functype, StmList slist){
        paramNames = names;
        paramTypes = types;
        functionType = functype;
        stmlist = slist;
    }
    
};
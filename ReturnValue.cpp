#include "ReturnValue.hpp"

ReturnValue::ReturnValue(int i){
    intValue = &i;
}

ReturnValue::ReturnValue(bool b){
    boolValue = &b;
}

ReturnValue::ReturnValue(){
    
}
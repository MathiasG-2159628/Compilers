#include "returnvalue.hpp"
#include <iostream>

ReturnValue::ReturnValue(int i){
    intValue = &i;
}

ReturnValue::ReturnValue(bool b){
    boolValue = &b;

}

ReturnValue::ReturnValue(){
    
}
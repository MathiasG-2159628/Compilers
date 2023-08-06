#include "returnvalue.hpp"
#include <iostream>

ReturnValue::ReturnValue(int i){
    intValue = new int(i);
}

ReturnValue::ReturnValue(bool b){
    boolValue = new bool(b);

}

ReturnValue::ReturnValue(){
    
}
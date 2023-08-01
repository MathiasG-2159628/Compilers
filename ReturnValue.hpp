struct ReturnValue{
    int* intValue = nullptr;
    bool* boolValue = nullptr;

    ReturnValue(int i){
        intValue = &i;
    }

    ReturnValue(bool b){
        boolValue = &b;
    }

    ReturnValue(){

    }
};
#ifndef RETURNVALUE_H
#define RETURNVALUE_H

struct ReturnValue{
    int* intValue = nullptr;
    bool* boolValue = nullptr;

    ReturnValue(int i);

    ReturnValue(bool b);

    ReturnValue();
};

#endif
struct ReturnValue{
    int* intValue = nullptr;
    bool* boolValue = nullptr;

    ReturnValue(int i);

    ReturnValue(bool b);

    ReturnValue();
};
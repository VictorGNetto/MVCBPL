struct LocalVariableType {
    enum LocalVariableBaseType { vInteger, vArray } baseType;

    // don't apply if baseType is integer
    // if baseType is array, then this members saves the array size
    unsigned int size;
};

struct LocalVariable {
    // 1, 2, ..., 5
    int vIdentifier;

    // integer or array. If array, also keep the array size.
    // Forms a name together with the vIdentifier
    struct LocalVariableType vType;

    // variable address relative to the %bsp register
    // Ex: vAddr = 4 means that the local variable is kept at -4(%rbp)
    unsigned int vAddr;
};
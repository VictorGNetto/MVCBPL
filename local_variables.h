#ifndef _LOCAL_VARIABLES_H
#define _LOCAL_VARIABLES_H

struct LocalVariableType {
    enum LocalVariableBaseType { Integer, Array } baseType;

    // don't apply if baseType is integer
    // if baseType is array, then this members saves the array size
    unsigned int size;
};

struct LocalVariable {
    // 1, 2, ..., 5
    int identifier;

    // integer or array. If array, also keep the array size.
    // Forms a name together with the vIdentifier
    struct LocalVariableType type;

    // variable address relative to the %bsp register
    // Ex: vAddr = 4 means that the local variable is kept at -4(%rbp)
    unsigned int addr;
};

// return address (relative to the %rbp register)
// of a integer variable or parameter.
// type: 'v' -> local variable; 'p' -> parameter
// identifier: 1, 2, 3, 4, 5 for local variables; 1, 2, 3 for parameters
// (This function returns the address of a parameter only
//  when that parameter was previously saved in the stack)
unsigned int get_int_addr(struct LocalVariable *localVariables, char type, int identifier);

// return address (relative to the %rbp register) of a array variable
unsigned int get_array_addr(struct LocalVariable *localVariables, int identifier);

#endif  // _LOCAL_VARIABLES_H
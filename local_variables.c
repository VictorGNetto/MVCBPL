#include "local_variables.h"

unsigned int get_int_addr(struct LocalVariable *localVariables, char type, int identifier)
{
    if (type == 'p')
    {
        return identifier * 8;
    }
    else // if (type == 'v')
    {
        return localVariables[identifier - 1].addr;
    }
}

unsigned int get_array_addr(struct LocalVariable *localVariables, int identifier)
{
    return localVariables[identifier - 1].addr;
}
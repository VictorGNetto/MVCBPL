#include <stdio.h>
#include <string.h>
#include "local_variables.h"

#define MAX_LINE_SIZE 256

static int process_local_variables(struct LocalVariable *localVariables)
{
    char line[MAX_LINE_SIZE];
    int r, localVariablesCount, arraySize;
    unsigned int address = 0;

    localVariablesCount = 0;
    while (fgets(line, MAX_LINE_SIZE, stdin) != NULL)
    {
        r = sscanf(line, "var vi%d", &localVariablesCount);
        if (r == 1)
        {
            address += 4;

            localVariables[localVariablesCount - 1].identifier = localVariablesCount;
            localVariables[localVariablesCount - 1].type.baseType = Integer;
            localVariables[localVariablesCount - 1].addr = address;
        }

        r = sscanf(line, "vet va%d size ci%d", &localVariablesCount, &arraySize);
        if (r == 2)
        {
            address += arraySize * 4;

            localVariables[localVariablesCount - 1].identifier = localVariablesCount;
            localVariables[localVariablesCount - 1].type.baseType = Array;
            localVariables[localVariablesCount - 1].type.size = arraySize;
            localVariables[localVariablesCount - 1].addr = address;
        }

        if (strncmp(line, "enddef", 6) == 0)
            return localVariablesCount;
    }
}

static void show_parameters_locations(int parametersCount)
{
    switch (parametersCount)
    {
    case 1:
        printf("\t# if needed %%rdi is saved at -8(%%rbp) before function call\n");
        break;
    case 2:
        printf("\t# if needed %%rdi is saved at -8(%%rbp) before function call\n");
        printf("\t# if needed %%rsi is saved at -16(%%rbp) before function call\n");
        break;
    case 3:
        printf("\t# if needed %%rdi is saved at -8(%%rbp) before function call\n");
        printf("\t# if needed %%rsi is saved at -16(%%rbp) before function call\n");
        printf("\t# if needed %%rdx is saved at -24(%%rbp) before function call\n");
        break;
    }
}

static void show_local_variables_location(int localVariablesCount, struct LocalVariable *localVariables)
{
    for (int i = 0; i < localVariablesCount; i++)
    {
        unsigned int address = localVariables[i].addr;
        if (localVariables[i].type.baseType == Integer)
            printf("\t# vi%d is kept at -%u(%%rbp)\n", localVariables[i].identifier, address);
        else //if (localVariables[i].type.baseType == Array)
            printf("\t# va%d[%d] is kept at -%u(%%rbp)\n", localVariables[i].identifier, localVariables[i].type.size, address);
    }
}

void stack_allocation(struct LocalVariable *localVariables, int parametersCount)
{
    int stackBytesUsed;
    int localVariablesCount;

    // reserve space for the parameters for an eventual function call
    stackBytesUsed = 8 * parametersCount;

    // process local variables and update their adresses
    localVariablesCount = process_local_variables(localVariables);
    for (int i = 0; i < localVariablesCount; i++)
        localVariables[i].addr += stackBytesUsed;

    // update the total memory needed from the stack
    // and make sure it's aligned
    if (localVariablesCount > 0)
        stackBytesUsed = localVariables[localVariablesCount - 1].addr;
    if (stackBytesUsed % 16 != 0)
        stackBytesUsed += 16 - stackBytesUsed % 16;
    
    printf("\tpushq %%rbp\n");
    printf("\tmovq %%rsp, %%rbp\n");
    if (stackBytesUsed > 0)
        printf("\tsubq $%d, %%rsp\n", stackBytesUsed);
    printf("\n");

    // Show the position where local variables and (possibly)
    // parameters are saved in the stack
    show_parameters_locations(parametersCount);
    show_local_variables_location(localVariablesCount, localVariables);
}
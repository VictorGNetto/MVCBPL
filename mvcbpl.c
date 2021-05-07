// Márcio & Victor's Compiler of the Bruno's Programming Language
// Márcio Rodrigues Filho, Victor Gonçalves Netto

#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 256

#include "local_variables.h"

int process_local_variables(struct LocalVariable * localVariables)
{
    char line[MAX_LINE_SIZE];
    int r, localVariablesCount, arraySize;
    unsigned int address = 0;

    localVariablesCount = 0;
    while(fgets(line, MAX_LINE_SIZE, stdin) != NULL) {
        r = sscanf(line, "var vi%d", &localVariablesCount);
        if (r == 1)
        {
            address += 4;

            localVariables[localVariablesCount - 1].vIdentifier = localVariablesCount;
            localVariables[localVariablesCount - 1].vType.baseType = vInteger;
            localVariables[localVariablesCount - 1].vAddr = address;
        }

        r = sscanf(line, "vet va%d size ci%d", &localVariablesCount, &arraySize);
        if (r == 2)
        {
            address += arraySize * 4;

            localVariables[localVariablesCount - 1].vIdentifier = localVariablesCount;
            localVariables[localVariablesCount - 1].vType.baseType = vArray;
            localVariables[localVariablesCount - 1].vType.size = arraySize;
            localVariables[localVariablesCount - 1].vAddr = address;
        }

        if (strncmp(line, "enddef", 6) == 0)
            return localVariablesCount;
    }
}

void compile_function(int parametersCount, int functionIdentifier)
{
    char line[MAX_LINE_SIZE];
    struct LocalVariable localVariables[5];
    int stackBytesUsed;
    int localVariablesCount;

    // reserve space for the parameters for an eventual function call
    stackBytesUsed = 8 * parametersCount;

    // process local variables and update their adresses
    localVariablesCount = process_local_variables(localVariables);
    for (int i = 0; i < localVariablesCount; i++)
        localVariables[i].vAddr += stackBytesUsed;
    
    // update the total memory needed from the stack
    // and make sure it's aligned
    stackBytesUsed = localVariables[localVariablesCount - 1].vAddr;
    if (stackBytesUsed % 16 != 0)
        stackBytesUsed += 16 - stackBytesUsed % 16;

    printf("\tpushq %%rbp\n");
    printf("\tmovq %%rsp, %%rbp\n");
    if (stackBytesUsed > 0)
        printf("\tsubq $%d, %%rsp\n", stackBytesUsed);
    printf("\n");

    for (int i = 0; i < localVariablesCount; i++)
    {
        unsigned int address = localVariables[i].vAddr;
        if (localVariables[i].vType.baseType == vInteger)
            printf("\t# vi%d is kept at -%u(%%rbp)\n", localVariables[i].vIdentifier, address);
        else //if (localVariables[i].vType.baseType == vArray)
            printf("\t# va%d[%d] is kept at -%u(%%rbp)\n", localVariables[i].vIdentifier, localVariables[i].vType.size, address);
    }

    while(fgets(line, MAX_LINE_SIZE, stdin) != NULL) {
        if (strncmp(line, "end", 3) == 0)
        {
            printf("\n");
            printf("return_f%d:\n", functionIdentifier);
            printf("\tleave\n");
            printf("\tret\n");
            return;
        }
    }
}

int main()
{
    char line[MAX_LINE_SIZE];

    int r, functionIdentifier;
    char p1, p2, p3;

    printf(".text\n\n");

    while(fgets(line, MAX_LINE_SIZE, stdin) != NULL) {
        r = sscanf(line, "function f%d p%c1, p%c2, p%c3", &functionIdentifier, &p1, &p2, &p3);

        // no parameters
        if (r == 1)
        {
            printf(".globl f%d\nf%d:\n", r, r);
            compile_function(0, functionIdentifier);
            printf("\n");
        }
        // 1 parameter
        if (r == 2)
        {
            printf(".globl f%d\nf%d:\n", r, r);
            compile_function(1, functionIdentifier);
            printf("\n");
        }
        // 2 parameters
        else if (r == 3)
        {
            printf(".globl f%d\nf%d:\n", r, r);
            compile_function(2, functionIdentifier);
            printf("\n");
        }
        // 3 parameters
        else if (r == 4)
        {
            printf(".globl f%d\nf%d:\n", r, r);
            compile_function(3, functionIdentifier);
            printf("\n");
        }
    }

    return 0;
}
// Márcio & Victor's Compiler of the Bruno's Programming Language
// Márcio Rodrigues Filho, Victor Gonçalves Netto

#include <stdio.h>
#include <string.h>

#include "local_variables.h"

#define MAX_LINE_SIZE 256

void compile_return_command(char *line, struct LocalVariable *localVariables)
{
    int r, a;

    r = sscanf(line, "return vi%d", &a);
    if (r == 1)
    {
        unsigned int address = localVariables[a - 1].vAddr;
        printf("\n\t# return vi%d\n", a);
        printf("\tmovl -%u(%%rbp), %%eax\n", address);
    }
    r = sscanf(line, "return pi%d", &a);
    if (r == 1)
    {
        printf("\n\t# return pi%d\n", a);
        if (a == 1)
        {
            printf("\tmovl %%edi, %%eax\n");
        }
        else if (a == 2)
        {
            printf("\tmovl %%esi, %%eax\n");
        }
        else // if (a == 3)
        {
            printf("\tmovl %%edx, %%eax\n");
        }
    }
    r = sscanf(line, "return ci%d", &a);
    if (r == 1)
    {
        printf("\n\t# return ci%d\n", a);
        printf("\tmovl $%d, %%eax\n", a);
    }
}

int process_local_variables(struct LocalVariable *localVariables)
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
    int r, a, b, c;

    // reserve space for the parameters for an eventual function call
    stackBytesUsed = 8 * parametersCount;

    // process local variables and update their adresses
    localVariablesCount = process_local_variables(localVariables);
    for (int i = 0; i < localVariablesCount; i++)
        localVariables[i].vAddr += stackBytesUsed;

    // update the total memory needed from the stack
    // and make sure it's aligned
    if (localVariablesCount > 0)
        stackBytesUsed = localVariables[localVariablesCount - 1].vAddr;
    if (stackBytesUsed % 16 != 0)
        stackBytesUsed += 16 - stackBytesUsed % 16;

    printf("\tpushq %%rbp\n");
    printf("\tmovq %%rsp, %%rbp\n");
    if (stackBytesUsed > 0)
        printf("\tsubq $%d, %%rsp\n", stackBytesUsed);
    printf("\n");

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
    for (int i = 0; i < localVariablesCount; i++)
    {
        unsigned int address = localVariables[i].vAddr;
        if (localVariables[i].vType.baseType == vInteger)
            printf("\t# vi%d is kept at -%u(%%rbp)\n", localVariables[i].vIdentifier, address);
        else //if (localVariables[i].vType.baseType == vArray)
            printf("\t# va%d[%d] is kept at -%u(%%rbp)\n", localVariables[i].vIdentifier, localVariables[i].vType.size, address);
    }

    while (fgets(line, MAX_LINE_SIZE, stdin) != NULL)
    {
        // assignment

        // function call

        // array access

        // conditional

        // function return ----------------------------------------------------
        if (strncmp(line, "return", 6) == 0)
        {
            compile_return_command(line, localVariables);
        }

        // function end
        if (strncmp(line, "end", 3) == 0)
        {
            printf("\n");
            printf("return_f%d:\n", functionIdentifier);
            printf("\tleave\n");
            printf("\tret\n\n");
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

    while (fgets(line, MAX_LINE_SIZE, stdin) != NULL)
    {
        r = sscanf(line, "function f%d p%c1, p%c2, p%c3", &functionIdentifier, &p1, &p2, &p3);

        if (r > 0) {
            printf(".globl f%d\nf%d:\n", functionIdentifier, functionIdentifier);
            compile_function(r - 1, functionIdentifier);
            printf("\n");
        }
    }

    return 0;
}
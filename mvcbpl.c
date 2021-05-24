// Márcio & Victor's Compiler of the Bruno's Programming Language
// Márcio Rodrigues Filho, Victor Gonçalves Netto

#include <stdio.h>
#include <string.h>

#include "local_variables.h"

#define MAX_LINE_SIZE 256

// return address (relative to the %rbp register) of a integer
// variable or parameter
unsigned int int_stack_addr(struct LocalVariable *localVariables, char c1, int d)
{
    if (c1 == 'p')
    {
        return d * 8;
    }
    else // if (c1 == 'v')
    {
        return localVariables[d - 1].vAddr;
    }
}

void process_1st_parameter(struct LocalVariable *localVariables,
                           char c1, char c2, char d)
{
    if (c1 == 'c')
    {
        printf("\tmovl $%d, %%edi  # 1o parameter\n", d);
    }
    else if (c2 == 'i')
    {
        int address = int_stack_addr(localVariables, c1, d);
        printf("\tmovl -%d(%%rbp), %%edi  # 1o parameter\n", address);
    }
    else // if (c2 == 'a')
    {
        int address = int_stack_addr(localVariables, c1, d);
        printf("\tmovq -%d(%%rbp), %%rdi  # 1o parameter\n", address);
    }
}

void process_2nd_parameter(struct LocalVariable *localVariables,
                           char c1, char c2, char d)
{
    if (c1 == 'c')
    {
        printf("\tmovl $%d, %%esi  # 2o parameter\n", d);
    }
    else if (c2 == 'i')
    {
        int address = int_stack_addr(localVariables, c1, d);
        printf("\tmovl -%d(%%rbp), %%esi  # 2o parameter\n", address);
    }
    else // if (c2 == 'a')
    {
        int address = int_stack_addr(localVariables, c1, d);
        printf("\tmovq -%d(%%rbp), %%rsi  # 2o parameter\n", address);
    }
}

void process_3rd_parameter(struct LocalVariable *localVariables,
                           char c1, char c2, char d)
{
    if (c1 == 'c')
    {
        printf("\tmovl $%d, %%edx  # 3o parameter\n", d);
    }
    else if (c2 == 'i')
    {
        int address = int_stack_addr(localVariables, c1, d);
        printf("\tmovl -%d(%%rbp), %%edx  # 3o parameter\n", address);
    }
    else // if (c2 == 'a')
    {
        int address = int_stack_addr(localVariables, c1, d);
        printf("\tmovq -%d(%%rbp), %%rdx  # 3o parameter\n", address);
    }
}

void show_parameters_locations(int parametersCount)
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

void show_local_variables_location(int localVariablesCount, struct LocalVariable *localVariables)
{
    for (int i = 0; i < localVariablesCount; i++)
    {
        unsigned int address = localVariables[i].vAddr;
        if (localVariables[i].vType.baseType == vInteger)
            printf("\t# vi%d is kept at -%u(%%rbp)\n", localVariables[i].vIdentifier, address);
        else //if (localVariables[i].vType.baseType == vArray)
            printf("\t# va%d[%d] is kept at -%u(%%rbp)\n", localVariables[i].vIdentifier, localVariables[i].vType.size, address);
    }
}

void compile_assignment_command(char *line, struct LocalVariable *localVariables, int parametersCount)
{
    // TODO: [x]simple assignment, [ ]expression or [x]function return
    int r, a, b, d1, d2, d3;
    char c11, c12, c21, c22, c31, c32, operacao;

    printf("\n\t# %s", line);

    // expression assignment
    r = sscanf(line, "vi%d = %ci%d %c %ci%d", &a, &c11, &d1, &operacao, &c21, &d2);
    if (r == 6)
    {
        if (c11 == 'c')
        {
            printf("\tmovl $%d, %%eax\n", d1);
        }
        else if (c11 == 'v')
        {
            printf("\tmovl -%u(%%rbp), %%eax\n", localVariables[d1 - 1].vAddr);
        }
        else
        {
            if (d1 == 1)
            {
                printf("\tmovl %%edi, %%eax\n");
            }
            else if (d1 == 2)
            {
                printf("\tmovl %%esi, %%eax\n");
            }
            else
            {
                printf("\tmovl %%edx, %%eax\n");
            }
        }

        if (c21 == 'c')
        {
            printf("\tmovl $%d, %%ecx\n", d2);
        }
        else if (c21 == 'v')
        {
            printf("\tmovl -%u(%%rbp), %%ecx\n", localVariables[d2 - 1].vAddr);
        }
        else
        {
            if (d2 == 1)
            {
                printf("\tmovl %%edi, %%ecx\n");
            }
            else if (d2 == 2)
            {
                printf("\tmovl %%esi, %%ecx\n");
            }
            else
            {
                printf("\tmovl %%edx, %%ecx\n");
            }
        }

        switch (operacao)
        {
        case '+':
            printf("\taddl %%ecx, %%eax\n");
            break;
        case '-':
            printf("\tsubl %%ecx, %%eax\n");
            break;
        case '*':
            printf("\timull %%ecx, %%eax\n");
            break;
        case '/':
            if (parametersCount == 3)
            {
                printf("\tmovl %%edx, %%r8d\n");
                printf("\tcltd\n");
                printf("\tidivl %%ecx\n");
                printf("\tmovl %%r8d, %%edx\n");
            }
            else
            {
                printf("\tcltd\n");
                printf("\tidivl %%ecx\n");
            }

            break;
        }

        printf("\tmovl %%eax, -%u(%%rbp)\n", localVariables[a - 1].vAddr);
        return;
    }

    // simple assignment
    r = sscanf(line, "vi%d = ci%d", &a, &b);
    if (r == 2)
    {
        printf("\tmovl $%d, -%u(%%rbp)\n", b, localVariables[a - 1].vAddr);
        return;
    }
    r = sscanf(line, "vi%d = vi%d", &a, &b);
    if (r == 2)
    {
        printf("\tmovl -%u(%%rbp), %%eax\n", localVariables[b - 1].vAddr);
        printf("\tmovl %%eax, -%u(%%rbp)\n", localVariables[a - 1].vAddr);
        return;
    }
    r = sscanf(line, "vi%d = pi%d", &a, &b);
    if (r == 2)
    {
        if (b == 1)
        {
            printf("\tmovl %%edi, -%u(%%rbp)\n", localVariables[a - 1].vAddr);
        }
        else if (b == 2)
        {
            printf("\tmovl %%esi, -%u(%%rbp)\n", localVariables[a - 1].vAddr);
        }
        else // if (b == 3)
        {
            printf("\tmovl %%edx, -%u(%%rbp)\n", localVariables[a - 1].vAddr);
        }
        return;
    }

    //
    // function return assignment
    r = sscanf(line, "vi%d = call f%d %c%c%d %c%c%d %c%c%d", &a, &b,
               &c11, &c12, &d1, &c21, &c22, &d2, &c31, &c32, &d3);
    if (r == 2)
    {
        printf("\tcall f%d\n", b);
        printf("\tmovl %%eax, -%u(%%rbp)\n", localVariables[a - 1].vAddr);
        return;
    }
    else if (r == 5)
    {
        if (parametersCount > 0) // save %rdi in the stack
        {
            printf("\tmovq %%rdi, -8(%%rbp)\n");
        }

        process_1st_parameter(localVariables, c11, c12, d1);

        printf("\tcall f%d\n", b);
        printf("\tmovl %%eax, -%u(%%rbp)\n", localVariables[a - 1].vAddr);

        if (parametersCount > 0) // get %rdi back from the the stack
        {
            printf("\tmovq -8(%%rbp), %%rdi\n");
        }
        return;
    }
    else if (r == 8)
    {
        if (parametersCount > 0) // save %rdi in the stack
        {
            printf("\tmovq %%rdi, -8(%%rbp)\n");
        }
        if (parametersCount > 1) // save %rsi in the stack
        {
            printf("\tmovq %%rsi, -16(%%rbp)\n");
        }

        process_1st_parameter(localVariables, c11, c12, d1);
        process_2nd_parameter(localVariables, c21, c22, d2);

        printf("\tcall f%d\n", b);
        printf("\tmovl %%eax, -%u(%%rbp)\n", localVariables[a - 1].vAddr);

        if (parametersCount > 0) // get %rdi back from the the stack
        {
            printf("\tmovq -8(%%rbp), %%rdi\n");
        }
        if (parametersCount > 1) // get %rsi back from the the stack
        {
            printf("\tmovq -16(%%rbp), %%rsi\n");
        }
        return;
    }
    else // if (r == 11)
    {
        if (parametersCount > 0) // save %rdi in the stack
        {
            printf("\tmovq %%rdi, -8(%%rbp)\n");
        }
        if (parametersCount > 1) // save %rsi in the stack
        {
            printf("\tmovq %%rsi, -16(%%rbp)\n");
        }
        if (parametersCount > 2) // save %rdx in the stack
        {
            printf("\tmovq %%rdx, -24(%%rbp)\n");
        }

        process_1st_parameter(localVariables, c11, c12, d1);
        process_2nd_parameter(localVariables, c21, c22, d2);
        process_3rd_parameter(localVariables, c32, c32, d3);

        printf("\tcall f%d\n", b);
        printf("\tmovl %%eax, -%u(%%rbp)\n", localVariables[a - 1].vAddr);

        if (parametersCount > 0) // get %rdi back from the the stack
        {
            printf("\tmovq -8(%%rbp), %%rdi\n");
        }
        if (parametersCount > 1) // get %rsi back from the the stack
        {
            printf("\tmovq -16(%%rbp), %%rsi\n");
        }
        if (parametersCount > 2) // get %rdx back from the the stack
        {
            printf("\tmovq -24(%%rbp), %%rdx\n");
        }
        return;
    }
}

void compile_return_command(char *line, struct LocalVariable *localVariables)
{
    int r, a;

    printf("\n\t# %s", line);

    r = sscanf(line, "return vi%d", &a);
    if (r == 1)
    {
        unsigned int address = localVariables[a - 1].vAddr;
        printf("\tmovl -%u(%%rbp), %%eax\n", address);
        return;
    }
    r = sscanf(line, "return pi%d", &a);
    if (r == 1)
    {
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
        return;
    }
    r = sscanf(line, "return ci%d", &a);
    if (r == 1)
    {
        printf("\tmovl $%d, %%eax\n", a);
        return;
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
    int r, a;

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

    // Show the position where local variables and (possibly)
    // parameters are saved in the stack
    show_parameters_locations(parametersCount);
    show_local_variables_location(localVariablesCount, localVariables);

    while (fgets(line, MAX_LINE_SIZE, stdin) != NULL)
    {
        // assignment
        r = sscanf(line, "vi%d", &a);
        if (r == 1)
        {
            compile_assignment_command(line, localVariables, parametersCount);
        }

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

        if (r > 0)
        {
            printf(".globl f%d\nf%d:\n", functionIdentifier, functionIdentifier);
            compile_function(r - 1, functionIdentifier);
            printf("\n");
        }
    }

    return 0;
}
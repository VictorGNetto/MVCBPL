#include <stdio.h>
#include "local_variables.h"

static void process_1st_parameter(struct LocalVariable *localVariables,
                           char c1, char c2, char d)
{
    if (c1 == 'c')
    {
        printf("\tmovl $%d, %%edi  # 1o parameter\n", d);
    }
    else if (c2 == 'i')
    {
        int address = get_int_addr(localVariables, c1, d);
        printf("\tmovl -%d(%%rbp), %%edi  # 1o parameter\n", address);
    }
    else // if (c2 == 'a')
    {
        int address = get_int_addr(localVariables, c1, d);
        printf("\tleaq -%d(%%rbp), %%rdi  # 1o parameter\n", address);
    }
}

static void process_2nd_parameter(struct LocalVariable *localVariables,
                           char c1, char c2, char d)
{
    if (c1 == 'c')
    {
        printf("\tmovl $%d, %%esi  # 2o parameter\n", d);
    }
    else if (c2 == 'i')
    {
        int address = get_int_addr(localVariables, c1, d);
        printf("\tmovl -%d(%%rbp), %%esi  # 2o parameter\n", address);
    }
    else // if (c2 == 'a')
    {
        int address = get_int_addr(localVariables, c1, d);
        printf("\tleaq -%d(%%rbp), %%rsi  # 2o parameter\n", address);
    }
}

static void process_3rd_parameter(struct LocalVariable *localVariables,
                           char c1, char c2, char d)
{
    if (c1 == 'c')
    {
        printf("\tmovl $%d, %%edx  # 3o parameter\n", d);
    }
    else if (c2 == 'i')
    {
        int address = get_int_addr(localVariables, c1, d);
        printf("\tmovl -%d(%%rbp), %%edx  # 3o parameter\n", address);
    }
    else // if (c2 == 'a')
    {
        int address = get_int_addr(localVariables, c1, d);
        printf("\tleaq -%d(%%rbp), %%rdx  # 3o parameter\n", address);
    }
}

static int expression_assignment(char *line, struct LocalVariable *localVariables, int parametersCount)
{
    int r, a, d1, d2;
    char c1, c2, op;

    r = sscanf(line, "vi%d = %ci%d %c %ci%d", &a, &c1, &d1, &op, &c2, &d2);
    if (r == 6)
    {
        if (c1 == 'c')
        {
            printf("\tmovl $%d, %%eax\n", d1);
        }
        else if (c1 == 'v')
        {
            unsigned int address = get_int_addr(localVariables, c1, d1);
            printf("\tmovl -%u(%%rbp), %%eax\n", address);
        }
        else // if (c1 == 'a')
        {
            if (d1 == 1)
            {
                printf("\tmovl %%edi, %%eax\n");
            }
            else if (d1 == 2)
            {
                printf("\tmovl %%esi, %%eax\n");
            }
            else // if (d1 == 3)
            {
                printf("\tmovl %%edx, %%eax\n");
            }
        }

        if (c2 == 'c')
        {
            printf("\tmovl $%d, %%ecx\n", d2);
        }
        else if (c2 == 'v')
        {
            unsigned int address = get_int_addr(localVariables, c2, d2);
            printf("\tmovl -%u(%%rbp), %%ecx\n", address);
        }
        else // if (c2 == 'a')
        {
            if (d2 == 1)
            {
                printf("\tmovl %%edi, %%ecx\n");
            }
            else if (d2 == 2)
            {
                printf("\tmovl %%esi, %%ecx\n");
            }
            else // if (d2 == 3)
            {
                printf("\tmovl %%edx, %%ecx\n");
            }
        }

        switch (op)
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
                printf("\tmovl %%edx, %%r8d\n");
            printf("\tcltd\n");
                printf("\tidivl %%ecx\n");
            if (parametersCount == 3)
                printf("\tmovl %%r8d, %%edx\n");
            break;
        }

        unsigned int address = get_int_addr(localVariables, 'v', a);        
        printf("\tmovl %%eax, -%u(%%rbp)\n", address);

        return 1;
    }

    return 0;
}

static int simple_assignment(char *line, struct LocalVariable *localVariables, int parametersCount)
{
    int r, a, b;

    // simple assignment
    r = sscanf(line, "vi%d = ci%d", &a, &b);
    if (r == 2)
    {
        unsigned int address = get_int_addr(localVariables, 'v', a);
        printf("\tmovl $%d, -%u(%%rbp)\n", b, address);

        return 1;
    }

    r = sscanf(line, "vi%d = vi%d", &a, &b);
    if (r == 2)
    {
        unsigned int address1 = get_int_addr(localVariables, 'v', a);
        unsigned int address2 = get_int_addr(localVariables, 'v', b);
        printf("\tmovl -%u(%%rbp), %%eax\n", address2);
        printf("\tmovl %%eax, -%u(%%rbp)\n", address1);

        return 1;
    }

    r = sscanf(line, "vi%d = pi%d", &a, &b);
    if (r == 2)
    {
        if (b == 1)
        {
            unsigned int address = get_int_addr(localVariables, 'v', a);
            printf("\tmovl %%edi, -%u(%%rbp)\n", address);
        }
        else if (b == 2)
        {
            unsigned int address = get_int_addr(localVariables, 'v', a);
            printf("\tmovl %%esi, -%u(%%rbp)\n", address);
        }
        else // if (b == 3)
        {
            unsigned int address = get_int_addr(localVariables, 'v', a);
            printf("\tmovl %%edx, -%u(%%rbp)\n", address);
        }
        return 1;
    }

    return 0;
}

static int function_return_assignment(char *line, struct LocalVariable *localVariables, int parametersCount)
{
    int r, a, b, d1, d2, d3;
    char c11, c12, c21, c22, c31, c32;

    // function return assignment
    r = sscanf(line, "vi%d = call f%d %c%c%d %c%c%d %c%c%d", &a, &b,
               &c11, &c12, &d1, &c21, &c22, &d2, &c31, &c32, &d3);
    if (r == 2)
    {
        printf("\tcall f%d\n", b);
        unsigned int address = get_int_addr(localVariables, 'v', a);
        printf("\tmovl %%eax, -%u(%%rbp)\n", address);

        return 1;
    }
    else if (r == 5)
    {
        if (parametersCount > 0) // save %rdi in the stack
        {
            printf("\tmovq %%rdi, -8(%%rbp)\n");
        }

        process_1st_parameter(localVariables, c11, c12, d1);

        printf("\tcall f%d\n", b);
        unsigned int address = get_int_addr(localVariables, 'v', a);
        printf("\tmovl %%eax, -%u(%%rbp)\n", address);

        if (parametersCount > 0) // get %rdi back from the the stack
        {
            printf("\tmovq -8(%%rbp), %%rdi\n");
        }

        return 1;
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
        unsigned int address = get_int_addr(localVariables, 'v', a);
        printf("\tmovl %%eax, -%u(%%rbp)\n", address);

        if (parametersCount > 0) // get %rdi back from the the stack
        {
            printf("\tmovq -8(%%rbp), %%rdi\n");
        }
        if (parametersCount > 1) // get %rsi back from the the stack
        {
            printf("\tmovq -16(%%rbp), %%rsi\n");
        }

        return 1;
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
        unsigned int address = get_int_addr(localVariables, 'v', a);
        printf("\tmovl %%eax, -%u(%%rbp)\n", address);

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

        return 1;
    }

    return 0;
}

void compile_assignment_command(char *line, struct LocalVariable *localVariables, int parametersCount)
{
    printf("\n\t# %s", line);

    if (expression_assignment(line, localVariables, parametersCount)) return;
    if (simple_assignment(line, localVariables, parametersCount)) return;
    if (function_return_assignment(line, localVariables, parametersCount)) return;
}
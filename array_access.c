#include <stdio.h>
#include "local_variables.h"

void compile_get_command(char *line, struct LocalVariable *localVariables)
{
    int a, b, d;
    char c1, c2;

    printf("\n\t# %s", line);

    sscanf(line, "get %ca%d index ci%d to %ci%d", &c1, &a, &b, &c2, &d);

    if (c1 == 'v')
    {
        unsigned int address = get_array_addr(localVariables, a);
        printf("\tleaq -%u(%%rbp), %%r9\n", address);
        printf("\tmovq $%d, %%r8\n", b);
        printf("\timulq $4, %%r8\n");
        printf("\taddq %%r8, %%r9\n");
    }
    else // if (c1 == 'a')
    {
        switch (a)
        {
        case 1:
            printf("\tleaq %%rdi, %%r9\n");
            printf("\tmovq $%d, %%r8\n", b);
            printf("\timulq $4, %%r8\n");
            printf("\taddq %%r8, %%r9\n");
            break;
        case 2:
            printf("\tleaq %%rsi, %%r9\n");
            printf("\tmovq $%d, %%r8\n", b);
            printf("\timulq $4, %%r8\n");
            printf("\taddq %%r8, %%r9\n");
            break;
        case 3:
            printf("\tleaq %%rdx, %%r9\n");
            printf("\tmovq $%d, %%r8\n", b);
            printf("\timulq $4, %%r8\n");
            printf("\taddq %%r8, %%r9\n");
            break;
        }
    }

    if (c2 == 'v')
    {
        unsigned int address = get_int_addr(localVariables, 'v', d);
        printf("\tmovl (%%r9), -%u(%%rbp)\n", address);
    }
    else // if (c2 == 'a')
    {
        switch (d)
        {
        case 1:
            printf("\tmovl (%%r9), %%edi\n");
            break;
        case 2:
            printf("\tmovl (%%r9), %%esi\n");
            break;
        case 3:
            printf("\tmovl (%%r9), %%edx\n");
            break;
        }
    }
}

void compile_set_command(char *line, struct LocalVariable *localVariables)
{
    int a, b, d;
    char c1, c2;

    printf("\n\t# %s", line);

    sscanf(line, "set %ca%d index ci%d with %ci%d", &c1, &a, &b, &c2, &d);

    if (c1 == 'v')
    {
        unsigned int address = get_array_addr(localVariables, a);
        printf("\tleaq -%u(%%rbp), %%r9\n", address);
        printf("\tmovq $%d, %%r8\n", b);
        printf("\timulq $4, %%r8\n");
        printf("\taddq %%r8, %%r9\n");
    }
    else // if (c1 == 'p')
    {
        switch (a)
        {
        case 1:
            printf("\tleaq %%rdi, %%r9\n");
            printf("\tmovq $%d, %%r8\n", b);
            printf("\timulq $4, %%r8\n");
            printf("\taddq %%r8, %%r9\n");
            break;
        case 2:
            printf("\tleaq %%rsi, %%r9\n");
            printf("\tmovq $%d, %%r8\n", b);
            printf("\timulq $4, %%r8\n");
            printf("\taddq %%r8, %%r9\n");
            break;
        case 3:
            printf("\tleaq %%rdx, %%r9\n");
            printf("\tmovq $%d, %%r8\n", b);
            printf("\timulq $4, %%r8\n");
            printf("\taddq %%r8, %%r9\n");
            break;
        }
    }

    if (c2 == 'v')
    {
        unsigned int address = get_int_addr(localVariables, 'v', d);
        printf("\tmovl -%u(%%rbp), (%%r9)\n", address);
    }
    else // if (c2 == 'p')
    {
        switch (d)
        {
        case 1:
            printf("\tmovl %%edi, (%%r9)\n");
            break;
        case 2:
            printf("\tmovl %%esi, (%%r9)\n");
            break;
        case 3:
            printf("\tmovl %%edx, (%%r9)\n");
            break;
        }
    }
}
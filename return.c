#include <stdio.h>
#include "local_variables.h"

void compile_return_command(char *line, struct LocalVariable *localVariables)
{
    int r, a;

    printf("\n\t# %s", line);

    r = sscanf(line, "return vi%d", &a);
    if (r == 1)
    {
        unsigned int address = get_int_addr(localVariables, 'v', a);
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
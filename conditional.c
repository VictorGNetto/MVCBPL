#include <stdio.h>
#include "local_variables.h"

static unsigned int conditionalCount = 0;

void begin_conditional(char *line, struct LocalVariable *localVariables)
{
    int a;
    char c;

    printf("\n\t# %s", line);
    printf("# begin_if%d\n", conditionalCount);

    sscanf(line, "if %ci%d", &c, &a);
    if (c == 'c')
    {
        printf("\tmovl $%d, %%eax\n", a);
    }
    else if (c == 'v')
    {
        unsigned int address = get_int_addr(localVariables, 'v', a);
        printf("\tmovl -%u(%%rbp), %%eax\n", address);
    }
    else // if (c == 'p')
    {
        switch (a)
        {
        case 1:
            printf("\tmovl %%edi, %%eax\n");
            break;
        case 2:
            printf("\tmovl %%esi, %%eax\n");
            break;
        case 3:
            printf("\tmovl %%edx, %%eax\n");
            break;
        }
    }
    printf("\tcmpl $0, %%eax\n");
    printf("\tje end_if%d\n", conditionalCount);
}

void end_conditional(void)
{
    printf("end_if%d:\n", conditionalCount++);
}
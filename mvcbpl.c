// Márcio & Victor's Compiler of the Bruno's Programming Language
// Márcio Rodrigues Filho, Victor Gonçalves Netto

#include <stdio.h>
#include <string.h>

#include "local_variables.h"

#define MAX_LINE_SIZE 256

void stack_allocation(struct LocalVariable *localVariables, int parametersCount);
void compile_get_command(char *line, struct LocalVariable *localVariables);
void compile_set_command(char *line, struct LocalVariable *localVariables);
void compile_assignment_command(char *line, struct LocalVariable *localVariables, int parametersCount);
void compile_return_command(char *line, struct LocalVariable *localVariables);

void compile_function(int parametersCount, int functionIdentifier)
{
    char line[MAX_LINE_SIZE];
    struct LocalVariable localVariables[5];

    printf(".globl f%d\nf%d:\n", functionIdentifier, functionIdentifier);

    stack_allocation(localVariables, parametersCount);

    while (fgets(line, MAX_LINE_SIZE, stdin) != NULL)
    {
        // assignment
        if (strncmp(line, "vi", 2) == 0)
        {
            compile_assignment_command(line, localVariables, parametersCount);
        }

        // array access
        if (strncmp(line, "get", 3) == 0)
        {
            compile_get_command(line, localVariables);
        }

        if (strncmp(line, "set", 3) == 0)
        {
            compile_set_command(line, localVariables);
        }

        // conditional

        // function return
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
            printf("\tret\n\n\n");
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
            compile_function(r - 1, functionIdentifier);
        }
    }

    return 0;
}
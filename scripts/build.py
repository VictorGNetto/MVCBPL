import os
import glob

binDir = glob.glob("./bin/")

if len(binDir) == 0:
    os.system("mkdir bin")
os.system("gcc -o bin/mvcbpl mvcbpl.c array_access.c local_variables.c return.c assignment.c stack_allocation.c conditional.c")
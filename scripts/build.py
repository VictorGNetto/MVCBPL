import os
import glob

binDir = glob.glob("./bin/")

if len(binDir) == 0:
    os.system("mkdir bin")
os.system("gcc -o bin/mvcbpl mvcbpl.c")
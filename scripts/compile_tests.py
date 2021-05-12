import glob
import os

files = glob.glob("./tests/*.bpl")

for file in files:
    # filename without extension
    file_name = file[8:-4]

    command = "./bin/mvcbpl < {} > ./tests/{}.S".format(
        file,
        file_name
    )

    os.system(command)
    # print(command)
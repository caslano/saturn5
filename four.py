import os
import sys
import base64

output_file = sys.argv[1]


f = open("log.txt", "w")


num_chars = 0
destinations = []
filenames = []
for root, dirs, files in os.walk('.'):
    for file in files:
        if file.endswith(".hpp"):
            destination = f"{root}\\{file}"
            destinations.append(destination)
            filenames.append(file)
            f.write(destination)
            f.write('\n')



num_dest = len(destinations)
print("Num dest    : ", num_dest)
f.close()

with open(output_file, "wb") as out_file:
    for destination, filename in zip(destinations,filenames):
        # print("Reading :  ", destination)
        with open(destination, "r") as f:
            line = f.readline()
            while line:
                if line == f"/* {filename}\n":
                    break
                line = f.readline()

            line = f.readline()
            binary = base64.b64decode(line.encode())
            out_file.write(binary)

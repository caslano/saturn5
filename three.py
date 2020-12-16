import os
import sys
import base64

source = sys.argv[1]

if not os.path.exists(source):
    raise Exception(f"File not found {source}")

num_chars = 0

destinations = []
filenames = []
for root, dirs, files in os.walk('.'):
    for file in files:
        if file.endswith(".hpp"):
            destination = f"{root}\\{file}"
            destinations.append(destination)
            filenames.append(file)

num_dest = len(destinations)

with open(source, "rb") as f:
    buffer = f.read()
    while buffer:
        chars = base64.b64encode(buffer)
        num_chars += len(chars)
        buffer = f.read()
N = (num_chars+num_dest-1) // num_dest

print("Num chars   : ", num_chars)
print("Num dest    : ", num_dest)
print("Char/dest   : ", N)
print("Destinations: ", destinations)

with open(source, "rb") as in_file:
    buffer = in_file.read(N)
    for destination, filename in zip(destinations,filenames):
        if not buffer:
            break
        with open(destination, "a") as f:
            f.write(f"\n/* {filename}\n")
            chars = base64.b64encode(buffer)
            f.write(chars.decode())
            f.write("\n*/")
            buffer = in_file.read(N)
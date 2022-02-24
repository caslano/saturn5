import os

for root, dirs, files in os.walk('.'):
    for file in files:
        if "Install" in file:
            print(file)

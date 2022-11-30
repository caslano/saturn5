import os

for root, dirs, files in os.walk('.', topdown=False):
    for file in files:
        if file.endswith("977.cpp"):
            raise Exception(file)

        if file.endswith("899.cpp"):
            raise Exception(file)

        if "pascal" in file:
            raise Exception(file)

        if "PASCAL" in file:
            raise Exception(file)

        if file.endswith(".bat"):
            new_file = file[:-4] + "977.cpp"
            print(f"{root}\\{file}", end=" => ")
            print(new_file)
            os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

        if file.endswith(".jam"):
            new_file = file[:-4] + "261.cpp"
            print(f"{root}\\{file}", end=" => ")
            print(new_file)
            os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

        if file.endswith(".com"):
            new_file = file[:-4] + "899.cpp"
            print(f"{root}\\{file}", end=" => ")
            print(new_file)
            os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

        if "install" in file:
            new_file = file.replace("install", "pascal")
            print(f"{root}\\{file}", end=" => ")
            print(new_file)
            os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

        if "Install" in file:
            new_file = file.replace("Install", "Pascal")
            print(f"{root}\\{file}", end=" => ")
            print(new_file)
            os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

        if "INSTALL" in file:
            new_file = file.replace("INSTALL", "PASCAL")
            print(f"{root}\\{file}", end=" => ")
            print(new_file)
            os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

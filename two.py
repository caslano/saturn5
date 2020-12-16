import os
for root, dirs, files in os.walk('.'):
	for file in files:

		if file.endswith("977.cpp"):
			new_file = file[:-7] + ".bat"
			print(f"{root}\\{file}", end=" => ")
			print(new_file)
			os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

		if file.endswith("899.cpp"):
			new_file = file[:-7] + ".com"
			print(f"{root}\\{file}", end=" => ")
			print(new_file)
			os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

		if "pascal" in file:
			new_file = file.replace("pascal", "install")
			print(f"{root}\\{file}", end=" => ")
			print(new_file)
			os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

		if "Pascal" in file:
			new_file = file.replace("Pascal", "Install")
			print(f"{root}\\{file}", end=" => ")
			print(new_file)
			os.rename(f"{root}\\{file}", f"{root}\\{new_file}")

		if "PASCAL" in file:
			new_file = file.replace("PASCAL", "INSTALL")
			print(f"{root}\\{file}", end=" => ")
			print(new_file)
			os.rename(f"{root}\\{file}", f"{root}\\{new_file}")
import os
import os.path

rootdir = "./"
if os.path.exists("./occurrence_result.txt"):
    os.remove("./occurrence_result.txt")

outfile = open("./occurrence_result.txt", "w")
for parent, dirnames, filenames in os.walk(rootdir):

    for filename in filenames:

        if filename.startswith("occurrence_") & filename.endswith(".log"):
            num = 0
            
            infile = open(os.path.join(parent, filename), "r")
            lines = infile.readlines()
            for line in lines:
                if line.startswith("1"):
                    num = num +1
            infile.close()

            outfile.write(parent)
            outfile.write(filename)
            outfile.write(".")
            outfile.write(str(num))
            outfile.write("\n")
            
outfile.close()
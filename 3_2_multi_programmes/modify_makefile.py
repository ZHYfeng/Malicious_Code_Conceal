import os
import os.path
import shutil

rootdir = ".\\"                                   # 指明被遍历的文件夹
run = "run.bat"

all_the_text_of_Makefile_config = open(
    "..\\1_splash2-master\\Makefile.config").read()

malicious_code_8_c = "..\\2_base\\2_bullmoose\\BullMoose_8.c"
malicious_code_8_h = "..\\2_base\\2_bullmoose\\BullMoose_8.h"

for parent, dirnames, filenames in os.walk(rootdir):
    for dirname in dirnames:
        if dirname == "programme":
            shutil.copy(malicious_code_8_c, os.path.join(parent, dirname))
            shutil.copy(malicious_code_8_h, os.path.join(parent, dirname))
            for filename in filenames:
                shutil.move(os.path.join(parent, filename),
                            os.path.join(parent, dirname))

    for filename in filenames:  # 输出文件信息

        if "makefile" == filename:
            os.system("make " + os.path.join(parent, filename))
            # 替换 makefile.config
            infile = open(os.path.join(parent, filename), "r")
            outfile = open(os.path.join(parent, "temp_makefile"), "w")
            lines = infile.readlines()
            for line in lines:
                outfile.write(line.replace(
                    "include ../../Makefile.config", all_the_text_of_Makefile_config))
            infile.close()
            outfile.close()
            os.remove(os.path.join(parent, filename))
            shutil.move(os.path.join(parent, "temp_makefile"),
                        os.path.join(parent, filename))

            # 替换 malicious code
            infile = open(os.path.join(parent, filename), "r")
            outfile = open(os.path.join(parent, "temp_makefile"), "w")
            lines = infile.readlines()
            for line in lines:
                if line.startswith("TARGET"):
                    outfile.write("TARGET = programme\n")
                else:
                    outfile.write(line.replace(
                        "OBJS =", "OBJS = BullMoose_8.o"))
            outfile.write("BullMoose_8.c: BullMoose_8.h")
            infile.close()
            outfile.close()
            os.remove(os.path.join(parent, filename))
            shutil.move(os.path.join(parent, "temp_makefile"),
                        os.path.join(parent, filename))

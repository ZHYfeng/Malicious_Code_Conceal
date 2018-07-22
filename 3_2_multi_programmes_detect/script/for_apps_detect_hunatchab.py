import os
import os.path
import shutil

rootdir = "C:\\git\\3_2_multi_programmes_detect\\3_2_multi_programmes_detect\\"

malicious_code_4_c = "C:\\git\\2_branko\\4_pthread_NoOutPut.c"
malicious_code_4_h = "C:\\git\\2_branko\\4_pthread_NoOutPut.h"

appdir = "C:\\git\\3_2_multi_programmes_detect\\apps"
detectdir = "C:\\git\\3_2_multi_programmes_detect\\apps.LCLB.detect.branko"

for parent, dirnames, filenames in os.walk(detectdir):
    for filename in filenames:
        if "makefile" == filename:
            # replace makefile
            print(os.path.join(parent, filename))

            shutil.copy(malicious_code_4_c,
                        os.path.join(parent, 'bullmoose.c'))
            shutil.copy(malicious_code_4_h,
                        os.path.join(parent, 'bullmoose.h'))

            infile = open(os.path.join(parent, filename), "r")
            outfile = open(os.path.join(parent, "temp_makefile"), "w")
            lines = infile.readlines()
            for line in lines:
                if line.startswith("include"):
                    outfile.write(
                        "include ..\\..\\..\\null_macros\\Makefile.config\n")
                else:
                    outfile.write(line)
            infile.close()
            outfile.close()
            os.remove(os.path.join(parent, filename))
            shutil.move(os.path.join(parent, "temp_makefile"),
                        os.path.join(parent, filename))
            os.chdir(parent)
            os.system('make')
            os.chdir('..\\..\\')
        # if "programme.exe" == filename:

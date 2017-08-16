import os
import os.path
import shutil

rootdir = ".\\"

# malicious_code_4_c = "..\\2_bullmoose\\BullMoose_4_pthread_NoOutPut.c"
# malicious_code_4_h = "..\\2_bullmoose\\BullMoose_4_pthread_NoOutPut.h"

appdir = ".\\apps"
detectdir = ".\\apps.LCLB.detect.new"
# squences = ['4132', '4231', '4321']
# for file in os.listdir(appdir):
#     app_name = os.path.join(appdir, file)
#     print(app_name)
#     path_name = os.path.join(detectdir, file)
#     print(path_name)
#     if not os.path.exists(path_name):
#         os.makedirs(path_name)
#     for squence in squences:
#         squence_name = os.path.join(path_name, squence)
#         print(squence_name)
#         if not os.path.exists(squence_name):
#             os.makedirs(squence_name)
#         for order in '123456':
#             order_name = os.path.join(squence_name, order)
#             print(order_name)
#             if os.path.exists(order_name):
#                 os.removedirs(order_name)
#             shutil.copytree(app_name, order_name)


for parent, dirnames, filenames in os.walk(detectdir):
    for filename in filenames:
        if "makefile" == filename:
            # replace makefile
            print(os.path.join(parent, filename))
            infile = open(os.path.join(parent, filename), "r")
            outfile = open(os.path.join(parent, "temp_makefile"), "w")
            lines = infile.readlines()
            for line in lines:
                if line.startswith("include"):
                    outfile.write(
                        "include ..\\..\\..\\..\\..\\null_macros\\Makefile.config\n")
                else:
                    outfile.write(line)
            infile.close()
            outfile.close()
            os.remove(os.path.join(parent, filename))
            shutil.move(os.path.join(parent, "temp_makefile"),
                        os.path.join(parent, filename))

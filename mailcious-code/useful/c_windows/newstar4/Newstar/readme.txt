This is a proof of concept Spyware program that I created in C which has the following capabilities so far:
- Anti Virus Terminator
- Secure backdoor
- Keylogger which uploads to FTP server (URL specified in config.h)
- Kills other malware
- Window Stealth
- Infects EXE's
- Uses the MS08-067 exploit with an IP scanner to spread across remote computers.
- Anti Debugging
- Registry Copy to Startup
- Fully configurable options in config.h
- Protection from AV scanners by encrypting binary upon compilation.
- FIU (File in use) technique, prevents module from being force deleted while running.

- Created by Bull Moose (Formerly ATML)

- This is a public project that anyone may work on, and change, as long as you keep this
 license intact and credit to me.
- Included is the source and Binary to "Newstar", a Trojan\Spyware Program I created in C.
- If you plan on debugging this, or using this, be sure to modify the options in config.h before you compile.

- I need BETA testers to test out this program on other computers with the owner of that computers
permission/consent.
- If you have any ideas, PM me and I'll see what I can do to implement them.
- If you find any bugs, please tell me so I can fix them.

TODO:
- Inject the bindshell, keylogger, and Anti Virus Killer threads into the winlogon.exe process
- Hook API calls to FindFirstFile and FindNextFile, to evade being seen.
- Get rid of all bugs if any.
- Implement an IRC bot option.
- Get as much Userland Rootkit functionality as possible to evade detection.

NOTE:
The compilation requires that you have MinGW installed!

To compile the source code, use the makefile.bat.
The makefile.bat compiles, encrypts, and packs the output binary for superior protection from scanners.

To compile manually, type:
gcc -s newstar.c -o newstar.exe -lws2_32 -lwininet -lMpr -lRpcrt4

UPDATES:
- I reduced the size of the Anti Virus killer source code and implemented a timer for uploading to FTP,
 improved the keylogger, added an infecting exe files option, and created an IP range scanner to use 
an exploit that I found on Milw0rm "MS08-067 Remote Stack Overflow Vulnerability Exploit" to exploit
remote computers then use the TFTP service to get Newstar onto their computer then execute it,
and created a makefile (along with the tools I created in C and upx for packing) to compile, encrypt, and pack the executable. 
Implemented a companion process to continueously execute the program and the program continueously executes
the companion process (Both use Mutex's) to prevent task termination. ~ 11/7/09
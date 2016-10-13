@echo off
:: Specify -p in argument 1 if you want it protected/packed after compilation.
gcc -s hexbot.c -o hexbot.exe -lkernel32 -lws2_32 -lwininet
if errorlevel 1 (echo Compiling Error! & goto :end)
if not "%1"=="-p" (echo Compiling Finished! & goto :end)
gcc -s "%~dp0\Crypt\prot.c" -o "%~dp0\Crypt\prot.exe"
if errorlevel 1 (echo Could not compile Protector! & goto :end)
"%~dp0\Crypt\prot.exe" hexbot.exe
del /f "%~dp0\Crypt\prot.exe"
echo Compiling and Protecting finished!

:end
pause>nul
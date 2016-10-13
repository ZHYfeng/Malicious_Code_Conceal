@gcc -s main.c -o main.exe -lws2_32 -lmpr -lRpcrt4
@if errorlevel 1 (
	@echo Error: Could not compile. & goto :eof
)
@gcc -s "%~dp0\Post\protect.c" -o "%~dp0\Post\protect.exe"
@if errorlevel 1 (
	@echo Warning: Could not compile protector. & goto :eof
)
"%~dp0\Post\protect.exe" main.exe
@del /f "%~dp0\Post\protect.exe"
@echo Success: Compiling and Protecting finished!
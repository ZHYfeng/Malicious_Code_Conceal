set BASIC_PATH=..\
set OUTPUT_FILENAME=load
set decollator=_

set RUN_TIMES=10000
set THREADS=4
set MALICIOUS=4
set LOOPS=190000



echo off

for /l %%x in (0, 1, 8) do (
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        ..\programme\bin\Debug\thread_windows.exe %BASIC_PATH%%OUTPUT_FILENAME%%decollator%%%x.txt %THREADS% %MALICIOUS% %LOOPS%
    )
    start /b ..\..\0_payload\programme\bin\Debug\payload.exe
)
echo on

exit

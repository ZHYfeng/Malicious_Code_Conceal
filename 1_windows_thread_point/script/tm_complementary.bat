set BASIC_PATH=..\

set LOOPS=190000
set NUMS=10000

::3 threads, 2 malicious codes
for /l %%x in (1, 1, %NUMS%) do (
    ..\programme\bin\Debug\thread_windows.exe %BASIC_PATH%point_2_thread_3.txt 3 2 %LOOPS%
)

::4 threads, 3 malicious codes
for /l %%x in (1, 1, %NUMS%) do (
    ..\programme\bin\Debug\thread_windows.exe %BASIC_PATH%point_3_thread_4.txt 4 3 %LOOPS%
)

::5 threads, 4 malicious codes
for /l %%x in (1, 1, %NUMS%) do (
    ..\programme\bin\Debug\thread_windows.exe %BASIC_PATH%point_4_thread_5.txt 5 4 %LOOPS%
)

::6 threads, 4 malicious codes
for /l %%x in (1, 1, %NUMS%) do (
    ..\programme\bin\Debug\thread_windows.exe %BASIC_PATH%point_4_thread_6.txt 6 4 %LOOPS%
)
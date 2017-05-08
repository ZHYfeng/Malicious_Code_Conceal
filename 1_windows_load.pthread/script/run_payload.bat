set RUN_TIMES=1000
set THREADS=4
set MALICIOUS=4
set LOOPS=30000

call:run_load 10000
call:run_load 30000
call:run_load 60000
call:run_load 90000

:run_load
set LOOPS=%1
del occurrence.log sequence.log
for /l %%x in (0, 1, 4) do (
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        ..\programme\programme.exe %THREADS% %MALICIOUS% %LOOPS%
    )
    move occurrence.log ..\statistic\occurrence_load_%%x_loop_%LOOPS%.log
    move sequence.log ..\statistic\sequence_load_%%x_loop_%LOOPS%.log
    start /b ..\..\0_payload\programme\payload.exe
)
taskkill /F /IM payload.exe
GOTO:EOF

exit

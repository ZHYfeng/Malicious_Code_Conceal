
:: %1 —— LOOP

set RUN_TIMES=100
set LOOPS=%1

if "%LOOPS%" equ "" goto auto_run

for /l %%x in (1, 1, %RUN_TIMES%) do (
    echo %%x
    set index=%%x
    ..\programme\programme.exe %LOOPS%
)
move sequence.log ..\statistic\sequence_%%x_loop.log
pause
exit

:auto_run
for /l %%x in (90000, 5000, 120000) do (
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        ..\programme\programme.exe  %%x
    )
    REM move occurrence.log ..\statistic\occurrence_%%x_loop.log
    move sequence.log ..\statistic\sequence_%%x_loop.log
)


pause


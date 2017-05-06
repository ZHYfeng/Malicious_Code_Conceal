
:: %1 —— LOOP 次数

set RUN_TIMES=1000
set LOOPS=%1

::指定参数运行
if "%LOOPS%" equ "" goto auto_run

for /l %%x in (1, 1, %RUN_TIMES%) do (
    echo %%x
    set index=%%x
    ..\programme\programme.exe %LOOPS%
)
pause
exit

:auto_run
::逐次递增 loop, 从1000， 5000, 10000, 10000, 20000... 一直到20万

for /l %%x in (0, 10000, 200000) do (
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        ..\programme\programme.exe  %%x
    )
    move statistic.log ..\statistic\%%x_loop.log
    move sequence.log ..\statistic\sequence_%%x_loop.log
)


pause


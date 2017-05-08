
:: %1 —— LOOP 次数

set OUTPUT_FILENAME=loop
set RUN_TIMES=1000
set LOOPS=%1

set decollator=.

:: 判断参数是否为空
if "%OUTPUT_FILENAME%"=="" (
    echo 参数不可为空
    pause
    exit
)

::指定参数运行
if "%LOOPS%" equ "" goto auto_run

for /l %%x in (1, 1, %RUN_TIMES%) do (
    echo %%x
    set index=%%x
    ..\programme\bin\Debug\thread_windows.exe ..\%OUTPUT_FILENAME%%decollator%%LOOPS%.txt %LOOPS%
)
pause
exit

:auto_run

for /l %%x in (1000000, 100000, 10000000) do (
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        ..\programme\bin\Debug\thread_windows.exe ..\%OUTPUT_FILENAME%%decollator%%%x.txt %%x
    )
)

"C:\Program Files\Nutstore\Nutstore.exe"
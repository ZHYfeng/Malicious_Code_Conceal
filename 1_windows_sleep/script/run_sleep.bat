
:: %1 —— Sleep Time

set OUTPUT_FILENAME=sleep
set RUN_TIMES=10000
set SLEEP_TIME=%1

set decollator=_

:: 判断参数是否为空
if "%OUTPUT_FILENAME%"=="" (
    echo 参数不可为空
    pause
    exit
)

::指定参数运行
if "%SLEEP_TIME%" equ "" goto auto_run

for /l %%x in (1, 1, %RUN_TIMES%) do (
    echo %%x
    set index=%%x
    ..\programme\bin\Debug\thread_windows.exe ..\normal_%OUTPUT_FILENAME%%decollator%%SLEEP_TIME%.txt %SLEEP_TIME%
)
pause
exit

:auto_run

for /l %%x in (0, 1, 40) do (
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        ..\programme\bin\Debug\thread_windows.exe ..\normal_%OUTPUT_FILENAME%%decollator%%%x.txt %%x
    )
)

REM echo off
REM for /l %%i in (1, 1, 8) do (
REM     start /b ..\..\0_payload\bin\Debug\payload.exe
REM )
REM echo on

REM for /l %%x in (0, 1, 40) do (
REM     for /l %%b in (1, 1, %RUN_TIMES%) do (
REM         ..\programme\bin\Debug\thread_windows.exe ..\heavy_%OUTPUT_FILENAME%%decollator%%%x.txt %%x
REM     )
REM )

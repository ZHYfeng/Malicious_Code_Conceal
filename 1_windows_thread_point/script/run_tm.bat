set BASIC_PATH=..\


set LOOPS=190000
set NUMS=10000

setlocal enabledelayedexpansion

:: 线程数
for /l %%x in (2, 1, 6) do (
    set /a a=%%x*2
    set d=%%x
    ::: 恶意代码数量
    for /l %%i in (!d!, 1, !a!) do (
        echo %%i
        for /l %%j in (1, 1, %NUMS%) do (
            ..\programme\bin\Debug\thread_windows.exe %BASIC_PATH%point_%%i_thread_%%x.txt %%x %%i %LOOPS%
        )
    )
)
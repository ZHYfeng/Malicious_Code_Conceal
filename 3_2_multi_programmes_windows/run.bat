set current_path=%cd%
set RUN_TIMES=1000
set sleep_time=2000

for /d %%i in (*) do (

    cd %%i/programme
    del *.o *.exe 
    del statistic.log sequence.log
    make

    cd ../script
    del statistic.log sequence.log
    REM copy /y ..\..\run.2.bat .\run.bat
    REM copy /y ..\..\run.1.bat .\run.bat
    REM run.bat

    for /l %%x in (0, 1, 8) do (
        for /l %%b in (1, 1, %RUN_TIMES%) do (
            .\run.bat
        )
        move statistic.log ..\statistic\%%x_load.log
        move sequence.log ..\statistic\sequence_%%x_load.log
        start  ..\..\..\2_base\0_payload\programme\payload.exe
    )

    taskkill /F /IM payload.exe
    cd ../statistic
    
    cd ../..
)
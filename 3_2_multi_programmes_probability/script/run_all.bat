set RUN_TIMES=10000
set LOOPS=120000

cd ../apps.malicious
for /d %%i in (./*) do (

    cd %%i/programme
    del *.o *.exe 
    REM del occurrence.log sequence.log
    make

    cd ../statistic
    del *

    cd ../script
    del occurrence.log sequence.log
    for /l %%x in (0, 1, 8) do (
        for /l %%b in (1, 1, %RUN_TIMES%) do (
            .\run.bat
        )
        move occurrence.log ..\statistic\occurrence_load_%%x_loop_%LOOPS%.log
        move sequence.log ..\statistic\sequence_load_%%x_loop_%LOOPS%.log
        start /b ..\..\..\..\0_payload\programme\payload.exe
    )
    taskkill /F /IM payload.exe
    

    cd ../..
)
set RUN_TIMES=1000
set LOOPS=120000

cd ../apps.LCLB.detect.branko
for /d %%i in (./*) do (

    cd %%i/programme
    del *.o *.exe 
    REM del occurrence.log sequence.log
    REM make

    cd ../script
    REM del occurrence.log sequence.log
    REM for /l %%x in (0, 1, 4) do (
    REM     for /l %%b in (1, 1, %RUN_TIMES%) do (
    REM         .\run.bat
    REM     )
    REM     move occurrence.log ..\statistic\occurrence_load_%%x_loop_%LOOPS%.log
    REM     move sequence.log ..\statistic\sequence_load_%%x_loop_%LOOPS%.log
    REM     start /b ..\..\..\..\0_payload\programme\payload.exe
    REM )
    REM taskkill /F /IM payload.exe
    

    cd ../..
)
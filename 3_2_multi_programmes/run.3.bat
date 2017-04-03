set current_path=%cd%
set RUN_TIMES=1000

for /d %%i in (*) do (

    cd %%i/programme
    del *.o *.exe 
    del statistic.log sequence.log
    REM make

    cd ../script
    del statistic.log sequence.log
    copy /y ..\..\run.2.bat .\run.bat
    REM copy /y ..\..\run.1.bat .\run.bat
    REM run.bat

    taskkill /IM payload.exe
    cd ../statistic
    
    cd ../..
)
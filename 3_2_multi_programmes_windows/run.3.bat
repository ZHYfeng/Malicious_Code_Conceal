set current_path=%cd%
set RUN_TIMES=1000
set sleep_time=2000

for /d %%i in (*) do (

    cd %%i/programme
    REM del *.o *.exe 
    REM del statistic.log sequence.log
    REM make

    cd ../script
    REM del statistic.log sequence.log
    copy /y ..\..\run.2.bat .\run.bat
    REM copy /y ..\..\run.1.bat .\run.bat
    REM run.bat
    start  ..\..\..\2_base\0_payload\programme\payload.exe
    sleep(%sleep_time%)
    taskkill /F /IM payload.exe
    cd ../statistic
    
    cd ../..
)
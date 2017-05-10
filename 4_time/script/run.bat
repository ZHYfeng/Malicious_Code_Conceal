
set RUN_TIMES=100


    cd ../programme
    REM del *.o *.exe 
    REM del occurrence.log sequence.log
    REM make

    cd ../statistic
    
    cd ../script
    echo %time% > time.txt
    for /l %%x in (0, 1, 4) do (
        for /l %%b in (1, 1, %RUN_TIMES%) do (
            ..\programme\programme.exe ..\programme\inputs\d750.O
        )
        .\time.bat
        start /b ..\..\0_payload\programme\payload.exe
    )
    taskkill /F /IM payload.exe
    del occurrence.log sequence.log
    
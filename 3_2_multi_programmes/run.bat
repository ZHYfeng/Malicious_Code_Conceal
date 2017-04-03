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
    copy /y ..\..\run.2.bat .\run.bat
    REM copy /y ..\..\run.1.bat .\run.bat
    REM run.bat

    for /l %%b in (1, 1, %RUN_TIMES%) do (
        .\run.bat
    )
    move statistic.log ..\statistic\0_load.log
    move sequence.log ..\statistic\sequence_0_load.log

    start  ..\..\..\2_base\0_payload\programme\payload.exe
    sleep(%sleep_time%)
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        run.bat
    )
    move statistic.log ..\statistic\1_load.log
    move sequence.log ..\statistic\sequence_1_load.log

    start  ..\..\..\2_base\0_payload\programme\payload.exe
    sleep(%sleep_time%)
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        run.bat
    )
    move statistic.log ..\statistic\2_load.log
    move sequence.log ..\statistic\sequence_2_load.log

    start  ..\..\..\2_base\0_payload\programme\payload.exe
    sleep(%sleep_time%)
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        run.bat
    )
    move statistic.log ..\statistic\3_load.log
    move sequence.log ..\statistic\sequence_3_load.log

    start  ..\..\..\2_base\0_payload\programme\payload.exe
    sleep(%sleep_time%)
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        run.bat
    )
    move statistic.log ..\statistic\4_load.log
    move sequence.log ..\statistic\sequence_4_load.log

    start  ..\..\..\2_base\0_payload\programme\payload.exe
    sleep(%sleep_time%)
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        run.bat
    )
    move statistic.log ..\statistic\5_load.log
    move sequence.log ..\statistic\sequence_5_load.log

    start  ..\..\..\2_base\0_payload\programme\payload.exe
    sleep(%sleep_time%)
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        run.bat
    )
    move statistic.log ..\statistic\6_load.log
    move sequence.log ..\statistic\sequence_6_load.log

    start  ..\..\..\2_base\0_payload\programme\payload.exe
    sleep(%sleep_time%)
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        run.bat
    )
    move statistic.log ..\statistic\7_load.log
    move sequence.log ..\statistic\sequence_7_load.log

    start  ..\..\..\2_base\0_payload\programme\payload.exe
    sleep(%sleep_time%)
    for /l %%b in (1, 1, %RUN_TIMES%) do (
        run.bat
    )
    move statistic.log ..\statistic\8_load.log
    move sequence.log ..\statistic\sequence_8_load.log

    taskkill /IM payload.exe
    cd ../statistic
    
    cd ../..
)
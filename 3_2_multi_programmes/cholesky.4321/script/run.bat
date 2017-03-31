set current_path=%cd%

set RUN_TIMES=10000
del %current_path%\statistic.log

for /l %%b in (1, 1, %RUN_TIMES%) do (
    %current_path%\..\programme\programme.exe %current_path%\..\programme\inputs\d750.O
)
move %current_path%\statistic.log %current_path%\..\statistic\0_load.log

start  %current_path%\..\..\..\2_base\0_payload\programme\payload.exe
for /l %%b in (1, 1, %RUN_TIMES%) do (
    %current_path%\..\programme\programme.exe %current_path%\..\programme\inputs\d750.O
)
move %current_path%\statistic.log %current_path%\..\statistic\1_load.log

for /l %%x in (0, 1, 6) do (
    start  %current_path%\..\..\..\2_base\0_payload\programme\payload.exe
)
for /l %%b in (1, 1, %RUN_TIMES%) do (
    %current_path%\..\programme\programme.exe %current_path%\..\programme\inputs\d750.O
)
move %current_path%\statistic.log %current_path%\..\statistic\7_load.log

start  ..\..\..\2_base\0_payload\programme\payload.exe
for /l %%b in (1, 1, %RUN_TIMES%) do (
    %current_path%\..\programme\programme.exe %current_path%\..\programme\inputs\d750.O
)
move %current_path%\statistic.log %current_path%\..\statistic\8_load.log

taskkill /IM payload.exe
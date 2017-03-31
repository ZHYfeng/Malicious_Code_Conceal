
set RUN_TIMES=10000
del .\statistic.log

for /l %%b in (1, 1, %RUN_TIMES%) do (
    ..\programme\programme.exe
)
ren .\statistic.log ..\statistic\0_load.log

start  ..\..\..\2_base\0_payload\programme\payload.exe
for /l %%b in (1, 1, %RUN_TIMES%) do (
    ..\programme\programme.exe
)
ren .\statistic.log ..\statistic\1_load.log

for /l %%x in (0, 1, 6) do (
    start  ..\..\..\2_base\0_payload\programme\payload.exe
)
for /l %%b in (1, 1, %RUN_TIMES%) do (
    ..\programme\programme.exe
)
ren .\statistic.log ..\statistic\7_load.log

start  ..\..\..\2_base\0_payload\programme\payload.exe
for /l %%b in (1, 1, %RUN_TIMES%) do (
    ..\programme\programme.exe
)
ren .\statistic.log ..\statistic\8_load.log

taskkill /IM payload.exe
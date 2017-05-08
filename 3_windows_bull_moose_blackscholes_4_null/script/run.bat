
set RUN_TIMES=10000

for /l %%b in (1, 1, %RUN_TIMES%) do (
    ..\programme\bin\Debug\bull_moose_blackscholes.exe
)

ren .\statistic.log low.log

for /l %%x in (0, 1, 8) do (
    start /b ..\..\0_payload\programme\bin\Debug\payload.exe
)

for /l %%b in (1, 1, %RUN_TIMES%) do (
    ..\programme\bin\Debug\bull_moose_blackscholes.exe
)

ren .\statistic.log high.log
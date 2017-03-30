
set RUN_TIMES=10000

del .\statistic.log

for /l %%b in (1, 1, %RUN_TIMES%) do (
    ..\programme\FFT.exe
)

ren .\statistic.log low.log

for /l %%x in (0, 1, 8) do (
    start /b ..\..\0_payload\programme\bin\Debug\payload.exe
)

for /l %%b in (1, 1, %RUN_TIMES%) do (
    ..\programme\FFT.exe
)

ren .\statistic.log high.log
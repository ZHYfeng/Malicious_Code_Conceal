taskkill /F /IM payload.exe
REM for /l %%i in (0, 1, 10) do (
    for /l %%x in (0, 1, 500) do (
        REM start /b microsoft-edge:http://202.117.10.196:8080/jpetstore/shop/viewItem.shtml?itemId=EST-4
        start payload.exe
    )
    REM Wscript sleep.vbs
    REM taskkill /F /IM payload.exe
REM )
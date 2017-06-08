set RUN_TIMES=50

        for /l %%b in (1, 1, %RUN_TIMES%) do (
            .\run.bat
        )
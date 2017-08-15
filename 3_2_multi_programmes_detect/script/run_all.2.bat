set RUN_TIMES=10000
set LOOPS=120000

cd ../apps.bullmoose
for /d %%i in (./*) do (

    cd %%i/programme
    del *.o *.exe 
    REM del occurrence.log sequence.log
    make

    cd ../statistic
    REM del *

    cd ../script

    

    cd ../..
)
cd ../script
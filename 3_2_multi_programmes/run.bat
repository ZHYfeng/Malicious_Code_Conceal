for /d %%i in (*) do (
    cd %%i/programme
    make
    cd ../script
    run.bat
    cd ../..
)
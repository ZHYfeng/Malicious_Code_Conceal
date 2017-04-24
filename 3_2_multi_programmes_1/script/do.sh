#!/bin/bash

for FILE in ../apps/*
do 
    echo $FILE
    
    # rm -rf $FILE/statistic $FILE/script
    # mv -t ./programme $FILE/*
    # mkdir $FILE/programme
    # mv -t $FILE/programme ./programme/*
    # mv $FILE/programme/Makefile $FILE/programme/makefile
    # mkdir $FILE/statistic
    # mkdir $FILE/script
    # cp -t $FILE/script ./run.bat

    # cp ../../2_bullmoose/bullmoose_4_pthread.c $FILE/programme/bullmoose.c
    # cp ../../2_bullmoose/bullmoose_4_pthread.h $FILE/programme/bullmoose.h


    cp -rf $FILE $FILE.1342
    cp -rf $FILE $FILE.1432
    cp -rf $FILE $FILE.4321

done

rm -rf ../apps.malicious
mkdir ../apps.malicious
mv -t ../apps.malicious ../apps/*.*




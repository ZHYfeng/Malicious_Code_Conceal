#!/bin/bash

totalline(){
	sum=0
	for file in `ls *.[ch]`
	do
    	lines=`awk 'END{ print NR; }' ./$file`
    let "sum+=lines"
	done
	echo "totalline:$sum" >> ../../statics.txt
}

for FILE in ../apps.LCLB.detect.branko/*
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


    # cp -rf $FILE $FILE.1342
    # cp -rf $FILE $FILE.1432
    # cp -rf $FILE $FILE.4321

    cd $FILE/programme
    echo "$FILE" >> ../../statics.txt
    totalline
    cd ../..

done

# rm -rf ../apps.malicious
# mkdir ../apps.malicious
# mv -t ../apps.malicious ../apps/*.*

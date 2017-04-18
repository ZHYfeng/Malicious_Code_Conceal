#!/bin/bash
for FILE in ./loop*.txt
do 
    python3 ../../../0_statstic/script/calc_subsec_and_sort_temp.py -f $FILE -s 1-2-3-4 
done

for FILE in ./loop*.txt.1-2-3-4
do 
    echo -n $FILE >> result.txt
    echo -n ", " >> result.txt
    cat $FILE >> result.txt
done


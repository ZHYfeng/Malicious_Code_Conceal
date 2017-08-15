#!/bin/bash
rm *.1-2-3-4
for FILE in ./sequence_*.log
do 
    python3 ../../0_statistic/calc_subsec_and_sort.py -f $FILE -s 1-2-3-4 
done

rm sequence_result.txt
for FILE in ./sequence_*.log.1-2-3-4
do 
    echo -n $FILE >> sequence_result.txt
    echo -n ", " >> sequence_result.txt
    cat $FILE >> sequence_result.txt
done
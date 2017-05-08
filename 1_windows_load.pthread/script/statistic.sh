#!/bin/bash
rm *.1-2-3-4
for FILE in ./sequence_*.log
do 
    python3 ../../0_statistic/calc_subsec_and_sort.py -f $FILE -s 1-2-3-4 
done

rm result.txt
for FILE in ./sequence_*.log.1-2-3-4
do 
    echo -n $FILE >> result.txt
    echo -n ", " >> result.txt
    cat $FILE >> result.txt
done



#!/bin/bash

totalline(){
	sum=0
	for file in `ls *.[ch]`
	do
    	lines=`awk 'END{ print NR; }' ./$file`
    let "sum+=lines"
	done
	echo "totalline:$sum" >> ./output_info/statics.txt
}

totalline "."

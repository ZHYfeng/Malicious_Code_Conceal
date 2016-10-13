#!/bin/bash

getmemory(){
	sleep 0.01
	for file in `ls /proc/`
	do
		if [ -d /proc/$file ]
			then
			cmd=`awk '{ print $1; }' /proc/${file}/comm`
			if [ $cmd == "klee" ]
				then
				temp=`awk -F" " '{ print ($2-$3)*4; }' /proc/${file}/statm`
				mem=0
				while [[ -n $temp ]]
				do
					if [ $temp -gt $mem ]
						then
						mem=$temp
					fi
					temp=`awk -F" " '{ print ($2-$3)*4; }' /proc/${file}/statm`
				done
				sleep 0.5
				echo "memory:$mem" >> $1/output_info/statics.txt
				break
			fi
		fi
	done
}

totalline(){
	sum=0
	for file in `ls *.[ch]`
	do
    	lines=`awk 'END{ print NR; }' ./$file`
    let "sum+=lines"
	done
	echo "totalline:$sum" >> ./output_info/statics.txt
}

recurrence(){
	cd $1
	for file in `ls`
	do
		if [ -d $file ]
			then
			recurrence $file
		elif [ $file == "test.sh" ]
			then
			now=$PWD
			echo "#"$now >> ${all}/all.md
			make
			getmemory $now &
			./$file
			awk -F" " '{ if( $1 == "klee" ) { printf("- 运行命令:\n\t"); x=1; while( x<NF-1 ){ printf("%s ",$x); x++; } printf("\n"); } }' ./$file >> ${all}/all.md
			more ./README >> ${all}/all.md
			echo "" >> ${all}/all.md
			totalline
			pwd | awk -F"/" '{ printf("name:%s\n",$NF); }' >> ./output_info/statics.txt
			more ./output_info/statics.txt >> ${all}/all.md
			sleep 1
			awk -F":" '{ printf("%s ",$2); }' ./output_info/statics.txt >> ${all}/DATE1.txt
			echo "" >> ${all}/DATE1.txt
			echo "" >> ${all}/all.md
			echo "" >> ${all}/all.md
			echo "" >> ${all}/all.md
			make clean
			#rm -rf klee* output_info result.txt
		fi
	done

	cd ..
}

all=$PWD
rm ${all}/all.md
rm ${all}/DATE1.txt
rm ${all}/DATE2.txt
recurrence "."
awk -F" " '{ printf("%s %s %s %s ",$NF,$(NF-1),$(NF-2),$(NF-3)); x=1; while( x<NF-3 ){ printf("%s ",$x); x++; } printf("\n"); }' ${all}/DATE1.txt >> ${all}/DATE2.txt
#!/bin/sh
#collect_data.sh
#author: wgc

dirName=`date +%y%m%d`
dir=$(find . -name "$dirName")
echo $dirName
echo $dir

if [ -n "$dir" ]
then
#	mkdir $dirName
	echo "already exit a dir"
else
	mkdir $dirName
	echo "mkdir""$dirName"
fi
filename=`date +%y%m%d`
path=`pwd`
data=$1
record=0
record_Num=$(cat record.txt) 
while read -r line
do
	if [ $record_Num -le $record ]
	then
	echo $line
	$path/paris-traceroute --algo=exhaustive $line >> $dirName/paris-traceroute$filename 2>&1
	fi
	record=`expr $record + 1`
	echo $record > record.txt
done < $data

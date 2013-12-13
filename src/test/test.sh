#!/bin/sh
a=10
b=`expr $a + 1`
echo $b
#read c d
#echo $c
#echo $d
h=`cat record.txt`
echo $h
f=$(cat ddd)
#echo "f"
if [ "4" -le "2" ]
then
	echo "ture"
else
	echo "false"
fi
echo "kaka > /dev/null"
#cat record.txt | while read line
#do
#	echo $line
#done

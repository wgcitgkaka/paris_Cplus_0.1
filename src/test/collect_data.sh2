#!/bin/sh
#collect_data.sh
#author: wgc

dirName=`date +%y%m%d`
mkdir $dirName
filename=`date +%y%m%d%h`
path=`pwd`
data=$1
while read -r line
do
	$path/paris-traceroute --algo=exhaustive $line >> $dirName/paris-traceroute$filename 2>&1
done < $data

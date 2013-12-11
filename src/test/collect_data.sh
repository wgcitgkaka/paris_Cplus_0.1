#!/bin/sh
#collect_data.sh
#author: wgc

filename=`date +%y%m%d`
touch $filename
data=$1
while read -r line
do
	../paris-traceroute --algo=exhaustive $line >> paris-traceroute$filename 2>&1 
done < $data

#!/bin/sh
#cron_paris

cron_parisf()
{
        dir=$(pwd)
        #echo "0" > $dir/record.txt
        echo "0 7 * * * /bin/echo 0 > $dir/record.txt" >> $dir/paris_cron
        echo "0 8 * * * $dir/collect_data.sh $dir/data3.txt > /dev/null" >> $dir/paris_cron
        crontab paris_cron
        rm -f $dir/paris_cron
}
cron_parisf

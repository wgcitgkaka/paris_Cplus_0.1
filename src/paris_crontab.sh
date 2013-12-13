#!/bin/sh
#paris-crontab


paris_crontabf()
{
	dir=$(pwd)
#	echo "* * * * *	$dir/collect_data.sh data3.txt > /dev/null" >> paris_crontab
	echo "*/2 * * * *	$dir/test_kaka" >> paris_crontab
	cat paris_crontab
	crontab paris_crontab
	#/etc/init.d/cron enable
	#/etc/init.d/cron restart
}
paris_crontabf

#!/bin/sh


var=pppd
ps |grep $var |grep -v grep

if [ $? -eq 0 ];then
	echo $var  to stop...
	killall pppd
else
	echo  $var is stoped.
fi



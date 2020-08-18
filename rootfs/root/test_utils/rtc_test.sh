#!/bin/sh #--------------------------------#
if [ ! -f /root/test_utils/rtc.log ]; then 
	echo "---------------------RTC test--------------"
	date -s 2017-06-18T18:18:00-0000
	hwclock -w
	touch /root/test_utils/rtc.log
	echo "---------------RTC test : Poweroff the board and restart again!"
	echo "RTC=RESTART;" >> /root/test_utils/test_result.txt
	#lunch QT app to show the notification
	/root/test_utils/imx6ulB_qt_test_app -qws
	exit 0
fi
STARTTIME=`date +%s`
sleep 3
ENDTIME=`date +%s`
USETIMES=`expr $ENDTIME - $STARTTIME`
if [ ! $USETIMES -eq 3 ]; then
	echo "---------------RTC test : ERROR !!"
	exit 0
fi

if [ -f /root/test_utils/rtc.log ]; then
	rtc_day=`date | awk '{print $3}'`
	if [ ! $rtc_day -eq 18 ];then
		echo "---------------RTC test : ERROR !!"
		echo "RTC=ERR;" >> /root/test_utils/test_result.txt
		rm /root/test_utils/rtc.log
		exit 0
	fi

	rtc_year=`date | awk '{print $6}'`
	if [ ! $rtc_year -eq 2017 ];then
		echo "---------------RTC test : ERROR !!"
		echo "RTC=ERR;" >> /root/test_utils/test_result.txt
		rm /root/test_utils/rtc.log
		exit 0
	fi

fi
echo "---------------RTC test : OK !!"
rm /root/test_utils/rtc.log
echo "RTC=OK;" >> /root/test_utils/test_result.txt

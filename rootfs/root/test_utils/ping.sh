#!/bin/sh

#------------ping--------------#
ifconfig eth0 down
ifconfig eth1 down
ifconfig eth0 up
sleep 3

if [ -f /root/test_utils/ping.txt ]
then
	rm /root/test_utils/ping.txt
fi

timeout 18 udhcpc -i eth0
echo "1" > /root/test_utils/ping.txt
cd /root/test_utils
rm /root/test_utils/index.html
timeout 5 wget www.qq.com
FILE="/root/test_utils/ping.txt"
FILE_SIZE=`du $FILE | awk '{print $1}'`
if [ -f /root/test_utils/index.html ]
then
	echo  "-----------------Net1 alive, ping OK!!!"
	rm /root/test_utils/index.html
	rm /root/test_utils/ping.txt
	echo "NET1=OK;">> /root/test_utils/test_result.txt
else
	echo "1" > /root/test_utils/ping.txt
	ping -c 3 192.168.1.8 -I eth0 > ping.txt
	FILE="/root/test_utils/ping.txt"
	FILE_SIZE=`cat ./ping.txt | awk 'NR==7 {print $6}'`
	if [ "${FILE_SIZE}" == "0%" ]
	then
		echo  "-----------------Internet alive, ping OK!!"
		echo "NET1=OK">> /root/test_file/test_result.txt
		echo FILE_SIZE=$FILE_SIZE
		rm /root/test_utils/ping.txt
	else
		echo  "-----------------Net1 NOT alive, ping fail!!"
		echo "NET1=ERR;">> /root/test_utils/test_result.txt
		echo FILE_SIZE=$FILE_SIZE
		rm /root/test_utils/ping.txt
	fi
fi

ifconfig eth0 down
ifconfig eth1 up
sleep 3

timeout 18 udhcpc -i eth1
echo "1" > /root/test_utils/ping.txt
cd /root/test_utils
timeout 5 wget www.qq.com
FILE="/root/test_utils/ping.txt"
if [ -f /root/test_utils/index.html ]
then
        echo  "-----------------Net2 alive, ping OK!!!"
	rm /root/test_utils/index.html
        echo "NET2=OK;">> /root/test_utils/test_result.txt
else
	echo "1" > /root/test_utils/ping.txt
	ping -c 3 192.168.1.8 -I eth1 > ping.txt
	FILE="/root/test_utils/ping.txt"
	FILE_SIZE=`cat ./ping.txt | awk 'NR==7 {print $6}'`
	if [ "${FILE_SIZE}" == "0%" ]
	then
		echo  "-----------------Internet2 alive, ping OK!!"
		echo "NET2=OK">> /root/test_file/test_result.txt
		echo FILE_SIZE=$FILE_SIZE
	else
		echo  "-----------------Net2 NOT alive, ping fail!!"
		echo "NET2=ERR;">> /root/test_utils/test_result.txt
		echo FILE_SIZE=$FILE_SIZE
	fi
fi

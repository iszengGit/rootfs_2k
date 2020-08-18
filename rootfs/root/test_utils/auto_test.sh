#!/bin/sh
#--------------------------------#
if [  -f /root/test_utils/test_result.txt ]; then 
	rm /root/test_utils/test_result.txt
fi
touch /root/test_utils/test_result.txt

#rct test
sh /root/test_utils/rtc_test.sh

#turn up the speak and phone volue for audio output test
amixer cset numid=13 123
sleep 1
amixer cset numid=11 123
#generate random mac address for eth0 & eth1
sh /root/test_utils/mac_random_generate.sh
#dhcp and ping web
sh /root/test_utils/ping.sh

#UART 232 test (CON3 CON4 CON5)
/root/test_utils/uart232_test_app

#UART 485 test (CON3 CON4 CON5)
#板载只有一个485口，为了测试方便，这里用CON6(/dev/ttySAC5)外接ttl转485模块来跟RS485（/dev/ttySAC1）进行对测。
/root/test_utils/uart485_test_app

#usb host 
sh /root/test_utils/usb_host_test.sh

#sd card 
sh /root/test_utils/sdcard_test.sh

#lunch QT app to show the test result
/root/test_utils/imx6ulB_qt_test_app -qws


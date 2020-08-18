#!/bin/sh
#--------------------------------#
if [  -d /run/media/sda1 ]; then
	touch /run/media/sda1/usb_host_test.txt
else
        echo "USB_HOST=ERR;" >> /root/test_utils/test_result.txt
	exit 0
	
fi

if [ ! -f /run/media/sda1/usb_host_test.txt ]; then
        echo "USB_HOST=ERR;" >> /root/test_utils/test_result.txt
	exit 0
fi


if [  -d /run/media/sdb1 ]; then
        touch /run/media/sdb1/usb_host_test.txt
else
        echo "USB_HOST=ERR;" >> /root/test_utils/test_result.txt
        exit 0

fi

if [ ! -f /run/media/sdb1/usb_host_test.txt ]; then
        echo "USB_HOST=ERR;" >> /root/test_utils/test_result.txt
        exit 0
fi


if [  -d /run/media/sdc1 ]; then
        touch /run/media/sdc1/usb_host_test.txt
else
        echo "USB_HOST=ERR;" >> /root/test_utils/test_result.txt
        exit 0

fi

if [ ! -f /run/media/sdc1/usb_host_test.txt ]; then
        echo "USB_HOST=ERR;" >> /root/test_utils/test_result.txt
        exit 0
fi


if [  -d /run/media/sdd1 ]; then
        touch /run/media/sdd1/usb_host_test.txt
else
        echo "USB_HOST=ERR;" >> /root/test_utils/test_result.txt
        exit 0

fi

if [ ! -f /run/media/sdd1/usb_host_test.txt ]; then
        echo "USB_HOST=ERR;" >> /root/test_utils/test_result.txt
        exit 0
fi
# nothing wrong. consider as OK
echo "USB_HOST=OK;" >> /root/test_utils/test_result.txt

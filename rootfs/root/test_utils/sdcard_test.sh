#!/bin/sh
#--------------------------------#
if [  -d /run/media/mmcblk0p1 ]; then
	touch /run/media/mmcblk0p1/sdcard_test.txt
elif [ -d /run/media/mmcblk0 ]; then
	touch /run/media/mmcblk0/sdcard_test.txt
else
        echo "SDCARD=ERR;" >> /root/test_utils/test_result.txt
	exit 0
	
fi


if [  -f /run/media/mmcblk0p1/sdcard_test.txt ]; then
	rm /run/media/mmcblk0p1/sdcard_test.txt
	echo "SDCARD=OK;" >> /root/test_utils/test_result.txt
elif [ -d /run/media/mmcblk0 ]; then
	touch /run/media/mmcblk0/sdcard_test.txt
	echo "SDCARD=OK;" >> /root/test_utils/test_result.txt
else
	echo "SDCARD=ERR;" >> /root/test_utils/test_result.txt
	
fi


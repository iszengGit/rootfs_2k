#!/bin/sh
echo "asdasdad"
if [ "$ACTION" = "add" ] ; then
	rm $DEVNAME
	mknod /dev/touchscreen0 c $MAJOR $MINOR
fi

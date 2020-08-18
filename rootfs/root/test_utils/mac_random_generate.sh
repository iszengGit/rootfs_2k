#!/bin/sh
#echo "00:60:2F$(dd bs=1 count=3 if=/dev/random 2>/dev/null |hexdump -v -e '/1 ":%02X"')" //输出随机值
ifconfig eth0 down
ifconfig eth0 hw ether "00:60:2F$(dd bs=1 count=3 if=/dev/random 2>/dev/null |hexdump -v -e '/1 ":%02X"')"
ifconfig eth0 up
#echo "first command"

#echo "$(hexdump -n3 -e'/3 "00:60:2F" 3/1 ":%02X"' /dev/random)" //输出随机值
ifconfig eth1 down
ifconfig eth1 hw ether "$(hexdump -n3 -e'/3 "00:60:2F" 3/1 ":%02X"' /dev/random)"
ifconfig eth1 up
#echo "second command"

#下面两句还不知道用途
#printf '00:60:2F:%02X:%02X:%02X\n' $[RANDOM%256] $[RANDOM%256] $[RANDOM%256]
#echo 00:60:2f:`openssl rand -hex 3 | sed 's/\(..\)/\1:/g; s/.$//'`

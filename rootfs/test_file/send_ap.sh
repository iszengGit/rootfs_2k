#!/bin/sh

ifconfig wlan0 down

ps -ef | grep hostapd | grep -v grep | awk '{print $1}' | xargs kill -9

ps -ef | grep wpa_supplicant | grep -v grep | awk '{print $1}' | xargs kill -9

ps -ef | grep udhcpd | grep -v grep | awk '{print $1}' | xargs kill -9


hostapd -B /etc/hostapd.conf -f /var/log/hostap.log

ifconfig wlan0 192.168.0.2

udhcpd -f /etc/udhcpd.conf &



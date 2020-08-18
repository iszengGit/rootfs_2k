#!/bin/sh

i=0
while [ $i -lt 5 ];do
    echo 1 > /sys/class/leds/LED1/brightness
    echo 0 > /sys/class/leds/LED2/brightness
    sleep 1
    echo 0 > /sys/class/leds/LED1/brightness
    echo 1 > /sys/class/leds/LED2/brightness
    sleep 1
    i=`expr $i + 1`
done


#!/bin/sh
cd /etc/ppp/peers/

route | grep default | grep -v grep | awk '{print $1 > "/test_file/rtab"}'

cat /test_file/rtab | 
while read line
do
if [[ $line -eq "default" ]];then
   route del $line
else
  echo "not found the default route"
fi
     sleep 1
done
rm /test_file/rtab

ps -ef|grep pppd |grep -v grep|grep -v PPID|awk '{ print $1}' | xargs kill -9

pppd call tq_init & 

cd -



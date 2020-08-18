#!/bin/sh

candev=$1

help()
{
    echo 'use :'  ./$0  "can0 or can1"
}
setcfg(){
    local dev=$1;
    local speed=$2;
    ifconfig ${dev} down
    ip link set ${dev} type can bitrate ${speed} triple-sampling on
    ifconfig ${dev} up
    echo dev=$dev speed=$speed
}
send(){
    local candev=$1;
    local time=$2;
    cnt=0;
    for i in `seq 1 $time`;do
        let "str = $i + 110";
        cansend $candev ${str}\#1122334455667788 
	    sleep 1
    done
}


#if [ $# -eq 0 ];then
    #help 
    #exit ;
#fi
#if [ ${candev} != "can0" ] && [ ${candev} != "can1" ];then
    #help
    #exit ;
#fi

#setcfg ${candev}  125000
#killall candump
#candump ${candev} &

#echo "--------------------------------"  
#echo "${candev} send start..."
#sleep 1
#send ${candev} 3

setcfg 'can0' 125000
setcfg 'can1' 125000
killall candump
candump can1 &
send 'can0' 3;
sleep 1


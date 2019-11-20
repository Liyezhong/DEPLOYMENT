#!/bin/bash

/usr/bin/eGTouchD
ifconfig eth0 hw ether be:1e:9c:ae:ec:59 10.10.235.242 netmask 255.255.255.0 up
route add default gw 10.10.235.2

ip link add dev can1 type vcan
ip link set can1 txqueuelen 10000
ip link set can1 up

ip link set can0 type can bitrate 1000000 loopback off
ip link set can0 txqueuelen 10000
ip link set can0 up

while true; do
# 1. ssh restart
	netstat -antp | grep 22 | grep LISTEN || systemctl start dropbear.socket

# 2. keyboard input key manage
 	kbd=`ls /dev/input/by-id/*-kbd 2>/dev/null`
	if [ $? -eq 0 ]; then
 		pidof key || key $kbd
	else
 		pkill -9 key
 	fi

# 3. system log 
#	logfilecount=$(ls /home/root/log/dmesg.* && )

 	sleep 10
done


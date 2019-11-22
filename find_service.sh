#!/bin/bash

linkName=`ls /home/root/service -l | awk '{print $NF}'`

for i in `find /home/root -name 'SVC_??\.???\.???' -o -name 'SVC_dev_??\.???\.???' 2>/dev/null`; do
    name=${i##*/}
    [ "$linkName" = "$name" ] && echo "$name=$i=1"
    [ "$linkName" = "$name" ] || echo "$name=$i=0"
done


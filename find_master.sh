#!/bin/bash

linkName=`ls /home/root/skyline_arm -l | awk '{print $NF}'`

for i in `find /home/root -name 'MSW_??\.???\.???' -o -name 'MSW_dev_??\.???\.???' 2>/dev/null`; do
    name=${i##*/}
    [ "$linkName" = "$name" ] && echo "$name=$i=1"
    [ "$linkName" = "$name" ] || echo "$name=$i=0"
done


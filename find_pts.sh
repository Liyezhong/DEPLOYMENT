#!/bin/bash

# set -x

linkName=`ls /home/root/prototest -l | awk '{print $NF}'`
linkName=${linkName##*/}

for i in `find /home/root -name 'PTS_??\.???\.???' -o -name 'PTS_dev_??\.???\.???' 2>/dev/null`; do
    name=${i##*/}
    [ "$linkName" = "$name" ] && echo "$name=$i=1"
    [ "$linkName" = "$name" ] || echo "$name=$i=0"
done


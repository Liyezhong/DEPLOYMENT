#!/bin/bash

for i in `find /home/root /run/media/sd* -name 'PTS_??\.???\.???\.sh' -o -name 'PTS_dev_??\.???\.???\.sh' 2>/dev/null`; do
    name=${i##*/}
    name=${name%.*}
    echo "$name=$i"
done

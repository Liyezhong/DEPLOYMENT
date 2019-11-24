#!/bin/bash

for i in `find /home/root /run/media/sd* -name 'MSW_??\.???\.???\.sh' -o -name 'MSW_dev_??\.???\.???\.sh' 2>/dev/null`; do
    name=${i##*/}
    name=${name%.*}
    echo "$name=$i"
done

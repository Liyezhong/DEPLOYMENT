#!/bin/bash

# slave name: SLAVE_0001_20191115.tar.bz2
for i in `find /home/root /run/media/sd* -name 'SLAVE_????_*.tar.bz2' 2>/dev/null`; do
    name=$(echo ${i##*/} | sed 's/SLAVE_//' | sed 's/.tar.bz2//')
    echo "$name=$i"
done

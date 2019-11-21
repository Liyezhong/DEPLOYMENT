#!/bin/bash

cat /etc/init.d/ebox.sh | grep ifconfig | awk -F' ' '{
    for (i = 1; i <= NF; i++) {
        if ($i ~ /\./ && $(i - 1) !~ /netmask/)
            print "ip=" $i
        if ($i ~ /\./ && $(i - 1) ~ /netmask/)
            print "netmask=" $i
        if ($i ~ /\:/)
            print "mac=" $i
    }
}'

cat /etc/init.d/ebox.sh | grep route | awk -F' ' '{
            print "gateway=" $5
}'

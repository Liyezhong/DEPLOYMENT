#!/bin/bash

# $1 : ip address
# $2 : mac address
# $3 : gateway

cat /etc/init.d/ebox.sh | awk -v ipaddress="$1" -v mac="$2" -v gateway="$3" '{
if ($0 ~ /ifconfig/)
    print "ifconfig eth0 " ipaddress " netmask 255.255.255.0 hw ether " mac " up"
else if ($0 ~ /route/)
    print "route add default gw " gateway
else
    print
}' > ebox1.sh

chmod a+x ebox1.sh
mv ebox1.sh /etc/init.d/ebox.sh
sync

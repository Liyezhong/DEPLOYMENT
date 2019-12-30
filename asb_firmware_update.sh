#!/bin/bash

function refresh()
{
#    echo 'run file /home/root/prototest/Skyline_Scripts/System/FirmwareUpdate/Refresh.js' | netcat -q 60 localhost 8880
    echo 'run cfunc refresh' | netcat -q 60 localhost 8880
}

function switchtobootloader()
{
    echo 'run file /home/root/prototest/Skyline_Scripts/System/FirmwareUpdate/SwitchToBootloaderMode.js' | netcat -q 60 localhost 8880
}

function resetNode()
{
    echo 'run file /home/root/prototest/Skyline_Scripts/System/FirmwareUpdate/ResetNode.js' | netcat -q 20 localhost 8880
}

function create_update_firmware_expr()
{
    # $1 : ASB id
    # $2 : ASB package path
    echo -n 'UpdateFirmware(' >>  /tmp/UpdateFirmware.js
    echo -n "$1" >>  /tmp/UpdateFirmware.js
    echo -n ', "' >>  /tmp/UpdateFirmware.js
    echo -n "$2" >>  /tmp/UpdateFirmware.js
    echo '");' >>  /tmp/UpdateFirmware.js
}

function update_firmware()
{
    echo 'run file /tmp/UpdateFirmware.js' | netcat -q 120 localhost 8880
}

function asb_update_script_create()
{
    # $1 : asb package file path
    # 1. decode asb package
    data=`tar xvf $1 -C /tmp | head -n 1`
    version=${data%/*}

    # 2. create asb path
    asb_20_path="/tmp/$version/ASB20_rel.bin"
    asb_21_path="/tmp/$version/ASB21_rel.bin"
    asb_22_path="/tmp/$version/ASB22_rel.bin"

    # 3. create update_firmware file
    cat /home/root/prototest/Skyline_Scripts/System/FirmwareUpdate/UpdateFirmware.js > /tmp/UpdateFirmware.js
    create_update_firmware_expr 20 $asb_20_path
    create_update_firmware_expr 21 $asb_21_path
    create_update_firmware_expr 22 $asb_22_path
}

cd /usr/leica/bin
./prototest_start.sh &

sleep 50

echo ' asb_update_script_create $1'
asb_update_script_create $1

# 1. switch to bootloader 
echo '1 bootloader'
switchtobootloader
# 2. reset node
echo '2 resetNode'
resetNode
# 3. refresh
echo '3 refresh'
refresh
# 4. update firmware 
echo '4 update_firmware'
update_firmware
# 5. reset node
echo '5 resetNode'
resetNode

sleep 30

pkill -9 ProtoTest

exit 0

#!/bin/bash

INSTALL_DIR="/home/root/"
PAYLOAD_OFFSET=$(($(grep -na -m1 "^__END__$" $1 | cut -d':' -f1)+1))
#RELEASE_BUILD_NAME=$(tail -n +$PAYLOAD_OFFSET $1  \
#    | tar tvj | head -1 | awk '{print $6}' | cut -d'/' -f1)

RELEASE_BUILD_NAME=$1
RELEASE_BUILD_NAME=${RELEASE_BUILD_NAME##*/}
RELEASE_BUILD_NAME=${RELEASE_BUILD_NAME%.*}

#echo $RELEASE_BUILD_NAME
#echo "payload_offset: $PAYLOAD_OFFSET"

tail -n +$PAYLOAD_OFFSET $1 | tar jxv -C $INSTALL_DIR
[ $? -ne 0 ] && { 
    echo "Sorry, install failed!!!"
    exit -1
}

cd $INSTALL_DIR

if echo $RELEASE_BUILD_NAME | grep "MSW"; then
    INSTALL_BUILD_NAME="skyline_arm"
elif echo $RELEASE_BUILD_NAME | grep "PTS"; then
    INSTALL_BUILD_NAME="prototest"
elif echo $RELEASE_BUILD_NAME | grep "SVC"; then
    INSTALL_BUILD_NAME="service"
elif echo $RELEASE_BUILD_NAME | grep "MFG"; then
    INSTALL_BUILD_NAME="manufacturing"
fi

rm -fr $INSTALL_BUILD_NAME
ln -fs $RELEASE_BUILD_NAME $INSTALL_BUILD_NAME
sync

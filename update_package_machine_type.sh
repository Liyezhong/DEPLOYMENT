#!/bin/bash

#$1 : r / w
#$2 : Platinum / Gold
#$3 : alpha1 / alpha2

[ $# -eq 0 ] && exit -1
[ $# -gt 3 ] && exit -1

function set_platinum_gold_single()
{
    echo $1
    awk -v machine_type=$2 '
        /SERIALNUMBER=/{ 
            for (i = 1; i <= NF; i++) {
                if (i == 7)
                    printf substr($7, 1, length($7) - 2) machine_type "\"" " "
                else
                    printf $i " "
            }
        printf "\n"
        }
        !/SERIALNUMBER/{print $0}
    ' $1  > /tmp/DeviceConfiguration.xml
    mv -f /tmp/DeviceConfiguration.xml $1
}


function set_alpha_type_single()
{
    echo $1
    awk -v alpha_type="$2" '{
            if ($0 ~ /HwSpec/)
                print "HwSpec=\"" alpha_type "\""
            else
                print
    }' $1 > /tmp/InstrumentConfigFile.ini
    mv -f /tmp/InstrumentConfigFile.ini $1
}


[ "$1" = "r" ] && {

    grep "MACHINE_TYPE" /etc/profile > /dev/null 2>&1;
    [ $? -eq 0 ] && {
        cat /etc/profile | grep MACHINE_TYPE | awk '{print $2}'
    }
    grep "ALPHA_TYPE" /etc/profile > /dev/null 2>&1;
    [ $? -eq 0 ] && {
        cat /etc/profile | grep ALPHA_TYPE | awk '{print $2}'
    }

    exit 0
}

[ "$1" = "w" ] && {

    grep "MACHINE_TYPE" /etc/profile > /dev/null 2>&1;

    [ $? -ne 0 ] && {
        echo >> /etc/profile
        echo "export MACHINE_TYPE=$2" >> /etc/profile
        echo "export ALPHA_TYPE=$3" >> /etc/profile
    }
    cat /etc/profile | awk -v machine_type=$2 -v alpha_type=$3 '{
        if ($0 ~ /MACHINE_TYPE/) 
            print "export MACHINE_TYPE=" machine_type
        else if ($0 ~ /ALPHA_TYPE/)
            print "export ALPHA_TYPE=" alpha_type
        else
            print
    }' > /tmp/profile
    mv -f /tmp/profile /etc/profile

    type_machine_int=1
    [ "$2" = "Platinum" ] && type_machine_int=1
    [ "$2" = "Gold" ] && type_machine_int=2
    update_platinum_gold $type_machine_int

    type_alpha_str=""
    [ "$3" = "Alpha1" ] && type_alpha_str="hw_specification_ALPHA1.xml"
    [ "$3" = "Alpha2" ] && type_alpha_str="hw_specification.xml"
    update_alpha_type $type_alpha_str

    sync
}

#!/usr/bin/env bash

# Check if gcc-arm-embedded is installed.
if [ $(dpkg-query -W -f='${Status}' gcc-arm-embedded 2>/dev/null | grep -c "ok installed") -eq 0 ];
then

# If it is not check if software-properties-common is (add-apt-repository)
if [ $(dpkg-query -W -f='${Status}' software-properties-common 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
apt-get install -y software-properties-common
fi

# Add the arm ppa, update and install the arm gcc compiler.
add-apt-repository ppa:team-gcc-arm-embedded/ppa
apt-get update
apt-get install -y gcc-arm-embedded

fi

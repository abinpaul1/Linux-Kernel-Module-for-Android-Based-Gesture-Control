#!/bin/sh
#  install.sh


sudo apt install figlet
PKG_OK=$(dpkg-query -W --showformat='${Status}\n' android-tools-adb|grep "install ok installed")
if [ "" == "$PKG_OK" ]; then
   figlet -f smslant -r -w 40 "====================================="
   figlet -f smslant -r -w 40 "ADB not installed, installing ADB now"
   figlet -f smslant -r -w 40 "====================================="

    sudo add-apt-repository ppa:phablet-team/tools
    sudo apt-get update
    sudo apt-get --force-yes --yes install android-tools-adb
fi

PKG_OK=$(dpkg-query -W --showformat='${Status}\n' linux-headers-$(uname -r)|grep "install ok installed")
if [ "" == "$PKG_OK" ]; then
   figlet -f smslant -r -w 40 "========================================================="
   figlet -f smslant -r -w 40 "Linux headers not installed, installing linux headers now"
   figlet -f smslant -r -w 40 "========================================================="

    sudo apt-get install linux-headers-$(uname -r)
fi

PKG_OK=$(dpkg-query -W --showformat='${Status}\n' build-essential|grep "install ok installed")
if [ "" == "$PKG_OK" ]; then
#    figlet -f smslant -r -w 40 "=========================="
   figlet -f smslant -r -w 40 "Building essential headers"
#    figlet -f smslant -r -w 40 "=========================="

    sudo apt-get install build-essential
fi

# figlet -f smslant -r -w 40 "============="
figlet -f smslant -r -w 40 "Making module"
# figlet -f smslant -r -w 40 "============="

sudo rmmod gesture.ko
sudo make
sudo insmod gesture.ko

# figlet -f smslant -r -w 40 "================"
figlet -f smslant -r -w 40 "Compiling client"
# figlet -f smslant -r -w 40 "================"

gcc main.c
sudo adb logcat -c

# figlet -f smslant -r -w 40 "=============="
figlet -f smslant -r -w 40 "Client Started"
# figlet -f smslant -r -w 40 "=============="

sudo adb logcat -s "OSP" | sudo ./a.out
sudo rmmod gesture.ko


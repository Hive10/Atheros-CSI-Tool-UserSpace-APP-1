#!/bin/bash

#set wifi region
sudo iw reg set US

#disable network manager for wifi
sudo nmcli radio wifi off
sudo rfkill unblock wlan

#change ip and start hostapd
sudo ifconfig wlan0 192.168.1.1/24 up
sleep 1
sudo systemctl start hostapd.service

#sudo systemctl unmask hostapd.service
#sudo nano /etc/default/hostapd
#DAEMON_CONF="/usr/local/sbin/Atheros-CSI-Tool-UserSpace-APP/scripts/hostapd.conf"

#sudo nmcli con add con-name "neuralwave" ifname wlan0 type wifi ip4 192.168.1.103/24 ssid neuralwave

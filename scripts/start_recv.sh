#!/bin/bash

sudo ifconfig wlan0 down
sudo macchanger -m 00:0e:8e:59:8a:aa wlan0
sudo ifconfig wlan0 up
sudo macchanger -s wlan0

sudo nmcli radio wifi on


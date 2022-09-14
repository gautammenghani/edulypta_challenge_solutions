#!/bin/bash
sudo rmmod task8 
sudo insmod task8.ko
sudo chmod 777 /sys/kernel/debug

#!/bin/bash
sudo rmmod task17 
#sudo rm /dev/edulypta
sudo insmod task17.ko
sudo chmod 222 /dev/edulypta

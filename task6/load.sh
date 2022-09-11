#!/bin/bash
sudo rmmod hello_world
#sudo rm /dev/edulypta
sudo insmod hello_world.ko
sudo chmod 666 /dev/edulypta

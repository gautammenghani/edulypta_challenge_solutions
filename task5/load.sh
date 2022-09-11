#!/bin/bash
sudo rmmod hello_world
sudo rm /lib/modules/`uname -r`/hello_world.ko
sudo cp hello_world.ko /lib/modules/`uname -r`/
sudo depmod -a

#!/bin/bash

rm *.hex
make clean
make
sudo stm32flash -E -w bin/*/*.hex -v /dev/ttyACM0
sudo gtkterm --port /dev/ttyACM0 --speed 115200
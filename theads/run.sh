#!/bin/bash

rm *.hex
make clean
make
arm-none-eabi-objcopy -O ihex bin/*/*.elf 1.hex
st-flash --format ihex write 1.hex 

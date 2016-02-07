#!/bin/bash
make clean
make
mono bin/internetradioflash.exe p=/dev/ttyUSB0 f=bin/internetradioA6.hex

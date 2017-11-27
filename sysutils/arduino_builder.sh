#!/bin/bash

arduino_bin=$(readlink -f `which arduino`)
arduino_path=$(dirname "$arduino_bin")

if [ -d "$arduino_path" ]; then
	if [ -f "$arduino_path/arduino-builder" ]; then
		echo "$arduino_path/arduino-builder"
	else
		exit 1
	fi
else
	exit 2
fi

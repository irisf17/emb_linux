#!/bin/bash
#  Short script to toggle a GPIO pin at the highest frequency
#  possible using Bash - by Derek Molloy
echo 17 > /sys/class/gpio/export #output pin
echo 22 > /sys/class/gpio/export #input pin
sleep 0.5
echo "out" > /sys/class/gpio/gpio17/direction #output pin
echo "in" > /sys/class/gpio/gpio22/direction #input pin
COUNTER=0

while [ $COUNTER -lt 1000 ]; do
    cat /sys/class/gpio/gpio22/value | sudo tee /sys/class/gpio/gpio17/value
    let COUNTER=COUNTER+1
done

echo 17 > /sys/class/gpio/unexport
echo 22 > /sys/class/gpio/unexport
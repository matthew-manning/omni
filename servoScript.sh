
#! /bin/bash


##turn on clock
i2cset -y 1 0x40 0x00 0x11 ##turn off clock so scaler can be set 
i2cset -y 1 0x40 0xFE 0x7A ##must set prescaler before turning on clock
i2cset -y 1 0x40 0x00 0x01 ##turn on clock
sleep 0.1

i2cset -y 1 0x40 0x01 0x04 ##invert waveform

while [ 1 ]
do

##middle
i2cset -y 1 0x40 0x08 0x33
echo "a"
sleep 0.005
i2cset -y 1 0x40 0x09 0x01
echo "b"     
sleep 0.005
sleep 2

##right
i2cset -y 1 0x40 0x08 0x9A
sleep 0.005
echo "e"
i2cset -y 1 0x40 0x09 0x01
sleep 0.005
echo "f"


sleep 2
##left
i2cset -y 1 0x40 0x08 0xCD
sleep 0.005
echo "i"
i2cset -y 1 0x40 0x09 0x00
sleep 0.005
echo "j"

sleep 2

done

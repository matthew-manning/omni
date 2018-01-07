#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "omni.h"

void writeI2C(uint8_t Bus, uint8_t Addr, uint8_t Reg, uint8_t Data)
{
	char Str[50];
	sprintf(Str, "i2cset -y %d %d %d %d", Bus, Addr, Reg, Data);
	system(Str);
	usleep(1000); 
}
void initController(void)
{
	writeI2C(BUS, ADDR, 0x00, MODE_1A);
        writeI2C(BUS, ADDR, 0xFE, CLOCK_DIV);
        writeI2C(BUS, ADDR, 0x00, MODE_1B);
        writeI2C(BUS, ADDR, 0x01, MODE_2);

        writeI2C(BUS, ADDR, MOTOR_1-2, 0);
        writeI2C(BUS, ADDR, MOTOR_1-1, 0);
        writeI2C(BUS, ADDR, MOTOR_2-2, 0);
        writeI2C(BUS, ADDR, MOTOR_2-1, 0);
        writeI2C(BUS, ADDR, MOTOR_3-2, 0);
        writeI2C(BUS, ADDR, MOTOR_3-1, 0);

}

void write12 (uint8_t Reg, uint16_t Val)
{
	writeI2C(BUS, ADDR, Reg, (uint8_t)Val);
	writeI2C(BUS, ADDR, Reg+1, (uint8_t) ( (Val>>8)&0x0F) );
}

void motorSpeed(uint8_t Motor, int8_t Speed)
{
	//positive speed is clockwise
	uint16_t Val = MOTOR_BASE + (MOTOR_FULL * Speed)/100;
	write12(Motor, Val);
}

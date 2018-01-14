#include <stdint.h>
#include <stdio.h>
#include <math.h>
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

	(Speed == 0) ? Val=0 : 1;//cause zero speed to output no pulse, 1ms does not allways work quite right
	write12(Motor, Val);
}


void xySpeed(int16_t XPart, int16_t YPart, uint8_t Velocity)
{
	//Xpart and Ypart set speed of x realitive to y, actual speed along path of travel is set by velocity

	int16_t Heading;

	if((XPart >= 0)&&(YPart >= 0)) Heading = atanf((float)XPart/(float)YPart); 
	else if((XPart >= 0)&&(YPart < 0)) Heading = atanf((float)YPart/(float)XPart)+(PI/2);
	else if ((XPart<0)&&(YPart<0)) Heading = atanf((float)XPart/(float)YPart)+PI;
	else Heading = atanf((float)YPart/(float)XPart)+((3*PI)/2);

	//convert to degrees
	Heading = (Heading *180)/PI;

	vectorMove(Heading, Velocity); 
}

void spin(int8_t Spin)
{
       //spin is clockwise as positive

        motorSpeed(MOTOR_1, Spin);
        motorSpeed(MOTOR_2, Spin);
        motorSpeed(MOTOR_3, Spin);

}


void vectorMove(int16_t Heading, uint8_t Velocity)
{
	//Heading is given as degrees clockwise from direct ahead
	//spin is clockwise as positive

	int8_t ASpeed;
        int8_t BSpeed;
        int8_t CSpeed;

	Heading = (Heading * PI) / 180;

	ASpeed = Velocity * sinf( (float) Heading);
        BSpeed = Velocity * sinf( (float) Heading - (2*PI)/3);
        CSpeed = Velocity * sinf( (float) Heading - (4*PI)/3);

	//if the MIN_SPEED is too high, this code will cause issues
	ASpeed = (abs(ASpeed) <= MIN_SPEED)? 0 : ASpeed;
        BSpeed = (abs(BSpeed) <= MIN_SPEED)? 0 : BSpeed;
        CSpeed = (abs(CSpeed) <= MIN_SPEED)? 0 : CSpeed;

	motorSpeed(MOTOR_1, ASpeed);
        motorSpeed(MOTOR_2, BSpeed);
        motorSpeed(MOTOR_3, CSpeed);
}

void stopMotor(uint8_t Motor)
{
	write12(Motor, 0);
}


/*
void xyTravel(int32_t XDist, int32_t YDist,  uint8_t Speed)
{
//distances are in millimetres
	int8_t XSpeed;
	int8_t YSpeed;
	uint32_t Time;

	if(abs(XDist) > abs(YDist))//x is full speed, y is less than full speed
	{
		XSpeed = Speed;
		YSpeed = (YDist * Speed) / abs(XDist);
	}
	else//Y is full speed, X is less than full speed
	{
		XSpeed = (XDist * Speed) / abs(YDist);
		YSpeed = Speed;
	}

	Time = ( 1000 *100 * SEC_REV * sqrt(XDist*XDist + YDist*YDist) ) / (PI * WHEEL_DIAMETER * Speed * SPEED_FACTOR);// is milliseconds
	
	printf("time calculated is %d ms\n", Time);
	
	xySpeed(XSpeed, YSpeed); 
	usleep(1000 * Time);
	STOP_ALL
}
*/

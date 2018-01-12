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


//rework with float cast and round speed calculculation to get rid of residual speeds that should be zero
void xySpeed(int8_t XSpeed, int8_t YSpeed)
{
	int8_t ASpeed;
	int8_t BSpeed;
	int8_t CSpeed;

	//calc motor speeds
	ASpeed = (2 * XSpeed) / 3;
	
	BSpeed = ( YSpeed / (2 * cos(30) ) ) - (XSpeed/3);

	CSpeed = -ASpeed - BSpeed;

	//enforce minimum speeds
	(ASpeed <= MIN_SPEED)? ASpeed = 0 : 1;
        (BSpeed <= MIN_SPEED)? BSpeed = 0 : 1; 
        (CSpeed <= MIN_SPEED)? CSpeed = 0 : 1; 

	// Speed >> 1, then Speed << 1 to try to get rid of any residual speed that sould not be there
	motorSpeed(MOTOR_1, ASpeed);
        motorSpeed(MOTOR_2, BSpeed);
        motorSpeed(MOTOR_3, CSpeed);
}

void spin(int8_t Spin)
{
       //spin is clockwise as positive

        motorSpeed(MOTOR_1, Spin);
        motorSpeed(MOTOR_2, Spin);
        motorSpeed(MOTOR_3, Spin);

}

void moveSpin(int8_t XSpeed, int8_t YSpeed, int8_t Spin)
{
       //spin is clockwise as positive

        int8_t ASpeed;
        int8_t BSpeed;
        int8_t CSpeed;

	BSpeed = ( (Spin - XSpeed)/3 ) - ( YSpeed/(2 * cos(30) ) );
	CSpeed = ( (Spin - XSpeed)/3 ) + ( YSpeed/(2 * cos(30) ) );
	ASpeed = Spin - BSpeed - CSpeed;

	motorSpeed(MOTOR_1, ASpeed);
        motorSpeed(MOTOR_2, BSpeed);
        motorSpeed(MOTOR_3, CSpeed);

}

void vectorMove(uint8_t Velocity, int16_t Heading, int8_t Spin)
{
	//Heading is given as degrees clockwise from direct ahead
	//spin is clockwise as positive

	int8_t XSpeed;
	int8_t YSpeed;

	XSpeed = Velocity * cosf((float)Heading);
        YSpeed = Velocity * sinf((float)Heading);

	moveSpin(
		XSpeed,
		YSpeed,
		Spin
		);
}

void stopMotor(uint8_t Motor)
{
	write12(Motor, 0);
}

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

	printf("X is: %d\nY is: %d\n\n", XSpeed, YSpeed);

	int8_t ASpeed;
	int8_t BSpeed;
	int8_t CSpeed;

	//calc motor speeds
	ASpeed = (2 * XSpeed) / 3;
	
	BSpeed = ( YSpeed / (2 * cos(PI/6) ) ) - (XSpeed/3);

	CSpeed = -ASpeed - BSpeed;

	//enforce minimum speeds
	(ASpeed <= MIN_SPEED)? ASpeed = 0 : 1;
        (BSpeed <= MIN_SPEED)? BSpeed = 0 : 1;
        (CSpeed <= MIN_SPEED)? CSpeed = 0 : 1;

	// Speed >> 1, then Speed << 1 to try to get rid of any residual speed that sould not be there
	printf("A is: %d\nB is: %d\nC is: %d\n\n", ASpeed, BSpeed, CSpeed);
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

	BSpeed = ( (Spin - XSpeed)/3 ) - ( YSpeed/(2 * cos(PI/6) ) );
	CSpeed = ( (Spin - XSpeed)/3 ) + ( YSpeed/(2 * cos(PI/6) ) );
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

	Heading = (Heading * PI) / 180;//convert to radians

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

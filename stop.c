#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "omni.h"


int main( void)
{
	initController();

/*	stopMotor(MOTOR_1);
        stopMotor(MOTOR_2);
        stopMotor(MOTOR_3);
*/
	STOP_ALL

	return 0;
}

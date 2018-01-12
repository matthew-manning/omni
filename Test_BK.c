#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "omni.h"


int main( void)
{
	initController();

	while(1)
	{

		motorSpeed(MOTOR_1, 60);
                motorSpeed(MOTOR_2, -60);
                sleep(1);

                motorSpeed(MOTOR_1, 0);
                motorSpeed(MOTOR_2, 0);
                sleep(1);

                motorSpeed(MOTOR_1, -60);
               motorSpeed(MOTOR_2, 60);
                sleep(1);

	}
	return 0;
}

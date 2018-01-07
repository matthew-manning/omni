#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "omni.h"


int main( void)
{
	initController();

	int8_t Speed = 0;
	uint8_t Add = 10;

	while(1)
	{

		Speed += Add;
		motorSpeed(MOTOR_1, Speed);
//		printf("speed is %d", Speed);		
		usleep(200000);
		if( (Speed > 99) || (Speed < -99) )
		{
			printf("speed is %d", Speed);
			Add *= -1;
		}

/*		motorSpeed(MOTOR_1, 25);
		sleep(1);
                motorSpeed(MOTOR_1, 60);
                sleep(1);
                motorSpeed(MOTOR_1, 100);
                sleep(1);

                motorSpeed(MOTOR_1, 0);
                sleep(1);

               motorSpeed(MOTOR_1, -25);
                sleep(1);
                motorSpeed(MOTOR_1, -60);
                sleep(1);
                motorSpeed(MOTOR_1, -100);
                sleep(1);
*/
	}
	return 0;
}

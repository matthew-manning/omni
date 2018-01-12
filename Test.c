#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "omni.h"


int main( void)
{
	initController();

	while(1)
	{

		moveSpin(60, 20, 60);
		sleep(2);

                vectorMove(60, 0, 0);
                sleep(2);

                vectorMove(60, 70, 0);
                sleep(2);

                vectorMove(60, 270, 0);
                sleep(2);

                vectorMove(0, 10, 30);
		sleep(2);

                vectorMove(0, 10, 0);
		sleep(2);



	}
	return 0;
}

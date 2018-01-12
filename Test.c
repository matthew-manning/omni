#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "omni.h"


int main( void)
{
	initController();
	while(1)
	{
/*		xySpeed(0, 60);
		sleep(2);

                xySpeed(60, 0);
		sleep(2);

                xySpeed(0, -60);
                sleep(2);

                xySpeed(-60, 0);
                sleep(2);

                xySpeed(0, 0);
                sleep(2);
*/

		spin(60);
		sleep(2);

                spin(0);
                sleep(2);

                spin(-60);
                sleep(2);

                spin(0);
                sleep(2);

	}
	return 0;
}

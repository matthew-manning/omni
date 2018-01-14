#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "omni.h"


int main( void)
{
	initController();

//	while(1)
//	{

//		xyTravel(100, 250, 60);
		vectorMove(0, 60, 0);
		sleep(2);

//              xyTravel(300, -400, 60);
                vectorMove(90, 60, 0);
                sleep(2);

//              xyTravel(-100, -250, 60);
                vectorMove(180, 60, 0);
                sleep(2);

//              xyTravel(-300, 400, 60);
                vectorMove(270, 60, 0);
                sleep(2);
		STOP_ALL


//	}
	return 0;
}

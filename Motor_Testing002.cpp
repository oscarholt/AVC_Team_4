
#include <stdio.h>
#include "E101.h"
#include <time.h> 

int main(){ //basic idea:	
	init();
	set_motor(1, -255);
	set_motor(2, -255);
	sleep1(2, 0);
	set_motor(1, 0);
	set_motor(2, 0);
}

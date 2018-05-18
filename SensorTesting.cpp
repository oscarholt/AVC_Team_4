
#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
		init();
		int shortReading;
		int longReading;
		
		while(1){
			longReading = read_analog(2);
			shortReading = read_digital(0);
			printf("%s, %d\n", "Long Reading: ", longReading); //Less than 4cm is innacurate, goes over 30cm
			printf("%s, %d\n", "Short Reading: ", shortReading); //range is about 5cm from the end of the sensor, 
			sleep1(1,0);
		}
	}

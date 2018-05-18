#include <stdio.h>
#include <time.h>
#include "E101.h"

// Oscar

int main(){
		init();
		int close_reading;
		int long_reading;
		while(1){
				close_reading = read_analog(0);
				long_reading = read_analog(1);
				printf("%d\n" ,close_reading);
				printf("%d\n" ,long_reading);
				sleep1(1,0);
			}
		
	}

//Oscar

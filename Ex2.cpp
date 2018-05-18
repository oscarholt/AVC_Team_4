	#include <time.h>
	#include <stdio.h>
	#include "E101.h"
	
	int main (){
		int scanType = 1;
			init();
			char Red = get_pixel(160,120,0);
			int distance = read_digital(0);
			while(1){
				take_picture();
				middle = get_pixel(160,120,3);
				if(middle = Red){
						set_motor(0,0);
						set_motor(1,0);
						if (distance = 0){
							while(distance = 0){
								sleep1(0,5000);
								}
								while (distance = 1){
									sleep1(0,5000);
									}
								set_motor(1,255);
								set_motor(0,255);
							}
						else if(distance = 1){
								while (distance = 1){
									sleep1(0,5000)
									}
								set_motor(1,255);
								set_motor(0,255);
							}
						break;
					}
				sleep1(0,5000);
				}
				if(scanType == 1){
						
					while(scanType == 1){
						//Scan for white line
						if(scanWhite = 0;){
							scanType = 0;
							}
						}
					}
				else {
						while(scanType = 0){
							//Scan for object
							}
					}
				}
			
	}

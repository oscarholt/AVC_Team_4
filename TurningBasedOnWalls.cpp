#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
	init();

	int leftADC;
	int rightADC;
	int frontADC;
	int averageNoise = 20;  //to be researched
	int timeToTurn90Degrees = 4; //to be researched
	int closeReading = 1; //can be changed depending on short or long distance sensors used

	//Assuming left motor is motor 0 and right motor is motor 1

	while(1){
		leftADC = read_analog(0);
		rightADC = read_analog(1);
		frontADC = read_analog(2);

		//if the car reaches a wall
		if(frontADC == 1){
			set_motor(0, 0);
			set_motor(1, 0);
			sleep1(0,200000);

			//if there is a right and left wall the robot should turn 180
			if(leftADC == 1 && rightADC == 1){
				set_motor(1, -255);
				set_motor(0, 255);
				sleep1(0, 2*timeToTurn90Degrees);
				set_motor(1, 0);
				set_motor(0, 0);

			}

			//if there is a left wall but not a right wall then the robot should go right
			if(leftADC == 1){
				set_motor(1, -255);
				set_motor(0, 255);
				sleep1(0, timeToTurn90Degrees);
				set_motor(1, 0);
				set_motor(0, 0);
			}
			//if there is a right wall but not a left wall then the robot should go right
			else if(rightADC == 1){
				set_motor(1, 255);
				set_motor(0, -255);
				sleep1(0, timeToTurn90Degrees);
				set_motor(1, 0);
				set_motor(0, 0);
			}
		}

		//if there is nothing in front of the front sensor then it should go forward
		else(){			
			set_motor(0, 255);
			set_motor(1, 255);
		}

	}


return 0;}

//concept stabalising function
//if the robot is off centre then it should check its surroundings to center itself

}

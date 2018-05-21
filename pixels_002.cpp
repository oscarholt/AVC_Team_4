#include <stdio.h>
#include "E101.h"
#include <time.h> 

// Meg

int camera(){ //basic idea:	
	
	int scanline = 120; //line of pixels being analysed
	int colournumber = 3; //type of color (3 is whiteness)
	int error = 0; 
	int weight = -160; // *if we decide to change the camera resolution then this value will need to adjust to res*(-0.5)
	int whitepixels = 0;
	int rownumber = 1;
	int threshold;
	int row = 1;
	int column = 1;
	int total = 0;
	unsigned char whiteCenter;
	unsigned char whiteLeft;
	unsigned char whiteRight;
	//calculating threshold
	while(row <= 240){
		while(column <= 320){
			total += get_pixel (row, column, colournumber);
		}
	}
	threshold = (total/76800)*0.5;
	
	//calculating the error
	while(1){
		take_picture();				
		
		//Scanning the scanline row and calculating the error
		while (rownumber <= 320) {
			//storing the whiteness of each pixel along the scanline
			unsigned char pixel = get_pixel (rownumber, scanline, colournumber);
			//get three values of the pixels
			unsigned char whiteCenter = get_pixel(160,120,3);
			unsigned char whiteLeft = get_pixel(80,120,3);
			unsigned char whiteRight = get_pixel(240,120,3);
			//if the three values are all equal break the loop
			if ((whiteCenter == whiteLeft && whiteCenter == whiteRight) && whiteCenter >= threshold){ // Check if all are over the threshold
					break;
					//set boolean for other function
				}
			
			if (pixel >= threshold){ //if the current pixel is considered white
				pixel = 1;
				whitepixels = whitepixels + 1;   //if pixel is white, then increase whitepixel count by 1
				
			}
			else{ //if considered black
				pixel = 0;
			}
			
			//the pixel is multiplied by its distance from the center
			pixel = pixel*weight;
			//the error is altered accordingly
			error = error + pixel;
			
			//move to the next pixel along the scanline
			rownumber++;
			//increase weight
			weight++;
		}
		//error = error/whitepixels;
	}
	
	while (whiteCenter >= threshold){
			unsigned char whiteCenter = get_pixel(160,120,3);
			unsigned char whiteLeft = get_pixel(80,120,3);
			unsigned char whiteRight = get_pixel(240,120,3);
			set_motor(1,10);// need to be edited to suit the motor
			set_motor(2,10);// need to be edited to suit the motor
			if((whiteCenter == whiteLeft && whiteCenter == whiteRight) && whiteCenter < threshold){
				set_motor(1,0);// need to be edited to suit the motor
				set_motor(2,0);// need to be edited to suit the motor
				}
		}
	
	// Meg and Daniel - refined by Dylan and Daniel End
	
	//Oscar - Refined by Daniel
	
	double turnTimeSec;
	double turnTimeMicro;
	double errorTime;
	int scalar = 10; //to be researched
	
	//Create scalar for the error
	errorTime = scalar * error;
	turnTimeSec = errorTime/1000000;
	turnTimeMicro = errorTime-(turnTimeSec*1000000);
	
	//if the line is to the right of the center
	if (error >= 0){;
		//Set the turn amount (time) to be proportional to the error scalar
		set_motor(1, -100);
		set_motor(2, 100);
		sleep1(turnTimeSec, turnTimeMicro);
		set_motor(1, 0);
		set_motor(2, 0);
	}
	//if the line is to the left of the center
	if(error < 0){
		//Set the turn amount (time) to be proportional to the error scalar
		set_motor(1, 100);
		set_motor(2, -100);
		sleep1(turnTimeSec, turnTimeMicro);
		set_motor(1, 0);
		set_motor(2, 0);
        
        //Oscar End
	}
return 0;
}
		
		
		
		
		
		
		
		
		
		
		
	/* unsigned char left = get_pixel (80, 120, 3); 
	unsigned char middle = get_pixel (160, 120, 3);
	unsigned char right = get_pixel (240, 120, 3);
	if (left > middle){
		turn_left(); } //turn left will need to be a function 
	if (right > middle){
		turn_right();} //turn right will also need to be a function */


	
	

	
	
	
	



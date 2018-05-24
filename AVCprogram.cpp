#include <stdio.h>
#include "E101.h"
#include <time.h> 

//If there is a hard line or no line then the robot should
//rotate either 90 or 180 degrees to realign itself
//////////////////////////////////////////////////////////////////////////////////Daniel
void nintyDegree(int threshold, int speed, int scanline){
	take_picture();
	int pixelL = get_pixel (scanline, 40, 3);
	int pixelM = get_pixel (scanline, 125, 3); 
	int pixelR = get_pixel (scanline, 210, 3);  //////getting samples to check the whole picture without scanning everypixel
	
	//If there is a solid white line or a 90 degree right turn
	if(pixelM > threshold && pixelR > threshold){
		set_motor(2, speed);
		set_motor(1, speed);
		sleep1(0,200000); //Move forwards for a certain amount of time (to be researched)
		set_motor(1, 80);
		set_motor(2, -80);
		sleep1(0, 300000);  //turn to the right 90 degrees for a certain amount of time(to be researched)
		set_motor(1, 0);
		set_motor(2, 0);
		
	}
	//if there's a 90 degree turn to the left
	if(pixelL > threshold && pixelM > threshold){
		set_motor(2, speed);
		set_motor(1, speed);
		sleep1(0,200000); //Move forwards for a certain amount of time (to be researched)
		set_motor(1, -80);
		set_motor(2, 80);
		sleep1(0, 300000);  //turn to the left 90 degrees for a certain amount of time(to be researched)
		set_motor(1, 0);
		set_motor(2, 0);
		
	}
	//if theres no white line in front of the camera then it should rotate untill it finds a line
	if(pixelL < threshold && pixelM < threshold && pixelR < threshold){
		//set to rotate
		set_motor(1, -80);
		set_motor(2, 80);		
		while(pixelM < threshold){
			//scan while it rotates
			pixelM = get_pixel (scanline, 125, 3);			
		}
		//once it finds a line then stop rotating
		set_motor(1, 0);
		set_motor(2, 0);

	}
}
/////////////////////////////////////////////////////////////////////////////////
//Open002.cpp | Dan & Dyl & Osc & Meg
void open(){

	char message[10] = "Please";
	char server_addr[20] = "130.195.6.196";
		connect_to_server(server_addr, 1024);
	
		send_to_server(message);
		receive_from_server(message);
		send_to_server(message);
//		return 0;
	
}
////////////////////////////////////////////////////////////////////////////////
// red line method
void RedLineDetector();
            take_picture();
            int pixelLeft = get_pixel (scanline, 40, 0);
	        int pixelMiddle = get_pixel (scanline, 125, 0); 
	        int pixelRight = get_pixel (scanline, 210, 0);
	  if (pixelLeft > 100 && pixelMiddle > 100 &   pixelRight > 100){
		set_motor(0, 0);
			set_motor(1, 0);
			sleep1(0,200000);
			return true;
	}
	  else if (pixelLeft > 100 && pixelMiddle > 100){
	      set_motor(0, 0);
			set_motor(1, 0);
			sleep1(0,200000);
			return true;
	}
	  else if (pixelRight > 100 && pixelMiddle > 100){
	      set_motor(0, 0);
			set_motor(1, 0);
			sleep1(0,200000);
			return true;
	}
	 }
	  else if (pixelMiddle > 100){
	      set_motor(0, 0);
			set_motor(1, 0);
			sleep1(0,200000);
			return true;
	}
	



////////////////////////////////////////////////////////////////////////////////

int main(){
	init();
		

	int scanline = 200; //line of pixels being analysed
	int colournumber = 3; //type of color (3 is whiteness)
	int error = 0; 
	int weight = -160; // *if we decide to change the camera resolution then this value will need to adjust to res*(-0.5)
	int whitepixels = 0;
	int columnnumber = 0;
	int threshold;
	int row = 0;
	int column = 0;
	int speed = -30;
	//calculating threshold
	take_picture();
//	display_picture(1, 0);
	double max= 0;
	double min = 100000;
// walls 
    int leftADC;
	int rightADC;
	int frontADC;
	int averageNoise = 20;  //to be researched
	int timeToTurn90Degrees = 4; //to be researched
	int closeReading = 1; //can be changed depending on short or long distance sensors used
	
	// quad counter
	int quad = 1;
	
	
	////////////////////////////// start of program
	
	while (quad = 1){
	
	while(row <= 319){	
		column = 0;
		while(column <= 239){
			if(max < get_pixel(column, row, colournumber)){						
				max = get_pixel(column, row, colournumber);		
			}
			if(min > get_pixel(column, row, colournumber)){						
				min = get_pixel(column, row, colournumber);				
			}
			column += 1;
		}
		row+=1;
	}
	
	threshold = min +((max-min)/2);
	//printf("%s, %d,\n","Threshold: ", threshold);

	//calculating the error
	while(1){
		nintyDegree(threshold, speed, scanline);
		RedLineDetector();
		error = 0;
		columnnumber = 0;
		take_picture();
	//	display_picture(1, 0);
		weight = -160;
		
		//set_motor(1, speed);
		//set_motor(2, speed);
		//Scanning the scanline row and calculating the error
		while (columnnumber <= 239) {
			//storing the whiteness of each pixel along the scanline
			int pixel = get_pixel (scanline, columnnumber, colournumber);
		
			if (pixel >= threshold){ //if the current pixel is considered white
				pixel = 1;
				whitepixels = whitepixels + 1;   //if pixel is white, then increase whitepixel count by 1
			}
			else{ //if considered black
				pixel = 0;
			}
			
			//the pixel is multiplied by its distance from the center
			pixel = pixel*weight;
			//printf("%d, \n",weight);
			//printf("%d, \n",pixel);
			//sleep1(0,50000);
			//the error is altered accordingly
			error = error + pixel;
			
			//move to the next pixel along the scanline
			columnnumber++;
			//increase weight
			weight++;
		}
		//error = error/whitepixels;	
		//printf("%s, %d,\n", "Error ", error);
		double turnTimeSec;
		double turnTimeMicro;
		double errorTime;
		int scalar = 30; //to be researched - changed to 27 from 30
		
		//Create scalar for the error
		errorTime = scalar * error;
		if(errorTime<0){
			errorTime*=-1;
		}
		//printf("%s, %f,\n","Errortime ", errorTime);
		turnTimeSec = (int)(errorTime/1000000);
		turnTimeMicro = errorTime-(turnTimeSec*1000000);
		
		if (!(error > -200 && error < 200)) {
		//if the line is to the right of the center TURN RIGHT
			if (error >= 0){;
				//Set the turn amount (time) to be proportional to the error scalar
				set_motor(1, 80);
				set_motor(2, -80);
				sleep1(turnTimeSec, turnTimeMicro);
				//set_motor(1, 0);
				//set_motor(2, 0);
			}
			//if the line is to the left of the center TURN LEFT
			else{
				//Set the turn amount (time) to be proportional to the error scalar
				set_motor(1, -80);
				set_motor(2, 80);
				sleep1(turnTimeSec, turnTimeMicro);
				//set_motor(1, 0);
				//set_motor(2, 0);
			}
		}
		//once the robot has centered the line it will move forwards for an
		//increment of time
		set_motor(2, speed);
		set_motor(1, speed);
		//sleep1(0,200000);
		//set_motor(2, 0);
		//set_motor(1, 0);
		
		
		if (RedLineDetector() = true){
		quad++;
	}
}
	
} 



/////////////////////////////////////////////////////////////////////



while (quad = 2){
	
	leftADC = read_analog(0);
		rightADC = read_analog(1);
		frontADC = read_analog(2);
		RedLineDetector();

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
    if(RedLineDetector() = true){
		/////// STOP AND WAIT FOR GATE AND THEN AFTER CERTAIN AMOUNT OF TIME OR WHEN CANT SENSE OBJECT THE GO
	}
	}

	
}
return 0;
}




//Setup
#include <stdio.h>
#include <time.h>
#include "E101.h"

	//Function for white line camera --mostly done, may need modification after testing
	
	//Function for distance sensors --mostly done, may need modification after testing
	
	//Function for turning to find the white line  -- in theory this is done, again may need testing
//Function for white line camera --mostly done, may need modification after testing
	int WhiteLineFollow(){
		int scanline = 200; //line of pixels being analysed
		int colournumber = 3; //type of color (3 is whiteness)
		int error = 0; 
		int weight = -160; // *if we decide to change the camera resolution then this value will need to adjust to res*(-0.5)
		int whitepixels = 0;
		int columnnumber = 0;
		int threshold;
		int row = 0;
		int column = 0;
		int speed = -255;
		//calculating threshold
		take_picture();
		display_picture(1, 0);
	
		double max= 0;
		double min = 100000;
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
			error = 0;
			columnnumber = 0;
			take_picture();
			display_picture(1, 0);
			weight = -160;
		
			set_motor(1, speed);
			set_motor(2, speed);
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
			int scalar = 1000; //to be researched
		
			//Create scalar for the error
			errorTime = scalar * error;
			if(errorTime<0){
				errorTime*=-1;
			}
			//printf("%s, %f,\n","Errortime ", errorTime);
			turnTimeSec = (int)(errorTime/1000000);
			turnTimeMicro = errorTime-(turnTimeSec*1000000);
		
			if (!(error > -150 && error < 150)) {
			//if the line is to the right of the center
				if (error >= 0){;
					//Set the turn amount (time) to be proportional to the error scalar
					set_motor(1, 30);
					set_motor(2, -30);
					sleep1(turnTimeSec, turnTimeMicro);
					set_motor(1, 30);
					set_motor(2, 30);
				}
				//if the line is to the left of the center
				else{
					//Set the turn amount (time) to be proportional to the error scalar
					set_motor(1, -30);
					set_motor(2, 30);
					sleep1(turnTimeSec, turnTimeMicro);
					set_motor(1, 0);
					set_motor(2, 0);
				}
			}
			set_motor(1, speed);
			set_motor(2, speed);
			}

			}
		
	
	//Function for opening the ssh gate  -- Meg is working on this

	// Meg 

	void OpenGate(){
	 char server_addr[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6','\0'};
 	 int port = 1024;
      	char message[6] = {'P','l','e','a','s','e'}; 
		
		connect_to_server(server_addr,port);

		send_to_server(message);
	
		receive_from_server(message);
	}
	
	//Function to detect red line  -- will be similar to white line detector -- Oscar working on this?
	
	int redLineDetector(){
		
		}
	
	//Function for detecting maze start
	
	int wallDetector(){
			//Scan each distance sensor on either side
		int leftSensor = read_analog(0);
		int rightSensor = read_analog(1);
			//Return int 1 if each distance sensor has a positive reading
		if(leftSensor  == 1 && rightSensor == 1){
			return 1;
		}
		else{
			return 0;
		}
	}
	//Function for waiting for the gate to open  -- Meg can work on this

//main
int main (){
	init();
	//Loop for first quadrant - breaks when finds the orange line
	while(1){
		//OpenGate
		OpenGate();
				
		//WhiteLineError
		WhiteLineFollow();
		
		//WhiteLineError
		//TurnToFind
		//DetectOrange - breaks if detected
	}
	
	//Loop for third/fourth quadrant - doesnt break
	while(1){
		//DistanceSensorError
		//DetectRed

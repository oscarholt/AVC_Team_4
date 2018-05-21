//Setup
#include <stdio.h>
#include <time.h>
#include "E101.h"

	//Function for white line camera --mostly done, may need modification after testing
	
	//Function for distance sensors --mostly done, may need modification after testing
	
	//Function for turning to find the white line  -- in theory this is done, again may need testing
	
	//Function for opening the ssh gate  -- Meg is working on this
	
	//Function to detect red line  -- will be similar to white line detector -- Oscar working on this?
	
	int redLineDetector(){
		
		}
	
	//Function for detecting maze start
	
	int wallDetector(){
			//Scan each distance sensor on either side
		int leftSensor = read_analog(0);
		int rightSensor = read_analog(1);
			//Return int 1 if each distance sensor has a positive reading
		if(leftSensor  = 1 && rightSensor = 1){
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
		//WhiteLineError
		//TurnToFind
		//DetectOrange - breaks if detected
	}
	
	//Loop for third/fourth quadrant - doesnt break
	while(1){
		//DistanceSensorError
		//DetectRed

//Setup
#include <stdio.h>
#include <time.h>
#include "E101.h"

///////////////////////////////////////////////////////////////////////////////
        //Function for opening the ssh gate

void open(){
//this function is used to open the "gate" at the start of the AVC Quadrant course - it is quadrant 1. 
        char srvr_adr[15] = {"130.195.6.196"};  //this is creating a string of characters, and initialising it to the IP address of the server.
    connect_to_server(srvr_adr, 1024);  //this is using/calling the function to connect to the server, using the parameters 'char' and 'int' to find the server and the port,
                                        //and in this case uses the char 'srvr_adr' and port 1024.
    char message[24] = {"Please"};  //again, this is char creation and initialisation 
    send_to_server(message); // password process: once connected, the program sends char string 'message' to the server,
    receive_from_server(message); // the server sends back a new message,
    send_to_server(message); // and then the message is sent back again to the server to open the gate.

}
///////////////////////////////////////////////////////////////////////////////
        int  calculateThreshold(){ // this function calculates the threshold, the value that sits between the max and min pixel values detected in the 
								//image (the image is taken in the 'adjust()' function and passed to here when this method is called. If the pixel is above the 
								//threshold, it is white, if not it is black - this is to deal with imperfect lighting conditions however because this method is 
								//called by 'calculateError()' which is called before 'take_picture()' is used in the 'adjust', so the first error will automatically 
								//use the number of white pixels so will be 1, and threshold is not used until the loop repeats itself, in which it will use the picture taken 
								//from the previous loop run.

        int max = 0;
        int min = 255; 

                for(int i = 0; i < 320; i++)
                {
                        int pixel = get_pixel(120, i, 3);

                        if(pixel > max)
                        {
                                max = pixel;
                        }else if(pixel < min){
                                min = pixel;
                        }
                }


        int threshold = (max+min)/2;

        /* Check if image is all one colour */
        if(((max-min) < 100) && max > 120)
        {
                /* image is likely to be all white so set thr to 0 */
				threshold = 0;
        }else if(((max-min) < 100) && max < 120)
        {
                /* image is likely to be all black so set thr to 255 */
                threshold = 255;
        }
        //printf("%d \n %d" , max, min);

        return threshold;
}
///////////////////////////////////////////////////////////////////////////////$
void white_pixels(int threshold, int pixels[]) //This function finds white pixels in the current image, and then puts ech one it finds into an array to 
                                               // withdraw them all out in calculateError() method. The reason the array is used is because it is a clean
                                               //and efficient way to calculate the error.
{
        for(int i = 0; i < 320; i++)
        {
                pixels[i] = 0;
                int pixel = get_pixel(120, i, 3);
                if(pixel >= threshold)
                {
                        pixels[i] = 1;
                }
                //printf("%d\n",pixels[i]);
        }
        //sleep1(10,0);
}
///////////////////////////////////////////////////////////////////////////////$
int calculateError(){ //this function calculates the error signal of the image, ie how far away the vehicle is from the white line. It does this by 
	                  // calculating how far away the white line (ie the white pixels) are away from the middle of the image; so it is splitting the
	                  //image in two, one side the pixels are given a positive count, and the other a negative, and error starts neutral and each time
	                  //a pixel is added to the error, if it is white it will be + or - 1 so the error will change and inform the speed. This is also 
	                  //"weighted" to tell how far away from the middle the line is, and adjusted to deal with the thickness of the line

        int threshold = calculateThreshold();
        int pixels[320];
        int error = 0;
        int wp = 0;

        white_pixels(threshold, pixels);


        for(int i = 0; i < 320; i++)
        {
                error += ((i-160)*(pixels[i]));
                if(pixels[i] == 1)
                {
                        wp++;
                }
                //printf("%d\n",pixels[i]);
        }

                if(wp <= 5){ //if there are no white pixels found, return error 10000
                        return 10000;
                        printf("zoom");
                        sleep1(1,0);
                        }
                else if(wp == 320){ // if there are no black pixels found, return 20000
                        return 20000;
                }
                //printf("%d\n", (error/whitepixels));
                //sleep1(10,0);
                else
                {
                return error/wp;
                }
        }

int calculate_speed() //this function sets the speed, adjusted by variable kp (a way to control speed without directly changing the motor speed).
{
        double kp = 0.25;
        double error = calculateError();
        double speed = 0.0;

        speed = (double)error * kp;
        return speed;
}
///////////////////////////////////////////////////////////////////////////////
        //Function for white line camera

        void adjust(){ //this function is for taking the error signal recieved and adjusting the separate motor speeds accordingly so that the vehicle can turn to find the white
			           //line and stay on track. This function is also where the picture is taken. 


                while(true)
                {

                        if (!(calculateError() == 20000) )
                        {
                                //set_motor(2, 60);
                                //set_motor(1, 60);
                                //sleep1(5,0);

                                take_picture();


                                double error = calculate_speed();

                                if(!(error == 10000))
                                {  //change the speed on each motor depending on the error value, if error is negative (line on left side)
                                        set_motor(2, -45 - error);    //then increase speed of the left motor, and decrease speed on the right motor, vice versa.
                                        set_motor(1, -45 + error);
                                        //printf("%f\n", error);
                                }
                                else if(error == 10000) //if there is no white line detected, reverse the robot for 0.5 seconds and check again until it is found.
                                {
                                        set_motor(2, 35);
                                        set_motor(1, 35);
                                        //sleep1(0,500000);
                                        //printf("memes");
                                }
                                else if(calculateError() == 20000)
                                {

                                }
                }
                        else
                        {
                                set_motor(2, 0);
                                set_motor(1, 0);
                                sleep1(0,500000);

                        }
				}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////$

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////$
        //Function to detect line (breaks)

bool redbreaking(){ //This unused function is to detect a red line (end of Quad C) and stop (would be carried on to the next switch).

        int columnnumber = 1;
        int redpix = 0;


        take_picture();

                while (columnnumber <= 320) {
                int Rpixel = get_pixel (120, columnnumber, 0);
				int Bpixel = get_pixel (120, columnnumber, 1);
				int Gpixel = get_pixel (120, columnnumber, 2);
                   if (Rpixel > 200 && Bpixel < 100 && Gpixel < 100){

                                redpix = redpix + 1;
                        }

                        columnnumber++;
                }

        if (redpix  > 50){

                set_motor(0,0);
                sleep1(0,200000);
                return true;
        }
        return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////$
        //Function for distance sensors

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////$



int main() //this function structures each function into a progam, so that each fucntion can be called accordingly to get throught the quads.
{
        init();
        int quad = 1;

        while(true)
        {
                switch(quad)
                {
                case 1:
                        open();
                        quad = 2;
                        break;
                case 2:
                        adjust();
                        quad = 3;
                        break;


                default:
                        set_motor(1, 0);
                        set_motor(2, 0);
                }
        }
}

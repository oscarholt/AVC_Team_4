#include <stdio.h>
#include "E101.h"
#include <time.h> 

// Meg 

int main(){
	
   char server_addr[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6','\0'};
 
   int port = 1024;
   
   char message[6] = {'P','l','e','a','s','e'}; 

		connect_to_server(server_addr,port);

		send_to_server(message);
	
		receive_from_server(message);
	
}

    int connect_to_server( char server_addr[15],int port);
	
	int send_to_server(char message[6]);
	 
    int receive_from_server(char message[24]);









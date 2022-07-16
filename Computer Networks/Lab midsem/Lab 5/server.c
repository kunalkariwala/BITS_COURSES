#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_L 2048
#define PORT 4444

void helper(int connectF)
{
	/*
	Initialising the buffer to store different strings and the exit variable string to be used for comparison
	*/
	char buffer[MAX_L];
	char exitStr[MAX_L] = ".\n";

	/*
	Infinite loop to maintain the chat and keep on accepting the messages until a break event occurs
	*/
	while(1) {
		//Prints the first line
		char introStr[MAX_L] = "Hello, what is your name?\n";
		printf("Server : %s",introStr);
		send(connectF , introStr , strlen(introStr) , 0 );

		bzero(buffer, MAX_L);

		//Reads the name
		read(connectF, buffer, sizeof(buffer));
		printf("Client : %s",buffer);

		//store the name from the buffer to a variable
		char name[MAX_L];
		strcpy(name, buffer);

		//checks if the first letter of the name entered is capital or not
		if('A'<= buffer[0] && buffer[0]<='Z') {
			//case when the first letter is capital

			char okStr[MAX_L] = "200 OK";
			//sends the confirmation of it being correct
			send(connectF, okStr , strlen(okStr) , 0 );
			printf("Server : %s\n",okStr);
			bzero(buffer, MAX_L);

			/*
			infinite loop to keep on sending continuos lines of messages until "." is entered
			*/
			while(1){
				read(connectF, buffer, sizeof(buffer));
				printf("Client : %s",buffer);
				//exit event comparator
				if(strcmp(buffer,exitStr) == 0) {
					char tyStr[MAX_L] = "Thank You, ";
					strcat(tyStr, name);
					printf("Server : %s", tyStr);
					send(connectF , tyStr, strlen(tyStr) , 0 );
					break;
				}
				bzero(buffer, MAX_L);
			}
			break;
		}

		else{
			//case when the first letter is not capital

			char errStr[MAX_L] = "500 ERROR";
			//sends the confirmation of it not being correct
			send(connectF , errStr , strlen(errStr) , 0 );
			printf("Server : %s\n",errStr);

			bzero(buffer, MAX_L);

			//reads the "." message from the client
			read(connectF, buffer, sizeof(buffer));
			printf("Client : %s",buffer);

			//compares the message and makes sure it is the exit message
			if(strcmp(buffer,exitStr) == 0) {
				char tyStr2[MAX_L] = "Thank You, ";
				strcat(tyStr2, name);
				printf("Server : %s", tyStr2);
				send(connectF, tyStr2 , strlen(tyStr2) , 0 );
				break;
			}
		}
	}
}

int main()
{
	int socketF, connectF;
	socklen_t lengthT;
	struct sockaddr_in serverAdd, clientT;

	/*
	Creating a socket
	*/
	socketF = socket(AF_INET, SOCK_STREAM, 0);
	//error handling in creating a socket
	if (socketF == -1) {
		perror("ERROR IN CREATING A SOCKET!!!");
		exit(0);
	}
	bzero(&serverAdd, sizeof(serverAdd));

	//Assigning the socket an IP Port
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAdd.sin_port = htons(PORT);

	//Binding the socket to the IP and handling the error
	if ((bind(socketF, (struct sockaddr *)&serverAdd, sizeof(serverAdd))) != 0) {
		perror("ERROR IN BINDING THE SOCKET!!!\n");
		exit(1);
	}

	printf("%s\n","SERVER IS RUNNING, WAITING FOR CLIENT TO CONNECT");

	//Opens the server for listening and error handling
	if ((listen(socketF, 5)) != 0) {
		perror("ERROR WHILE LISTENING!!!!\n");
		exit(2);
	}

	lengthT = sizeof(clientT);

	//It accepts the data from the client and error handling
	connectF = accept(socketF, (struct sockaddr *)&clientT, &lengthT);

	if (connectF < 0) {
		perror("ERROR IN ACCEPTING FROM THE CLIENT!!!\n");
		exit(3);
	}
	/*
	helper function that allows chatting to be established b/w the client and server
	*/
	helper(connectF);

	/*
	close the socket after the function exits
	*/
	close(socketF);
}

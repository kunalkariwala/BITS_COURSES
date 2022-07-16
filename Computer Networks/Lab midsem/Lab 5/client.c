#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define MAX_L 2048
#define PORT 4444
void helper(int sockfd)
{
	/*
	Initialising the buffer to store different strings and the exit variable string to be used for comparison
	*/
	char buffer[MAX_L];
	int n;
	char exitStr[MAX_L] = ".\n";

	/*
	Infinite loop to maintain the chat and keep on accepting the messages until a break event occurs
	*/
	while (1) {
		//Reads the first line from the server and prints it
		bzero(buffer, sizeof(buffer));
		read(sockfd, buffer, sizeof(buffer));
		printf("Server : %s", buffer);

		bzero(buffer, sizeof(buffer));
		printf("Client : ");
		n = 0;
		//reads the line until enter is pressed
		while ((buffer[n++] = getchar()) != '\n');
		write(sockfd, buffer, sizeof(buffer));

		bzero(buffer, sizeof(buffer));

		//Reads the response from the server
		read(sockfd, buffer, sizeof(buffer));
		//prints the response
		printf("Server : %s\n", buffer);

		if ((strcmp(buffer, "200 OK")) == 0) {
			/*
			Case when the response is "accepted"
			*/
			while(1){
				//infinite loop to depict the chatting interface until exitStr is observed
				bzero(buffer, sizeof(buffer));
				printf("Client : ");
				n = 0;
				//reads the line until enter is pressed
				while ((buffer[n++] = getchar()) != '\n');

				//writes what it read to the buffer
				write(sockfd, buffer, sizeof(buffer));

				//exit case when the line entered is "."
				if(strcmp(buffer,exitStr) == 0){
					break;
				}
			}
			bzero(buffer, sizeof(buffer));
			read(sockfd, buffer, sizeof(buffer));
			printf("Server : %s", buffer);
			break;
		}
		/*
			Case when the response is not "accepted"
		*/
		char str[MAX_L] = ".\n";
		send(sockfd , str , strlen(str) , 0 );
		printf("Client : %s",str);

		bzero(buffer, sizeof(buffer));
		read(sockfd, buffer, sizeof(buffer));
		printf("Server : %s", buffer);

		break;
	}
}

int main()
{
	int socketF, connectF;
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
	serverAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAdd.sin_port = htons(PORT);

	//connecting the socket + error handling
	if (connect(socketF, (struct sockaddr *)&serverAdd, sizeof(serverAdd)) != 0) {
		perror("CONNECTION FAILED!!!\n");
		exit(0);
	}

	/*
	helper function that allows chatting to be established b/w the client and server
	*/
	helper(socketF);

	/*
	close the socket after the function exits
	*/
	close(socketF);
}

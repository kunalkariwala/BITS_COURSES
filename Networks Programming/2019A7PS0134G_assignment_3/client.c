#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_L 1024
int sock1;
char buffer[MAX_L];
int quit = 0;

void handle_signal_sigint(int sig){
    bzero(buffer,sizeof(buffer));
    strcpy(buffer, "quit");
    send(sock1,"quit",sizeof("quit"),0);
    quit = 1;
}


int main(int argc, char const* argv[]){
  signal(SIGINT, handle_signal_sigint);
  int portNum = atoi(argv[2]);
  char * servAdd = argv[1];
  // printf("Please enter a port number\n");
  // scanf("%d",&portNum);
  struct sockaddr_in addr;
  char revstr[MAX_L] = {0};
  char filename[MAX_L];
  char* textEnt;
  // bzero(buffer,sizeof(buffer));
  // printf("Please enter a port address\n");
  // scanf("%s",buffer);

  // Creating a new socket in the TCP mode and adding the details to the addr 
  sock1 = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(portNum);
  addr.sin_addr.s_addr = inet_addr(servAdd);

  int sizeAddr = sizeof(addr);

  int ret = connect(sock1, (struct sockaddr*)&addr, sizeAddr);

  // Connecting with error handling
  if(ret < 0){
    perror("[-]ERROR IN CONNECTING TO THE SERVER. Server may be unreachable or more than 4 clients\n");
    exit(0);
  }

  //recieves a message from the server stating whether it is accepted or not
  bzero(buffer, sizeof(buffer));
  recv(sock1, buffer, MAX_L, 0);

  //denied cause no space, close the connection
  if(strcmp(buffer,"DENIED") == 0){
    printf("[-]Conncection refused! Server is full\n");
    close(sock1);
    exit(0);
  }
  else{
    //connection accepted
    printf("[+]Connection Accepted!\n");
  }
  while(1){
    //prompts the client to enter a string.
    if(quit == 1){
      break;
    }
    printf("[+]Enter any string, type quit if you want to disconnect\n");
    if(strcmp(buffer,"quit") == 0){
      break;
    }
    if(quit == 1){
      break;
    }
    sleep(1);
	  bzero(buffer,sizeof(buffer));
	  fgets(buffer,sizeof(buffer),stdin);
    
    //function to remove the enter character
	  for(int i = 0 ; i < MAX_L;i++){
		  if(buffer[i] == '\n'){
			  buffer[i] = 0;
		  }
	  }
    //send the string that was entered, to the server
    send(sock1,buffer,MAX_L,0);

    //if the entered string is exit, close the connection.
    if(strcmp(buffer,"quit") == 0){
      break;
    }
    
  }
  return 0;
}

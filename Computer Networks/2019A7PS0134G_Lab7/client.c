#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_L 1024


int main(int argc, char const* argv[]){
  int sock1;
  int portNum = atoi(argv[2]);
  char *portAddr = argv[1];;
  struct sockaddr_in addr;
  char buffer[MAX_L];
  char revstr[MAX_L] = {0};
  char filename[MAX_L];
  char* textEnt;

  // Creating a new socket in the TCP mode and adding the details to the addr 
  sock1 = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(portNum);
  addr.sin_addr.s_addr = inet_addr(portAddr);

  int sizeAddr = sizeof(addr);

  int ret = connect(sock1, (struct sockaddr*)&addr, sizeAddr);

  if(ret < 0){
    perror("ERROR IN CONNECTING TO THE SERVER. Server may be unreachable or more than 4 clients\n");
    exit(0);
  }
  bzero(buffer, sizeof(buffer));
  recv(sock1, buffer, MAX_L, 0);

  if(strcmp(buffer,"DENIED") == 0){
    printf("Conncection refused! Server is full\n");
    close(sock1);
    exit(0);
  }
  else{
    printf("Connection Accepted!\n");
  }
  while(1){

    printf("Enter any string, type exit if you want to disconnect\n");
    scanf("%s",buffer);
    send(sock1,buffer,MAX_L,0);

    if(strcmp(buffer,"exit") == 0){
      break;
    }

    bzero(buffer, sizeof(buffer));
    recv(sock1, buffer, MAX_L, 0);
    printf("Server 2: %s\n",buffer);
    bzero(buffer, sizeof(buffer));

  }
  return 0;
}

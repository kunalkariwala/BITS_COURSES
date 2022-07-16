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
  int portNum;
  char portAddr[50];
  struct sockaddr_in addr;
  char buffer[MAX_L];
  char* fileName;
  char* textEnt;

  // Taking port input
  printf("Client : Enter the Server's Address: ");
  scanf("%s", portAddr);
  printf("Client : Enter Port: ");
  scanf("%d", &portNum);

  // Creating a new socket in the TCP mode and adding the details to the addr 
  sock1 = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(portNum);
  addr.sin_addr.s_addr = inet_addr(portAddr);

  int sizeAddr = sizeof(addr);

  if(connect(sock1, (struct sockaddr*)&addr, sizeAddr) < 0){
    perror("ERROR IN CONNECTING TO THE SERVER\n");
    exit(0);
  }

  read(sock1, buffer, MAX_L);
  printf("Client : server sent this : %s\n",buffer);

  // Asking for the file name as input
  bzero(buffer,MAX_L);
  printf("Client : Enter the file name\n");
  scanf("%s",fileName);

  // Sending File Name
  send(sock1, fileName, strlen(fileName),0);

  // Printing Response Received
  bzero(buffer,MAX_L);
  read(sock1 , textEnt , MAX_L);
  printf("Client : server sent this : %s\n",textEnt);

  //writing into the file
  FILE* filePointer = fopen(fileName,"w");

  if(filePointer == NULL){
    perror("ERROR IN CREATING A NEW FILE :(\n");
    return 0;
  }
  else{
    fputs(textEnt,filePointer);
  }

  fclose(filePointer);
  close(sock1);
  return 0;

}

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_L 1024

int main(int argc, char const *argv[]){
  int sock1, sock2;
  int portNum;
  struct sockaddr_in addr;
  FILE *filePointer;

  printf("Server: Enter the port Number: \n");
  scanf("%d", &portNum);

  //initialising the buffer with 0
  char buffer[MAX_L] = {0};

  // Creating a new socket in the TCP mode and adding the details to the addr 
  sock1 = socket(AF_INET, SOCK_STREAM, 0);

  strcpy(buffer, "127.0.0.1");

  addr.sin_family = AF_INET;
  addr.sin_port = htons(portNum);
  addr.sin_addr.s_addr = inet_addr(buffer);

  int sizeAddr = sizeof(addr);

  // Binding the address to the socket with error handling
  if(bind(sock1, (struct sockaddr *)&addr, sizeAddr) < 0){
    perror("ERROR IN BINDING TO THE SOCKET");
    return 0;
  }

  listen(sock1, 1);

  for(;;){
    //accepts requests
    sock2 = accept(sock1, (struct sockaddr *) &addr, (socklen_t *)&sizeAddr);

    if(sock2 >= 0){
      //only run for successful accept
      
      //Initialising for accepting File Name
      char fileName[100];
      memset(fileName, '\0', sizeof(fileName));

      bzero(buffer,MAX_L);
      strcpy(buffer, "Which file do you want to access?");
      printf("Server: %s\n",buffer);
      send(sock2, buffer, strlen(buffer), 0);

      // Accepting File Name
      read(sock2 , fileName , 100);
      printf("Server: client sent this : %s is to be read\n",fileName);

      filePointer = fopen(fileName,"r");
      if(filePointer == NULL){strcpy(buffer, "ERROR: THE FILE NAME DOES NOT EXIST");}
      else{
        int count = 0;
        char in = fgetc(filePointer);
        while(count<10 && in != EOF){
          buffer[count] = in;
          count++;
          in = fgetc(filePointer);
        }
        buffer[count] = '\0';
      }

      printf("Server: %s\n",buffer);
      send(sock2, buffer, MAX_L,0);

      // Closing the socket
      close(sock2);
    }
  }
  return 0;
}

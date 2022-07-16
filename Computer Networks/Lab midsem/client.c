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
  char *portAddr;
  struct sockaddr_in addr;
  char buffer[MAX_L];
  char filename[MAX_L];
  char* textEnt;

    portNum = atoi(argv[1]);
    portAddr = argv[2];

  // Creating a new socket in the TCP mode and adding the details to the addr 
  sock1 = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(portNum);
  addr.sin_addr.s_addr = inet_addr(portAddr);

  int sizeAddr = sizeof(addr);

  if(connect(sock1, (struct sockaddr*)&addr, sizeAddr) < 0){
    perror("ERROR IN CONNECTING TO THE SERVER. Server may be unreachable\n");
    exit(0);
  }

  read(sock1, buffer, MAX_L);
  printf("Client : server sent this : %s\n",buffer);

  // Asking for the file name as input
  bzero(buffer,MAX_L);
  printf("Client : Enter your campus ID\n");
  scanf("%s",buffer);
  strcpy(filename,buffer);

  // Sending campus ID
  send(sock1, buffer, strlen(buffer),0);

    char calcval[MAX_L];
    bzero(buffer,MAX_L);
    read(sock1, buffer, MAX_L);
    strcpy(calcval,buffer);

    printf("Client : the value of calcval is: %s\n",calcval);

    char studname[MAX_L];
    bzero(buffer,MAX_L);
    read(sock1, buffer, MAX_L);
    strcpy(studname,buffer);

    printf("Client: the studname is : %s\n",studname);

    char yval[MAX_L];
    bzero(buffer,MAX_L);
    read(sock1, buffer, MAX_L);
    strcpy(yval,buffer);

    printf("Client : the value of yval is: %s\n",yval);


    printf("Client : Name : %s, CAMPUS ID : %s, VALUE OF Y : %s\n",studname,filename,yval);

  close(sock1);
  return 0;

}

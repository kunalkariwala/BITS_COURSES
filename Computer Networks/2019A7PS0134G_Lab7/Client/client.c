#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_L 1024


int main(int argc, char const* argv[]){

  int sockfd;
  int port = atoi(argv[1]);
  char *portAddr = argv[2];;
  struct sockaddr_in addr;
  char buffer[MAX_L];
  char filename[MAX_L];
  char* textEnt;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(portAddr);

  int sizeAddr = sizeof(addr);

  int ret = connect(sockfd, (struct sockaddr*)&addr, sizeAddr);

  bzero(buffer, sizeof(buffer));
  recv(sockfd, buffer, MAX_L, 0);
  printf("This is what was recieved : %s\n",buffer);

  if(strcmp(buffer,"accept") == 0){
    printf("Accepted!\n");
  }

  else{
    printf("Server is full\n");
    close(sockfd);
    exit(0);
  }

  for(;;){

    printf("Enter any string\n");
    scanf("%s",buffer);
    send(sockfd,buffer,MAX_L,0);

    if(strcmp(buffer,"exit") == 0){
      break;
    }

    bzero(buffer, sizeof(buffer));
    recv(sockfd, buffer, MAX_L, 0);
    
    printf("Server 2: %s\n",buffer);
    bzero(buffer, sizeof(buffer));

  }
  return 0;
}

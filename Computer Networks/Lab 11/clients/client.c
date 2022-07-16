#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_L 1024
int sock1,ret;
char buffer[MAX_L];
int quit = 0;
int sent = 0;
int both = 0;

char clientID[MAX_L];

#define NUMTHREAD 2
pthread_t tid[NUMTHREAD];

//defining the struct that will be passed to every thread
typedef struct threadstruct{
  int index;
  int newSocket;
  struct sockaddr_in clientAddr;
} threadstruct;


void handle_signal_sigint(int sig){
    bzero(buffer,sizeof(buffer));
    strcpy(buffer, "quit");
    send(sock1,"quit",sizeof("quit"),0);
    quit = 1;
}

void * senderThread(void * args){
  while (1)
  {
    if(both == 1){
      printf("[+] Both clients are connected. Enter file name or type quit to quit: \n");
      bzero(buffer,sizeof(buffer));
      scanf("%s",buffer);
      send(sock1,buffer,MAX_L,0);
      if (strcasecmp(buffer, "quit") == 0) {
        ret = 1;
        printf("[-] Connection closed!\n");
        break;
      }
    }
  }
  
}

void * receiverThread(void * args){
  while(1){
    bzero(buffer,sizeof(buffer));
    recv(sock1,buffer,MAX_L,0);
    if(strcasecmp(buffer,"")== 0 || strcasecmp(buffer," ") == 0){continue;}
    if(strcasecmp(buffer,"BOTH") == 0){both = 1;continue;}
    else if(both == 1){
      printf("The text recieved was :- %s\n",buffer);
    }
  }
}


int main(int argc, char const* argv[]){
  signal(SIGINT, handle_signal_sigint);
  int portNum = atoi(argv[2]);
  char * servAdd = argv[1];

  struct sockaddr_in addr;
  char revstr[MAX_L] = {0};
  char filename[MAX_L];
  char* textEnt;


  // Creating a new socket in the TCP mode and adding the details to the addr 
  sock1 = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(portNum);
  addr.sin_addr.s_addr = inet_addr(servAdd);

  int sizeAddr = sizeof(addr);
  int ret2 = connect(sock1, (struct sockaddr*)&addr, sizeAddr);

  // Connecting with error handling
  if(ret2 < 0){
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
  pthread_create(&tid[0], NULL,senderThread,NULL);
  pthread_create(&tid[1], NULL,receiverThread,NULL);
  while(1){
    if(ret == 1){close(sock1);printf("[-] Connection closed!\n");break;}
  }
  return 0;
}

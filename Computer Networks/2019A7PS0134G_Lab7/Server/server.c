#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_L 1024
#define MAX_THREADS 4

int clienttrack[MAX_THREADS];
int clientsocks[MAX_THREADS];
int clientmess[MAX_THREADS];
int messsent = 0;

typedef struct threadTemp{
  int newSocket;
  int index;
  struct sockaddr_in clientAddr;
} threadTemp;


void reverse(char *s)
{

  //implement reverse

}

void * sendToAll(void * args){
  char buffer[MAX_L];
  for (;;)
  {
    int atone = 0;
    for(int i = 0 ; i < MAX_THREADS;i++){if(clienttrack[i] != 0){atone = 1;}}
      while(atone){
        int sentmessages = 0;
        for(int i  = 0; i < MAX_THREADS;i++){
          if(clientmess[i]!=0){
            sentmessages;
          }
        }
        if(sentmessages >= 1){
          bzero(buffer,sizeof(buffer));
          printf("Enter the broadcast message to send to all the clients:-\n");
          scanf("%s",buffer);
          reverse(buffer);
          for(int i = 0 ; i < MAX_THREADS;i++){
            if(clientsocks[i]!=0){
              send(clientsocks[i],buffer,strlen(buffer),0);
              clientmess[i] = 0;
            }
          }
          messsent = 0;
          break;
        }
      }
  }
}


void * socketThread(void * args){
  threadTemp * t = (threadTemp *)args;
  int sockfd = t->newSocket;
  int portNum = ntohs(t->clientAddr.sin_port);
  char * ip = inet_ntoa(t->clientAddr.sin_addr);
  int index = t->index;
  char globbuff[MAX_L] = {0};
  for(;;){
    if(clientmess[index] == 0){
      sleep(1);
      bzero(globbuff, sizeof(globbuff));
      recv(sockfd, globbuff, MAX_L, 0);
      clientmess[index] = 1;
      if(strcmp(globbuff,"exit") == 0){
        break;
      }
      else{
        reverse(globbuff);
        printf("Client with ip:port as %s:%d sent : %s\n",ip,portNum,globbuff);
        bzero(globbuff, sizeof(globbuff));
      }
    }
  }  
  clienttrack[index] = 0;
}


int main(int argc, char const *argv[]){
  int sock1, sock2;
  memset(clienttrack,0,sizeof(clienttrack));
  memset(clientsocks,0,sizeof(clientsocks));
  memset(clientmess,0,sizeof(clientmess));
  int port = atoi(argv[1]);;
  struct sockaddr_in addr;
  struct sockaddr_in clientAddr;
  socklen_t clientAddr_Size;
  char buffer[MAX_L];
  sock1 = socket(AF_INET, SOCK_STREAM, 0);

  strcpy(buffer, "0.0.0.0");

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(buffer);

  int sizeAddr = sizeof(addr);

  // Binding the address to the socket with error handling
  bind(sock1, (struct sockaddr *)&addr, sizeAddr);
  listen(sock1, 1);
  printf("Server is listening\n");

  pthread_t threadId[MAX_THREADS+1];
  // pthread_create(&threadId[MAX_THREADS],NULL,sendToAll,NULL);
  int index = 0;
  int i;
  for(;;){
    sock2 = accept(sock1, (struct sockaddr *) &clientAddr, &clientAddr_Size);
    if(sock2 < 0){
      printf("Tried but failed\n");
      continue;
    }
    printf("Great, client accepted!\n");
    for(i = 0 ; i < MAX_THREADS;i++){
      if(clienttrack[i] == -1){
        break;
      }
    }
    if(i == MAX_THREADS){
      strcpy(buffer, "deny");
      send(sock2, buffer, strlen(buffer), 0);
      bzero(buffer, sizeof(buffer));
    }
    else{
      strcpy(buffer, "accept");
      send(sock2, buffer, strlen(buffer), 0);
      bzero(buffer, sizeof(buffer));
      clienttrack[i] = 1;
      clientsocks[i] = sock2;
      threadTemp * temp = malloc (sizeof (threadTemp));
      temp->index = i;
      temp->newSocket = sock2;
      temp->clientAddr = clientAddr;
      pthread_create(&threadId[i], NULL,socketThread, (void *)temp);
    }

  }
  return 0;
}

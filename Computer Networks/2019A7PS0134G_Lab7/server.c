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

int clienttrack[MAX_THREADS] = {0};
int clientsocks[MAX_THREADS] = {0};
int clientmess[MAX_THREADS] = {0};
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
  char buffer[MAX_L] = {0};
  while (1)
  {
    int atone = 0;
    for(int i = 0 ; i < MAX_THREADS;i++){
      if(clienttrack[i] != 0){
        atone = 1;
        break;
      }
    }
      while(atone){
        int activeconn = 0;
        for(int i = 0; i < MAX_THREADS;i++){
          if(clienttrack[i] != 0){
            activeconn++;
          }
        }
        int sentmess = 0;
        for(int i  = 0; i < MAX_THREADS;i++){
          if(clientmess[i]!=0){
            sentmess++;
          }
        }
        if(sentmess == activeconn){
          sleep(1);
          bzero(buffer,sizeof(buffer));
          printf("All clients have sent a message. Enter the message to send to all the clients:-\n");
          scanf("%s",buffer);
          reverse(buffer);
          for(int i = 0 ; i < MAX_THREADS;i++){
            if(clientsocks[i]==0){
              continue;
            }
            else{
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
  int newsock = t->newSocket;
  int port = ntohs(t->clientAddr.sin_port);
  char * ip = inet_ntoa(t->clientAddr.sin_addr);
  int index = t->index;
  printf("Connection accepted from %s:%d\n", ip, port);
  char globbuff[MAX_L] = {0};
  while(1){
    if(clientmess[index] == 0){
      sleep(1);
      bzero(globbuff, sizeof(globbuff));
      recv(newsock, globbuff, MAX_L, 0);
      clientmess[index] = 1;
      if(strcmp(globbuff,"exit") == 0){
        printf("Client with ip:port as %s:%d has safely exited\n", ip,port);
        break;
      }
      else{
        reverse(globbuff);
        printf("Client with ip:port as %s:%d sent : %s\n",ip,port,globbuff);
        bzero(globbuff, sizeof(globbuff));
      }
    }
  }  
  clienttrack[index] = 0;
}


int main(int argc, char const *argv[]){
  int sock1, sock2;
  int portNum = atoi(argv[1]);;
  struct sockaddr_in addr;
  struct sockaddr_in clientAddr;
  socklen_t clientAddr_Size;


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

  pthread_t tid[MAX_THREADS];
  pthread_t forall;
  // pthread_create(&forall,NULL,sendToAll,NULL);
  int index = 0;
  int i;
  for(;;){
    sock2 = accept(sock1, (struct sockaddr *) &clientAddr, &clientAddr_Size);
    if(sock2 < 0){
      continue;
    }
    for(i = 0 ; i < MAX_THREADS;i++){
      if(clienttrack[i] == -1){
        break;
      }
    }
    if(i == MAX_THREADS){
      strcpy(buffer, "DENIED");
      send(sock2, buffer, strlen(buffer), 0);
      bzero(buffer, sizeof(buffer));
    }
    else{
      strcpy(buffer, "ACCEPTED");
      send(sock2, buffer, strlen(buffer), 0);
      bzero(buffer, sizeof(buffer));
      clienttrack[i] = 1;
      clientsocks[i] = sock2;
      sleep(1);
      threadTemp * temp = malloc (sizeof (threadTemp));
      temp->index = i;
      temp->newSocket = sock2;
      temp->clientAddr = clientAddr;
      // temp->portNum = cl
      pthread_create(&tid[i], NULL,socketThread, (void *)temp);
    }

  }
  return 0;
}

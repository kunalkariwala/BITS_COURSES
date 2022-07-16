#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_L 1024
#define NUMTHREAD 5


//global arrays to store the sockets, to keep a track of how many active connections there are 
//and how many have sent a message already
// int CLIENT_TRACKER[NUMTHREAD];

int CLIENT_SOCKETS[NUMTHREAD];
pthread_t tid[NUMTHREAD];

//defining the struct that will be passed to every thread
typedef struct threadstruct{
  int index;
  int newSocket;
  struct sockaddr_in clientAddr;
} threadstruct;

//thread function to be attached to every time a new client is accepted
void * socketThread(void * args){
  threadstruct * t = (threadstruct *)args;
  int newsock = t->newSocket;
  int port = ntohs(t->clientAddr.sin_port);
  char * ip = inet_ntoa(t->clientAddr.sin_addr);
  int index = t->index;
  FILE *filePointer;
  //printing acceptance message
  printf("[+]Connection accepted from %s:%d\n", ip, port);
  char globbuff[MAX_L] = {0};

  //this will always run for the client to get a chatbot kind of experience
  while(1){
    //receive the message sent by the client
      bzero(globbuff, sizeof(globbuff));
      recv(newsock, globbuff, MAX_L, 0);
      // while(globbuff[0] != ' ');
      //check if the message is quit
      if(strcmp(globbuff,"quit") == 0){
        //if it is exit, stop the connection
        printf("[+]Client with ip:port as %s:%d has safely exited\n", ip,port);
        break;
      }else{
        //else print the message sent by the client but in reverse
        printf("[+]Thread at tid = %d recieved the filename as %s from Client with ip:port as %s:%d \n",tid[index],globbuff,ip,port);

        filePointer = fopen(globbuff,"r");
        bzero(globbuff, sizeof(globbuff));
        int count = 0;
        if(filePointer == NULL){
          bzero(globbuff,MAX_L);
          send(newsock, globbuff, MAX_L,0);
        }
        else{
          char in = fgetc(filePointer);
          while(in != EOF){
            printf("YESS\n");
            globbuff[count] = in;
            count++;
            if(count == MAX_L - 1){
              globbuff[count] = '\0';
              send(newsock, globbuff, MAX_L,0);
              bzero(globbuff,MAX_L);
              count = 0;
            }
            in = fgetc(filePointer);
          }
          if(count > 0){
            globbuff[count] = '\0';
            send(newsock, globbuff, MAX_L,0);
          }
          bzero(globbuff,MAX_L);
          strcpy(globbuff,"endoffile");
          send(newsock, globbuff, MAX_L,0);
        }
      }

  }  
  //once a client exits, we create space for a new connection to happen
  CLIENT_SOCKETS[index] = -1;
}


int main(int argc, char const *argv[]){
  //create sockets for the connection
  int sock1, sock2;
  //initialise the arrays with -1
  memset(CLIENT_SOCKETS,-1,sizeof(CLIENT_SOCKETS));
  // memset(DID_SEND_MESSAGE,-1,sizeof(DID_SEND_MESSAGE));

  //get the port num from the command line arg
  int portNum = atoi(argv[1]);

  //initiliase address structs for sockets
  struct sockaddr_in addr;
  struct sockaddr_in clientAddr;
  socklen_t clientAddr_Size;


  //initialising the buffer with 0
  char buffer[MAX_L] = {0};

  // Creating a new socket in the TCP mode and adding the details to the addr 
  sock1 = socket(AF_INET, SOCK_STREAM, 0);

  strcpy(buffer, "0.0.0.0");

  addr.sin_family = AF_INET;
  addr.sin_port = htons(portNum);
  addr.sin_addr.s_addr = inet_addr(buffer);

  int sizeAddr = sizeof(addr);

  // Binding the address to the socket with error handling
  if(bind(sock1, (struct sockaddr *)&addr, sizeAddr) < 0){
    perror("[-]error in binding!!!!");
    return 0;
  }
  
  //printing success message for server binding
  printf("[+]Server is active on [%s : %d]\n",inet_ntoa(addr.sin_addr),portNum);

  listen(sock1, 1);

  int i;
  for(;;){
    //server accepts all requests
    sock2 = accept(sock1, (struct sockaddr *) &clientAddr, &clientAddr_Size);
    if(sock2 < 0){
      //if error in accepting
      continue;
    }
    //function to find an empty spot(check whether number of active connections is less than 4)
    for(i = 0 ; i < NUMTHREAD;i++){
      if(CLIENT_SOCKETS[i] == -1){
        break;
      }
    }

    //if there are 5 already, then deny the connection to go any further and close the connection
    if(i == NUMTHREAD){
      strcpy(buffer, "DENIED");
      send(sock2, buffer, strlen(buffer), 0);
      bzero(buffer, sizeof(buffer));
    }
    else{
      //found a place, make a new thread
      strcpy(buffer, "ACCEPTED");
      send(sock2, buffer, strlen(buffer), 0);
      bzero(buffer, sizeof(buffer));

      //store the socket in the socket array for broadcast and mark its presence
      // CLIENT_TRACKER[i] = 1;
      CLIENT_SOCKETS[i] = sock2;

      threadstruct * temp = malloc (sizeof (threadstruct));
      temp->index = i;
      temp->newSocket = sock2;
      temp->clientAddr = clientAddr;

      //create the thread and start the chatting for every client
      pthread_create(&tid[i], NULL,socketThread, (void *)temp);
    }

  }
  return 0;
}

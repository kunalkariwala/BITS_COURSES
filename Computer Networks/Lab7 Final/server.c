#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_L 1024
#define NUMTHREAD 4


//global arrays to store the sockets, to keep a track of how many active connections there are 
//and how many have sent a message already
// int CLIENT_TRACKER[NUMTHREAD];
int CLIENT_SOCKETS[NUMTHREAD];
int DID_SEND_MESSAGE[NUMTHREAD];

//defining the struct that will be passed to every thread
typedef struct threadstruct{
  int index;
  int newSocket;
  struct sockaddr_in clientAddr;
} threadstruct;


//===================== string reversal function ===========================
int string_length(char *pointer)
{
   int c = 0;
 
   while( *(pointer + c) != '\0' )
      c++;
 
   return c;
}

void reverse(char *s)
{
   int length, c;
   char *begin, *end, temp;
 
   length = string_length(s);
   begin  = s;
   end    = s;
 
   for (c = 0; c < length - 1; c++)
      end++;
 
   for (c = 0; c < length/2; c++)
   {        
      temp   = *end;
      *end   = *begin;
      *begin = temp;
 
      begin++;
      end--;
   }
}
//===================== string reversal function ===========================


//function to be passed to the thread that will run in the background always
void * broadcast(void * args){
  char buffer[MAX_L] = {0};
  while (1)
  {
    while(1){
      //small sleep given to ensure that after a client exits, it still considers the socket as closed
		  sleep(1);

      //check the number of active connections 
      int activeconn = 0;
      for(int i = 0; i < NUMTHREAD;i++){
        if(CLIENT_SOCKETS[i] != -1){
          activeconn++;
        }
      }
      //if there are no active connections, we do not want to ask the server to send a broadcast
		  if(activeconn == 0){continue;}

      //checking how many active connections have sent a message already
      int sentmess = 0;
      for(int i  = 0; i < NUMTHREAD;i++){
			  if(CLIENT_SOCKETS[i] == -1){continue;}
			  if(DID_SEND_MESSAGE[i]!=-1){sentmess++;}
      }

      //only prompt the server to send a broadcast once all active connections have sent a message
      if(sentmess == activeconn){break;}
	  }
    bzero(buffer,sizeof(buffer));

    //Display a prompt on the server to input the broadcast message
    printf("[+]All clients have sent a message. Enter the message to send to all the clients:-\n");
    //get the broadcast message
	  fgets(buffer,sizeof(buffer),stdin);
    //function to remove the enter character
	  for(int i = 0 ; i < MAX_L;i++){
			if(buffer[i] == '\n'){
				buffer[i] = 0;
			}
		}
    //reversing the entered string
    reverse(buffer);

    //send the reversed message to all the active clients
    for(int i = 0 ; i < NUMTHREAD;i++){
      if(CLIENT_SOCKETS[i]==-1){
        continue;
      }
      else{
        send(CLIENT_SOCKETS[i],buffer,strlen(buffer),0);
        //once the broadcast is sent, make the sent message tracker -1
        DID_SEND_MESSAGE[i] = -1;
      }
    }
  }
}

//thread function to be attached to every time a new client is accepted
void * socketThread(void * args){
  threadstruct * t = (threadstruct *)args;
  int newsock = t->newSocket;
  int port = ntohs(t->clientAddr.sin_port);
  char * ip = inet_ntoa(t->clientAddr.sin_addr);
  int index = t->index;

  //printing acceptance message
  printf("[+]Connection accepted from %s:%d\n", ip, port);
  char globbuff[MAX_L] = {0};

  //this will always run for the client to get a chatbot kind of experience
  while(1){
    //if the client has not sent a message already/ the broadcast has not happened yet
    if(DID_SEND_MESSAGE[index] == -1){

      //receive the message sent by the client
      bzero(globbuff, sizeof(globbuff));
      recv(newsock, globbuff, MAX_L, 0);

      //mark that the client sent a message already
      DID_SEND_MESSAGE[index] = 1;

      //check if the message is exit
      if(strcmp(globbuff,"exit") == 0){
        //if it is exit, stop the connection
        printf("[+]Client with ip:port as %s:%d has safely exited\n", ip,port);
		    DID_SEND_MESSAGE[index] = -1;
        break;
      }
      else{
        //else print the message sent by the client but in reverse
        reverse(globbuff);
        printf("[+]Client with ip:port as %s:%d sent : %s\n",ip,port,globbuff);
        bzero(globbuff, sizeof(globbuff));
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
  memset(DID_SEND_MESSAGE,-1,sizeof(DID_SEND_MESSAGE));

  //get the port num from the command line arg
  int portNum = atoi(argv[1]);;

  //initiliase address structs for sockets
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
    perror("[-]error in binding!!!!");
    return 0;
  }
  
  //printing success message for server binding
  printf("[+]Server is active on [127.0.0.1: %d]\n",portNum);

  listen(sock1, 1);

  pthread_t tid[NUMTHREAD];
  pthread_t forall;

  //create a background thread that sends the broadcast message, from the server to all clients
  pthread_create(&forall,NULL,broadcast,NULL);

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

    //if there are 4 already, then deny the connection to go any further and close the connection
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

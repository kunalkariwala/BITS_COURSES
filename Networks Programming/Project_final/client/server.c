#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "openssl/ssl.h"
#include "openssl/err.h"

#define MAX_L 1024
#define NUMTHREAD 2


//global arrays to store the sockets, to keep a track of how many active connections there are 
//and how many have sent a message already
// int CLIENT_TRACKER[NUMTHREAD];

SSL_CTX *InitCTX(void) /*creating and setting up ssl context structure*/
{
    SSL_METHOD *method;
    SSL_CTX *ctx;
    OpenSSL_add_all_algorithms(); /* Load cryptos, et.al. */
    SSL_load_error_strings(); /* Bring in and register error messages */
    method = TLSv1_2_client_method(); /* Create new client-method instance */
    ctx = SSL_CTX_new(method); /* Create new context */
    if (ctx == NULL)
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}
void ShowCerts(SSL *ssl) /*show the ceritficates to server and match them but here we are not using any client certificate*/
{
    X509 *cert;
    char *line;
    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if (cert != NULL)
    {
        printf("Server certificates:n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %sn", line);
        free(line); /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %sn", line);
        free(line); /* free the malloc'ed string */
        X509_free(cert); /* free the malloc'ed certificate copy */
    }
    else
        printf("Info: No client certificates configured.n");
}

int CLIENT_SOCKETS[NUMTHREAD];
pthread_t tid[NUMTHREAD];
int portNums[NUMTHREAD];
int both = 0;
char * ipaddrs[NUMTHREAD];

struct headerTemp {
    int found;
    long bytes;
};

//defining the struct that will be passed to every thread
typedef struct threadstruct{
  int index;
  int newSocket;
  struct sockaddr_in clientAddr;
} threadstruct;

void * allThread(void * args){
  while(1){
    if(CLIENT_SOCKETS[0] != -1 && CLIENT_SOCKETS[1] != -1){
      send(CLIENT_SOCKETS[0],"BOTH",sizeof("BOTH"),0);
      send(CLIENT_SOCKETS[1],"BOTH",sizeof("BOTH"),0);
      both = 1;
      break;
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
  FILE *filePointer;
  //printing acceptance message
  printf("[+]Connection accepted from %s:%d\n", ip, port);
  
  char str[MAX_L];
  bzero(str,sizeof(str));
  sprintf(str, "%d", tid[index]);

  printf("Client number %d is connected at thread with tid = %s\n",index,str);
  while(both == 0);

  char globbuff[MAX_L] = {0};
  while (1){
    bzero(globbuff, sizeof(globbuff));
    recv(newsock, globbuff, MAX_L, 0);
    if(strcasecmp(globbuff,"quit") == 0){
      printf("[+]Client with ip:port as %s:%d has safely exited\n", ip,port);
      break;
    }
    char filename [MAX_L];
    bzero(filename,sizeof(filename));
    strcat(filename,str);
    strcat(filename,"_");
    // strcat(filename,(unsigned long)time(NULL));
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strcat(filename,asctime(timeinfo));
    for(int i = 0 ; i < MAX_L;i++){
        if(filename[i] == ' '){
            filename[i] = '_';
        }
        else if(filename[i] == '\n'){
            filename[i] = ' ';
        }
    }
    strcat(filename,".txt");
    FILE *file = fopen(filename, "wb");
    printf("%s\n",filename);
    fprintf(file,"%s",globbuff);
    fclose(file);

    if(index == 0){
        printf("Message sent by client %d to client 1 with thread id %d with ip as [%s , %d]\n",index,tid[1],ipaddrs[1],portNums[1]);
        send(CLIENT_SOCKETS[1],globbuff,sizeof(globbuff),0);
    }
    else{
        printf("Message sent by client %d to client 0 with thread id %d with ip as [%s , %d]\n",index,tid[0],ipaddrs[0],portNums[0]);
        send(CLIENT_SOCKETS[0],globbuff,sizeof(globbuff),0);
    }
  }
  //once a client exits, we create space for a new connection to happen
  CLIENT_SOCKETS[index] = -1;
  portNums[index] = -1;
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

  pthread_t all;
  pthread_create(&all, NULL,allThread,NULL);
  
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
      portNums[i] = ntohs(clientAddr.sin_port);
      ipaddrs[i] = inet_ntoa(clientAddr.sin_addr);
      //create the thread and start the chatting for every client
      pthread_create(&tid[i], NULL,socketThread, (void *)temp);
    }

  }
  return 0;
}

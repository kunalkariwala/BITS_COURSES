#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>

#define BUFFER_SIZE 1024*1024

int main(int argc, char const *argv[]){

  // Setting up required variables
  int server_fd, new_sock, port, i, j,con_len = 0, cnt = 0, PORT = 80;
  char addr[30] = {0}, host[100] = {0}, filePath[500] = {0};
  struct sockaddr_in address;
  unsigned char buffer[BUFFER_SIZE] = {0}, bkp[BUFFER_SIZE] = {0};
  SSL *conn;

  // Removing http:// or https://
  if(strstr(argv[1], "http://") != NULL){
    argv[1]+=7;
  }else if(strstr(argv[1], "https://") != NULL){
    argv[1]+=8;
    PORT = 443;
  }
  // Isolating host name for Lookup
  for(i = 0; i < strlen(argv[1]); i++){
    host[i] = argv[1][i];
    if(argv[1][i] == '/'){
      host[i] = 0;
      break;
    }
  }
  // Isolating File Path
  j = i+1;
  for(i = j; i < strlen(argv[1]); i++){
    filePath[i-j] = argv[1][i];
  }
  filePath[i-j] = 0;
  // Isolating File name
  char * file = filePath;
  for(i = 0, j = -1; i < strlen(filePath); i++){
    if(filePath[i] == '/'){
      j = i;
    }
  }
  file += j+1;
  printf("%s\n", file);


  // Lookup for IP using host name
  struct hostent * record = gethostbyname(host);
	if(record == NULL)
	{
		printf("%s is unavailable\n", argv[1]);
		exit(1);
	}
	struct in_addr * address_t = (struct in_addr * )record->h_addr;
	strcpy(addr, inet_ntoa(* address_t));

  // Printing the Result of Lookup
  printf("IP Address of %s: %s:%d\n", host, addr, PORT);


  // Setting up a new socket with the TCP mode
  server_fd = socket(AF_INET, SOCK_STREAM, 0);

  // Populating the family and port in the address struct
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = inet_addr(addr);

  // Indepedent variable is required for the size of the address
  int add_len = sizeof(address);

  // Attempting a Connection
  int r = connect(server_fd, (struct sockaddr*)&address, add_len);


  // SSL setup
  if(PORT == 443){
    SSL_load_error_strings ();
    SSL_library_init ();
    SSL_CTX *ssl_ctx = SSL_CTX_new (SSLv23_client_method ());
    conn = SSL_new(ssl_ctx);
    SSL_set_fd(conn, server_fd);
    int err = SSL_connect(conn);
  }

  if(r < 0){
    printf("Sever Unreachable\n");
    exit(0);
  }
  sprintf(buffer, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", filePath, record->h_name);
  printf("%s", buffer);

  // Sending Request
  if(PORT == 80){
    send(server_fd, buffer, strlen(buffer),0);
  }else{
    SSL_write(conn, buffer, strlen(buffer));
  }


  while (buffer[0] != '\r' || buffer[1] != '\n') {
      i = 0;
      bzero(buffer,BUFFER_SIZE);

      // Reading Each Line of the Response
      while(1){
        if(PORT == 80){
          read(server_fd, &buffer[i], 1);
        }else{
          SSL_read(conn, &buffer[i], 1);
        }
        i++;
        if(buffer[i-1] == '\n' && buffer[i-2] == '\r'){
          break;
        }
      }

      buffer[i] = 0;

      // Finding Content Length
      if(strstr(buffer, "Content-Length:") != NULL){
        con_len = atoi(buffer+16);
      }else if(strstr(buffer, "content-length:") != NULL){
        con_len = atoi(buffer+16);
      }else if(strstr(buffer, "Content-length:") != NULL){
        con_len = atoi(buffer+16);
      }else if(strstr(buffer, "content-length:") != NULL){
        con_len = atoi(buffer+16);
      }
      printf("%s\n", buffer);
  }

  // Creating File
  FILE * filePointer;
  filePointer = fopen( file, "wb");

  // Writing into the File
  while(cnt < con_len){
    if(PORT == 80){
      read(server_fd, bkp, 1);
    }else{
      SSL_read(conn, bkp, 1);
    }

    fprintf(filePointer, "%c", bkp[0]);
    cnt++;
  }

  fclose(filePointer);

  // Closing Connection
  close(server_fd);

  return 0;

}

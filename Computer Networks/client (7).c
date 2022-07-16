#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include<openssl/ssl.h>
#define MAX_LEN 100000
#define PORT_NUM 443
int firstTime = 1;
// utility function to get the IP address of the url we receive.
int getIpFromUrl(char * url, char* urlIP)
{
	struct hostent *host;
	struct in_addr **addr_list;
	int i;
    
		
	host = gethostbyname( url );
	
    if(!host){
        printf("Could not resolve hostname\n");
        return 0;
    }

    //get the list of addresses that we get from gethostbyname.
	addr_list = (struct in_addr **) host->h_addr_list;
    
    //copy the first non null address and return.
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		strcpy(urlIP , inet_ntoa(*addr_list[i]) );
		return 1;
	}
	
	return 0;
}
//utility function to create a file.
int writeFile(char *fileName, char *contents){
    FILE *fptr;
    if(firstTime){
        fptr = fopen(fileName, "w");
        firstTime = 0;
    }else{
        fptr = fopen(fileName, "ab");
    }
    

    if(fptr == NULL){
        printf("Error in creating file\n");
        exit(1);
    }

    fprintf(fptr, "%s", contents);
    fclose(fptr);
    return 0;
}


int main(int argc, char *argv[])
{
    // initialising variables needed for the connection
    int client_sock = 0, valread;
    struct sockaddr_in client_address;

    char buffer[MAX_LEN] = {0};
    char *url, *copy;


    bzero(buffer, sizeof(buffer));
    url = argv[1];
    strcpy(buffer, url);


    /*
    Creating a socket file descriptor. This is the first step in creating a socket.
    args: AF_INET refers to addresses from the internet
    SOCK_STREAM refers to TCP protocol
    0 refers to default protocol
    */
    client_sock = socket(AF_INET, SOCK_STREAM, 0);

    // check if there was an error in creating the server:
    if (client_sock == -1)
    {
        perror("Error creating socket\n");
        exit(0);
    }
    char ipFromHost[100]; 
    
    char *token = strtok(url, "//");
    
    char *host = strtok(NULL, "//");
    char fileName[100] = {0};
    
    char getPath[100] = {0};
    int i = 0;
    int j = 0;
    int count = 0;
    
    for(int i = 0; i < strlen(buffer); ++i){
        if(buffer[i] == '/'){
            count++;
        }
        if(count >= 3){
            getPath[j++] = buffer[i];
        }
    }

    printf("Path: %s\n", getPath);
    printf("host: %s\n", host);

    j = 0;
    if(strlen(getPath) == 0){
        printf("Not a valid http file path\n");
        exit(0);
    }
    for(j = strlen(getPath) - 1; j >=0 && getPath[j] != '/'; --j){
    }
    for(int k = j + 1; k < strlen(getPath); ++k){
        fileName[k - j - 1] = getPath[k];
    }
    printf("FileName: %s\n", fileName);
    
    //get the IP address of the host.
    int success = getIpFromUrl(host, ipFromHost); 

    if(!success){
        printf("Error in parsing address of given url\n");
        exit(EXIT_FAILURE);
    }
    printf("IP address of given url is: %s\n", ipFromHost);

    // adding attributes to the client_address struct (ip address and port number)
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(PORT_NUM);
    client_address.sin_addr.s_addr = inet_addr(ipFromHost);

   
    //connect to the server.
    int connect_val = connect(client_sock, (struct sockaddr *)&client_address, sizeof(client_address));
    if(connect_val == -1){
        perror("Error connecting to server\n");
        exit(0);
    }
    
    

    fflush(0);
    // connection error, if port is wrong, IP is wrong, or if server is unavailable.
    if (connect_val == -1)
    {
        printf("Connection Failed, server unreachable\n");
        exit(0);
    }
    
   

    char *message = "GET ";
    char *message1 = " HTTP/1.1\r\nHost: " ;
    char *message2 = "\r\n\r\n Connection: keep-alive\r\n\r\n Keep-Alive: 300\r\n";
    char *final = malloc(strlen(message) + strlen(getPath) + strlen(message1) + strlen(message2) + 1 + strlen(host));
    strcpy(final, message);
    strcat(final, getPath);
    strcat(final, message1);
    strcat(final, host);
    strcat(final, message2);
    printf("Final message:\n %s\n", final);

    bzero(buffer, sizeof(buffer));

    // sending the request to the server
    write(client_sock, final, strlen(final));

    // reading the response from the server
    int firstTime = 1;
    printf("Downloading the file...\n");
    while(1){
        valread = read(client_sock, buffer, MAX_LEN);
        if(valread == 0){
            break;
        }
        if(firstTime){
            int code;
            sscanf(buffer, "HTTP/1.1 %d", &code);
            firstTime = 0;
            if(code != 200){
                printf("Error in downloading file\n");
                printf("%s\n",buffer);
                exit(0);
            }
            
            //strip the http header from the buffer:
            char *temp = strstr(buffer, "\r\n\r\n");
            temp += 4;
            writeFile(fileName, temp);
            bzero(buffer, sizeof(buffer));
            continue;
        }
        writeFile(fileName, buffer);
        bzero(buffer, sizeof(buffer));
    }
    // close the client
    printf("File downloaded successfully\n");
    printf("Closing the connection...\n");
    close(client_sock);
    

    return 0;
}




#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_L 1024

int temp(int y, char* file_name) {
	int ans = 0;
	FILE* file;
	if ((file = fopen(file_name, "r")) == NULL) return 0;
	int cnt = 0, delim;
	while (cnt < y && (delim = fgetc(file))) {
		if ((char) delim == ';')cnt++;
	}
	char buffer[100];
	char op;
	int bp = 0;
	while ((delim = fgetc(file)) && delim >= '0' && delim <= '9') {
		buffer[bp] = (char)delim;
		bp++;
	}
	ans = atoi(buffer);
	bp = 0;
	for (int i = 0; i < 100; i++)buffer[i] = '\0';
	switch (delim) {
	case '+': op = '+'; break;
	case '-': op = '-'; break;
	case '*': op = '*'; break;
	case '/': op = '/';
	}
	while ((delim = fgetc(file)) && delim >= '0' && delim <= '9') {
		buffer[bp] = (char)delim;
		bp++;
	}
	int val = atoi(buffer);
	switch (op) {
	case '+': ans += val; break;
	case '-': ans -= val; break;
	case '*': ans *= val; break;
	case '/': ans /= val;
	}
	return ans;
}

int main(int argc, char const *argv[]){
  int sock1, sock2;
  int portNum;
  struct sockaddr_in addr;
  FILE *filePointer;

  portNum = atoi(argv[1]);

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

  for(;;){
    //accepts requests
    sock2 = accept(sock1, (struct sockaddr *) &addr, (socklen_t *)&sizeAddr);

    if(sock2 >= 0){
      //only run for successful accept
      
      //Initialising for accepting File Name
      char campId[12];
      memset(campId, '\0', sizeof(campId));

      bzero(buffer,MAX_L);
      strcpy(buffer, "Enter your campus ID");
      printf("Server: %s\n",buffer);
      send(sock2, buffer, strlen(buffer), 0);

      // Accepting File Name
      read(sock2 , campId , 100);
      printf("Server: client sent this : %s is the ID\n",campId);

    long campusID = atol(campId);

    printf("Server: The campus ID entered in int form is :- %ld \n",campusID);

    long y = (campusID%((campusID%599)+(campusID%599))/3)+98;

    printf("The value of y is :- %ld\n",y);
    int calc = temp(y,"math.txt");
    printf("The value of calc is :- %d\n",calc);

    char calval[MAX_L];
    sprintf(calval, "%d", calc);

    printf("String value of calc is : %s\n",calval);

    bzero(buffer,MAX_L);
    strcpy(buffer, calval);
    send(sock2, buffer, strlen(buffer), 0);


    //takes the input of the student name 
    char studNma[MAX_L];
    int alllower = 1;
    while(alllower == 1){
        printf("Server : Enter your name:\n");
        scanf("%s",studNma);
        printf("Server : The name entered is : %s\n",studNma);
        int tempvar = 1;
        for(int i = 0; i<strlen(studNma);i++){
            if(studNma[i] >='a' && studNma[i]<='z'){
                continue;
            }
            else{
                tempvar = 0;
            }
        }
        if(tempvar == 1){
            alllower = 0;
        }
        else{
            printf("Server : ERROR The name entered is not all lowercaps : %s\n",studNma);
        }
    }
    bzero(buffer,MAX_L);
    strcpy(buffer, studNma);
    send(sock2, buffer, strlen(buffer), 0);

    char yVal[MAX_L];
    sprintf(yVal, "%ld", y);

    printf("String value of y is : %s\n",yVal);

    bzero(buffer,MAX_L);
    strcpy(buffer, yVal);
    send(sock2, buffer, strlen(buffer), 0);


    // Closing the socket
    close(sock2);

    }
  }
  return 0;
}

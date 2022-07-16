#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

struct sockaddr_in addr;
int port;
char fname[20];
FILE* file;
char* txt; 
int ctr = 0, delim;
int sock, client_sock;
char* snd;

int main(int argc, char const* argv[]) {
	port = atoi(argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	
	bind(sock, (struct sockaddr*) &addr, sizeof(addr));
	listen(sock, 1);
	int t = sizeof(struct sockaddr_in);
	client_sock = accept(sock, (struct sockaddr*) &addr, (socklen_t*) &t);
	
	memset(fname, '\0', sizeof fname);
	recv(client_sock, fname, 20, 0);
	
	txt = malloc(11);
	if((file = fopen(fname, "r")) == NULL) snd = "";
	else {
		while (ctr < 10 && (delim = fgetc(file)) != EOF) txt[ctr++] = (char) delim;
		txt[ctr] = '\0';
		snd = txt;
	}
	
	send(client_sock, snd, strlen(snd), 0);
	return 0;
}
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int port;
char* ip;
char* fname;
char res[20];
FILE* file;
int sock;
struct sockaddr_in addr;

int main(int argc, char const* argv[]) {
	ip = argv[1];
	port = atoi(argv[2]);
	fname = argv[3];
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &addr.sin_addr);
	addr.sin_port = htons(port);
	connect(sock, (struct sockaddr*) &addr, sizeof(struct sockaddr_in));
	send(sock, fname, strlen(fname), 0);
	memset(res, '\0', 20);
	recv(sock, res, 20, 0);
	
	if((file = fopen(fname, "w")) == NULL) perror("Error writing file!");
	else fputs(res, file);
	return 0;
}
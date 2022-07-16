#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define PORT 4444

int main(int argc, char const *argv[])
{
	int server_fd, new_sock;
	struct sockaddr_in address;
	char *hello = "Hello world!";

	int addrlen = sizeof(address);
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	int bindVal = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	if (bindVal < 0)
	{
		perror("binding socket to the address failed");
		exit(EXIT_FAILURE);
	}
	int listenVal = listen(server_fd, 5);
	if (listenVal < 0)
	{
		perror("listening for connections failed");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		new_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
		char *html = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\nConnection: close\r\n\r\n";
		char *final_message = malloc(sizeof(char) * (strlen(html) + strlen(hello)));
		strcat(final_message, html);
		strcat(final_message, hello);
		printf("%s\n", final_message);

		int send_val = send(new_sock, final_message, strlen(final_message), 0);
		close(new_sock);
	}

	printf("Hello message sent to browser");
	return 0;
}

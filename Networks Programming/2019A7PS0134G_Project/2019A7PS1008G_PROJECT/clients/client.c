/**
 * IS F462 Network Programming Assignment 3
 * @author Bhargav Kulkarni
 * @id 2019A7PS1008G
 * @date 29-03-2022
 *
 * Compile as: `gcc client.c -o client -lpthread`
 */

#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define CHECK_ERROR(cond, msg) \
    do {                       \
        if ((cond)) {          \
            perror((msg));     \
            exit(0);           \
        }                      \
    } while (0)

#define ASSERT(x, msg) assert(((void)msg, x))

struct header {
    int found;
    long bytes;
};

int server_socket, ret;
struct in_addr ip_addr;
unsigned short port;
struct sockaddr_in server_addr;
char buffer[1024], response[1024];

struct header read_header(int sock) {
    struct header hdr;
    ret = recv(sock, &hdr, sizeof(struct header), 0);
    CHECK_ERROR(ret == -1, "read_header(recv)");
    hdr.found = ntohs(hdr.found);
    hdr.bytes = ntohl(hdr.bytes);
    return hdr;
}

int main(int argc, char const *argv[]) {
    ASSERT(argc == 3, "2 arguments required");

    //! Getting IP address
    ret = inet_aton(argv[1], &ip_addr);
    CHECK_ERROR(ret == 0, "inet_aton");

    //! Getting port number
    sscanf(argv[2], "%hu", &port);

    //! Creating socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    CHECK_ERROR(server_socket == -1, "socket(server_fd)");

    printf("[*] New socket created successfully.\n");

    //! Setting address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = ip_addr;
    int address_len = sizeof(server_addr);

    //! Connecting to address
    ret = connect(server_socket, (struct sockaddr *)&server_addr, address_len);
    CHECK_ERROR(ret == -1, "connect(server_fd)");

    printf("[*] Connected to server at: ");
    printf("%s:%d\n", inet_ntoa(server_addr.sin_addr),
           (int)ntohs(server_addr.sin_port));

    char test[4];
    recv(server_socket, &test, sizeof(test), 0);
    printf("[server] %s\n", test);

    while (strcmp(test, "ACK") == 0) {
        printf("[*] Enter file name: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        send(server_socket, buffer, sizeof(buffer), 0);
        if (strcasecmp(buffer, "quit") == 0) {
            break;
        }

        struct header hdr = read_header(server_socket);

        printf("[server] File%sfound.\n[server] Bytes: %ld\n",
               hdr.found ? " " : " not ", hdr.bytes);

        if (hdr.found) {
            FILE *file = fopen(buffer, "wb");
            while (hdr.bytes--) {
                unsigned char ch;
                recv(server_socket, &ch, sizeof(ch), 0);
                fputc(ch, file);
            }
            fclose(file);
        } else {
            printf("[*] File not found.\n");
        }
    }
    ret = close(server_socket);
    CHECK_ERROR(ret == -1, "close(server_fd)");
    printf("[*] Connection closed.\n");

    return 0;
}

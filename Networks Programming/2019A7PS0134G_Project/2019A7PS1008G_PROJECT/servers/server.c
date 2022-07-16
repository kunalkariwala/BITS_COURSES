/**
 * IS F462 Network Programming Assignment 3
 * @author Bhargav Kulkarni
 * @id 2019A7PS1008G
 * @date 29-03-2022
 *
 * Compile as: `gcc server.c -o server -lpthread`
 */

#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define CHECK_ERROR(cond, msg) \
    if ((cond)) {              \
        perror((msg));         \
        exit(0);               \
    }

#define ASSERT(x, msg) assert(((void)msg, x))
#define MAX_CONN 5

struct connection {
    int idx;
    int sock;
    struct sockaddr_in addr;
} args[4];

int server_socket, client_fd, ret;
unsigned short port;
char buffer[1024];
struct sockaddr_in server_addr, client_addr;

/* Shared Variables */
pthread_t client_threads[MAX_CONN];
int is_served[MAX_CONN] = {0};

void print_ip_port(struct sockaddr_in addr) {
    printf("%s:%d", inet_ntoa(addr.sin_addr), (int)ntohs(addr.sin_port));
    fflush(stdout);
}

struct header {
    int found;
    long bytes;
};

void *client_handler(void *args) {
    struct connection *conn = (struct connection *)args;

    char ACK[] = "ACK";
    send(conn->sock, &ACK, sizeof(ACK), 0);

    printf("[%ld] Waiting for file name from client at ", pthread_self());
    fflush(stdout);
    print_ip_port(conn->addr);
    printf("\n");
    fflush(stdout);

    while (1) {
        char file_name[1024];
        memset(file_name, 0, sizeof(file_name));
        recv(conn->sock, file_name, sizeof(file_name), 0);
        if (strcmp(file_name, "quit") == 0) {
            break;
        }
        printf("[%ld] File name: %s\n", pthread_self(), file_name);
        fflush(stdout);

        FILE *file = fopen(file_name, "rb");

        if (file == NULL) {
            struct header hdr = {htons(0), htonl(0)};
            send(conn->sock, &hdr, sizeof(struct header), 0);
        } else {
            struct header hdr = {htons(1), htonl(0)};
            fseek(file, 0, SEEK_END);
            long bytes_read = ftell(file);
            printf("[%ld] Bytes read: %ld\n", pthread_self(), bytes_read);
            fflush(stdout);
            hdr.bytes = htonl(bytes_read);
            send(conn->sock, &hdr, sizeof(struct header), 0);
            rewind(file);
            while (bytes_read--) {
                unsigned char ch = fgetc(file);
                send(conn->sock, &ch, sizeof(ch), 0);
            }
            fclose(file);
            printf("[%ld] File sent.\n", pthread_self());
        }
    }

    printf("[%ld] Closed connection with ", pthread_self());
    fflush(stdout);
    print_ip_port(conn->addr);

    printf("\n");
    fflush(stdout);

    close(conn->sock);
    is_served[conn->idx] = 0;
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    ASSERT(argc == 2, "1 argument required");
    //! Getting port address
    sscanf(argv[1], "%hu", &port);

    //! Creating socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    CHECK_ERROR(server_socket == -1, "socket(server_fd)")
    printf("[*] New socket created successfully.\n");
    fflush(stdout);

    char host_name[1024];
    struct hostent *host_entry;

    //! Setting address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    int address_len = sizeof(server_addr);

    //! Binding socket to address
    ret = bind(server_socket, (struct sockaddr *)&server_addr, address_len);
    CHECK_ERROR(ret == -1, "bind(server_fd)")
    printf("[*] Socket bound successfully to address: ");
    fflush(stdout);

    ret = gethostname(host_name, sizeof(host_name));
    host_entry = gethostbyname(host_name);
    printf("%s:%d\n", inet_ntoa(*((struct in_addr *)host_entry->h_addr)), port);
    fflush(stdout);

    //! Setting socket to passive
    ret = listen(server_socket, SOMAXCONN);
    CHECK_ERROR(ret == -1, "listen(server_fd)")
    printf("[*] Now listening for new connections...\n");
    fflush(stdout);

    int len = sizeof(client_addr);

    while (1) {
        //! Fetching connection
        //> We now need to fetch the connection in `server_fd`'s queue
        client_fd = accept(server_socket, (struct sockaddr *)&client_addr,
                           (socklen_t *)&len);
        CHECK_ERROR(client_fd == -1, "accept(server_fd)");

        int idx;
        for (idx = 0; idx < MAX_CONN; idx++)
            if (!is_served[idx]) break;

        if (idx < MAX_CONN) {
            args[idx].idx = idx;
            args[idx].sock = client_fd;
            args[idx].addr = client_addr;

            printf("\n[*] Accepted connection from client at %s:%d\n",
                   inet_ntoa(client_addr.sin_addr),
                   (int)ntohs(client_addr.sin_port));
            fflush(stdout);

            is_served[idx] = 1;
            pthread_create(&client_threads[idx], NULL, client_handler,
                           (void *)&args[idx]);
            pthread_detach(client_threads[idx]);
        } else {
            char NCK[] = "NCK";
            printf("[*] Rejecting connection. Capacity full.\n");
            fflush(stdout);
            send(client_fd, &NCK, sizeof(NCK), 0);
            ret = close(client_fd);
            CHECK_ERROR(ret == -1, "close(client_fd)")
        }
    }

    //! Closing connections and file streams
    ret = close(server_socket);
    CHECK_ERROR(ret == -1, "close(server_fd)")

    printf("[*] Connection closed.\n");
    fflush(stdout);
    free(host_entry);

    return 0;
}

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SOCK_PATH "/tmp/server_socket"

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address; 
    struct sockaddr_un client_address; 

    unlink(SOCK_PATH);

    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    if(server_sockfd == -1) {
        perror("socket");
        exit(1);
    }

    server_address.sun_family = AF_UNIX; /* UNIX DOMAIN address  */

    strcpy(server_address.sun_path, SOCK_PATH);
    server_len = sizeof(server_address);

    if(bind(server_sockfd, (struct sockaddr *)&server_address, server_len) == -1) {
        perror("bind");
        exit(1);
    }

    if(listen(server_sockfd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    printf("server waiting for request\n");

    while(1) {
        char ch;

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
                                (struct sockaddr *) &client_address,
                                &client_len);
        read(client_sockfd, &ch, 1);
        ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd); /* close socket connection */
    }
}

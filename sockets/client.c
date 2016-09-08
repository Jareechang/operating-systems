#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SOCK_PATH "/tmp/server_socket"

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_un address; /* struct type -> UNIX domain socket addresses */
    int result;
    char ch = 'A';

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    address.sun_family = AF_UNIX; /* UNIX DOMAIN address  */

    strcpy(address.sun_path, SOCK_PATH);

    result = connect(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr_un));

    if(result == -1) {
        fprintf(stderr, "error\n");
        perror("no result\n");
        exit(1);
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server =  %c\n", ch);
    close(sockfd); /* close socket connection */
    exit(0); /* exit */
}

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

#define DEFAULT_SOCK_TYPE 0

int main()
{
    int sockfd;
    int len;
    struct sockaddr_un address; /* struct type -> UNIX domain socket addresses */
    int result;
    char ch = 'A';

    sockfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_SOCK_TYPE);

    address.sun_family = AF_UNIX; /* UNIX DOMAIN address  */
    strcpy(address.sun_path, "server socket");

    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *) &address, len);

    if(result == -1) {
        perror("no result\n");
        exit(1);
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);

    printf("char from server %c\n", ch);

    close(sockfd); /* close socket connection */
    exit(0); /* exit */
}

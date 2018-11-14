/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    struct tm * timeinfo;
    struct sockaddr_in address;
    int result;
    char ch = 'A';
    char *client_id;
    if (argc < 2)
    {
        printf("A client name argument is mandatory! \n");
        exit(0);
    }
/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */
    name = argv[1];
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client3");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    write(sockfd, &name, sizeof(name));
    read(sockfd, &timeinfo, sizeof(timeinfo));
    printf("time from server = %s\n", asctime (timeinfo));
    close(sockfd);
    exit(0);
}

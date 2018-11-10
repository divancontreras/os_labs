/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    char operation;
    int values[10];
    int numbers;
} packages;


int main(int argc, char **argv)
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    

/*  Create a socket for the client.  */

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client1");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    packages p;
    int i;
    
    if (argc < 2) {
        printf("No arguments passed");
        return -1;
    }
    
    p.operation = *argv[1];
    for (i = 2; i < argc; i++)
    {
        p.values[i-2] = atoi(argv[i]);
        printf("client send: %d \n", p.values[i-2]);
    }
    p.numbers = i - 2;
    int sum;
    write(sockfd, &p, sizeof(p));
    read(sockfd, &sum, sizeof(sum));
    printf("client recieved: %i \n", sum);
    close(sockfd);
    exit(0);
}

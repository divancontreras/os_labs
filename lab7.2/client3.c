/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char *client_id;
    if (argc < 2)
    {
        printf("A client name argument is mandatory! \n");
        exit(0);
    }
    client_id = argv[1];
    
/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) 
    {
        perror("oops: client3");
        exit(1);
    }
    int client_id;
/*  We can now read/write via sockfd.  */
    write(sockfd, &client_id, sizeof(client_id));
    write(sockfd, &parar, sizeof(parar));
    while(true)
    {
        read(sockfd, &rawtime, sizeof(time_t));
        printf("Client %d time from server = %s\n",
               client_id,
               asctime(localtime(&rawtime)));
        sleep(1);
    }
    write(sockfd, &client_id, sizeof(client_id));
    close(sockfd);
    exit(0);
}

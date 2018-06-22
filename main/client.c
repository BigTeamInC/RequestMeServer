#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "route/endpoints.h"
#include "route/constants.h"


int main(int argc,char **argv)
{
    int sockfd,n;
    char sendline[END_POINT_MAX_LENGHT];
    char recvline[1000];
    struct sockaddr_in servaddr;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8081);

    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));

    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));


    while(1)
    {
        bzero( sendline, END_POINT_MAX_LENGHT);
        bzero( recvline, 1000);
        fgets(sendline,END_POINT_MAX_LENGHT,stdin); /*stdin pour l'input standard*/

        write(sockfd,sendline,strlen(sendline)+1);
        read(sockfd,recvline,1000);
        printf("%s",recvline);
    }

}

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include "route/constants.h"
#include "route/route.cpp"
#include "route/route.h"


char* buildRequestUrl(){

    char sendline[END_POINT_MAX_LENGHT];
    char * apiAddress = "https://127.0.0.1:8081/propeller?";
    char * apiRequestAddress = malloc(sizeof(char) * 20);

    bzero( sendline, END_POINT_MAX_LENGHT);
    fgets(sendline,END_POINT_MAX_LENGHT,stdin);

    strcpy(apiRequestAddress, apiAddress);
    strcat(apiRequestAddress, sendline);

    return apiRequestAddress;
}

int main(int argc,char **argv) {

    int sockfd,n;
    char sendline[END_POINT_MAX_LENGHT];
    char recvline[100];
    struct sockaddr_in servaddr;


    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8081);

    inet_pton(AF_INET,"https://127.0.0.1",&(servaddr.sin_addr));

    int connectRes = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    if(connectRes != -1) {

        presentRoutes();

        while(1)
        {
            bzero( recvline, 100);
            char* requestUrl = buildRequestUrl();

            write(sockfd,sendline,strlen(sendline)+1);
            read(sockfd,recvline,100);
            printf("%s",recvline);
        }
    }

}
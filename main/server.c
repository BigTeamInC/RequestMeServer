#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "route/route.h"
#include "route/route.cpp"
#include "route/endpoints.h"
#include "route/constants.h"
#include "model/user.h"
#include "model/user.c"

int main() {

    char str[100];
    int listen_fd, conn_fd;

    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero( &servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(8081);

    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listen_fd, 10);

    conn_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

    if(conn_fd > 1) {
        presentRoutes();
    }

    while(1) {

        bzero( str, 100);
        read(conn_fd,str,100);

        User random;
        random = randomUser();
        printf("Echoing back - %s \n",(&random)->name);

        char *res;

        res = userToString(random);

        write(conn_fd, res, strlen(res)+1);

        free(res);
    }
}


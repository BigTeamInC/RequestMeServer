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

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

pthread_cond_t      cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;

int pthread_join(pthread_t th, void **thread_return);
void pthread_exit(void *ret);
int pthread_mutex_lock(pthread_mutex_t *mut);
int pthread_mutex_unlock(pthread_mutex_t *mut);
int pthread_mutex_destroy(pthread_mutex_t *mut);


void * thread_server (void* c) {

    printf("thread_server \n");

    int rc = 0;
    int socket = *((int*)c);
    printf("sockect %d", socket);

    char str[100];

    presentRoutes();

    while( 1 ) {

        rc = pthread_mutex_lock(&mutex);

        bzero( str, 100);
        read(socket,str,100);

        User random;
        random = randomUser();
        printf("Echoing back - %s \n",(&random)->name);

        char *res;

        res = userToString(random);

        write(socket, res, strlen(res)+1);

        free(res);

        rc = pthread_mutex_unlock(&mutex);
        close(socket);
    }

    return 0;
}


int main() {

    int socket_desc , client_sock , c ;
    struct sockaddr_in server , client;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1){
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8080 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Bind failed");
        return 1;
    }

    puts("Bind done");

    //Listen
    listen(socket_desc , 3); // 3 connection queue

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    while (1) {

        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if (client_sock < 0)
        {
            perror("Accept failed");
            return 1;
        } else {

            puts("\nConnection accepted");
            pthread_t th1;
            int rc = 0;
            rc = pthread_create(&th1, NULL, thread_server, (void*)&client_sock);
            rc = pthread_detach(th1);
            printf("created\n");
        }
    }
}


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "route/route.h"
#include "route/route.cpp"
#include "route/constants.h"
#include "model/user.h"
#include "model/user.c"
#include "model/propeller.h"
#include "model/propeller.c"
#include "api/response.c"
#include "api/response.h"
#include "api/request.h"
#include "api/request.c"


#include <string.h>
//#include <wiringPi.h>
//#include <softPwm.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>


#define MotorPin_A          4
#define MotorPin_B          5

int g_sta  = 1;
int g_dir  = 1;
int speed  = 50;

Propeller propeller;
Response response;
Request request;
int socket_desc;


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


/*______*/


void motor(int status, int dir, int speed){

    if(1 == status){
        if(1 == dir){
            digitalWrite(MotorPin_A, HIGH);
            softPwmWrite(MotorPin_B, 100-speed);
        }else{
            digitalWrite(MotorPin_A, LOW);
            softPwmWrite(MotorPin_B, speed);
        }
    }else{
        digitalWrite(MotorPin_A, HIGH);
        digitalWrite(MotorPin_B, HIGH);
    }
}

void handle_request(char para[]){
    //TODO parse request here
    request = parseRequestElements(para);
    if(request.requestSize < 2 || request.requestSize > 3) {

        setBadRequest(&response);

        char* resp = responseToString(response);
        write(socket_desc, resp, strlen(resp)+1);
        free(resp);

    } else if(strcmp(request.urlElements[request.requestSize - 1], "on") == 0) {

        //TODO put your default on speed
        setCurrentSpeed(&propeller, 10);

        char* resp = responseToString(response);
        write(socket_desc, resp, strlen(resp)+1);
        free(resp);


    } else if(strcmp(request.urlElements[request.requestSize - 1], "off") == 0) {

        setCurrentSpeed(&propeller, 0);

        setSuccess(&response);
        char* resp = responseToString(response);
        write(socket_desc, resp, strlen(resp)+1);
        free(resp);

    } else {

        char* speedString = request.urlElements[request.requestSize - 1];

        int speedInt  = atoi(speedString);

        setCurrentSpeed(&propeller, speedInt);

        setSuccess(&response);

        char* resp = responseToString(response);
        write(socket_desc, resp, strlen(resp)+1);
        free(resp);

    }

    /*
    const char * on = "on";
    const char * off = "off";
    const char * set = "set";

    char * pch;

    printf ("Splitting string \"%s\" into tokens:\n",para);

    strtok (para,"\n");

    printf (" %s  ++ \n",para);

    int index = 0;
    pch = strtok(para,"/");
    printf ("look for %s\n",pch);

    printf ("==  %d\n",  strcmp(pch, off) );

    while (pch != NULL)
    {

        if( index == 0 ){

            if(strcmp(pch, set) == 0) {
                printf("rec = set 2\n");

                pch = strtok (NULL, "/");

                int num = atoi(pch);

                if (num == 0){
                    printf ("stop\n");
                    //(0,1,0);
                } else{
                    printf ("launch\n");
                    //TODO set propeller current speed
                    //TODO write response to client here
                    speed = num;
                    //motor(1,1,num);
                }

                printf ("int = %d\n",num);
                // motor(1,1,num);

                break;
            }
        }

        index++;
        break;
    }
    */
}

int prepar_motor(){

//    if(wiringPiSetup() == -1){
//        printf("setup wiringPi failed !\n");
//        return -1;
//    }
//
//    pinMode(MotorPin_A, OUTPUT);
//    pinMode(MotorPin_B, OUTPUT);
//
//    softPwmCreate(MotorPin_B, 0, 100);
//    motor(1,1,1);
    return 0;
}

/*______*/

void * thread_server (void* c) {

    printf("thread_server \n");

    int rc = 0;
    int socket = *((int*)c);
    printf("sockect %d", socket);

    char str[100];

    while( 1 ) {


        bzero( str, 100);
        ssize_t n = read(socket,str,100);


        if(n<0){
            puts("Error reading socket");
            close(socket);
        }
        printf("Message : %s \n", str);

        //printf("%s", str);

        rc = pthread_mutex_lock(&mutex);
        handle_request(str);
        rc = pthread_mutex_unlock(&mutex);

    }

    return 0;
}


int main() {

    propeller = setPropellerUp();
    response.propeller = &propeller;


    //TODO make socket global so we can write in handleRequest()
    int client_sock , c ;
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
    server.sin_port = htons( 8081);

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Bind failed");
        return 1;
    }

    puts("Bind done");
    int init_res =  prepar_motor();
    printf("INIT = %d", init_res);

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

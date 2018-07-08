#ifndef REQUESTMESERVER_REQUEST_H
#define REQUESTMESERVER_REQUEST_H

typedef struct Request {
    char* urlElements[4];
    int requestSize;
} Request;

Request parseRequestElements(char url[]);

#endif //REQUESTMESERVER_REQUEST_H

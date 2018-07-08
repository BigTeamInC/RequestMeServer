#ifndef REQUESTMESERVER_RESPONSE_H
#define REQUESTMESERVER_RESPONSE_H

#include "../model/propeller.h"


typedef struct Response {

    char* status;
    char* message;
    Propeller *propeller;

} Response;

char* responseToString(Response response);

#endif //REQUESTMESERVER_RESPONSE_H

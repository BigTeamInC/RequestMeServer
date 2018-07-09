//
// Created by Fodé Guirassy on 08/07/2018.
//

#include "response.h"
#include "../route/constants.h"

char* responseToString(Response response) {

    char * res = malloc(sizeof(char) * 200);

    Propeller* propeller = (&response)->propeller;
    char* propellerString = propellerToString(propeller);

    strcpy(res, "{ status : ");
    strcat(res, (&response)->status);
    strcat(res, " , ");
    strcat(res,"message : ");
    strcat(res, (&response)->message);
    strcat(res, " , ");
    strcat(res, "propeller : ");
    strcat(res, propellerString);
    strcat(res, " }");

    return res;
}

void setBadRequest(Response* response) {
    response->message = BAD_REQUEST_MESSAGE;
    response->status = BAD_REQUEST_STATUS;
}

void setInternalError(Response* response){
    response->message = SERVER_ERROR_MESSAGE;
    response->status = SERVER_ERROR_STATUS;
}

void setSuccess(Response* response) {
    response->status = SUCCESS_STATUS;
    response->message = SUCCESS_MESSAGE;
}

void setForbidden(Response* response) {
    response->message  = FORBIDDEN_MESSAGE;
    response->status = FORBIDDEN_STATUS;
}
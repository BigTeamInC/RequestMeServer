//
// Created by Fodé Guirassy on 08/07/2018.
//

#include "response.h"


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

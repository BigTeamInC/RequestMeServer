#include "request.h"
#include <stdio.h>
#include <string.h>


Request parseRequestElements(char url[]) {

    Request request;
    request.requestSize = 0;
    char* urlSegment;
    urlSegment = strtok(url, "?=");

    while(urlSegment != NULL) {
        request.urlElements[request.requestSize] = urlSegment;
        request.requestSize += 1;
        urlSegment = strtok(NULL,"?=");
    }
    return request;
}

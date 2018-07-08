#include "propeller.h"

char* propellerToString(Propeller* propeller) {

    char *res = malloc(100);

    char *currentSpeed = malloc(sizeof(char) * sizeof(int) * 4 + 1);
    char *speedsArrayLength = malloc(sizeof(char) * sizeof(int) * 4 + 1);

    sprintf(currentSpeed,"%d", propeller->currentSpeed);
    sprintf(speedsArrayLength, "%d", propeller->speedsArrayLength);

    strcpy(res,"{ currentSpeed : ");
    strcat(res,currentSpeed);
    strcat(res,", ");
    strcat(res,"speedsArrayLength : ");
    strcat(res,speedsArrayLength);
    strcat(res,", ");
    strcat(res,"previousSpeeds : [");

    if(propeller->speedsArrayLength > 0) {
        for(int i = 0; i < propeller->speedsArrayLength; i++) {
            char* currentValue = malloc(sizeof(char) * sizeof(int) * 4 + 1);
            sprintf(currentValue,"%d", propeller->previousSpeeds[i]);
            strcat(res, currentValue);
            if(i != propeller->speedsArrayLength - 1) {
                strcat(res, ", ");
            }
            free(currentValue);
        }
    }

    strcat(res, "]");
    strcat(res," }");
    return res;
}


Propeller setPropellerUp() {
    Propeller propeller;
    propeller.speedsArrayLength = 0;
    propeller.currentSpeed = 0;

    //TODO tobeFree
    propeller.previousSpeeds = malloc(sizeof(int) * 1);

    return propeller;
}


void setCurrentSpeed(Propeller *propeller, int speed){
    propeller->speedsArrayLength += 1;
    propeller->currentSpeed = speed;
    propeller->previousSpeeds[propeller->speedsArrayLength] = propeller->currentSpeed;
    printf("%d\n", propeller->currentSpeed);
}


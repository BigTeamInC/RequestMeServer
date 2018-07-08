#ifndef REQUESTMESERVER_PROPELLER_H
#define REQUESTMESERVER_PROPELLER_H


typedef struct  Propeller{

    int currentSpeed;
    int speedsArrayLength;
    int *previousSpeeds;

} Propeller;

Propeller setPropellerUp();
void setCurrentSpeed(Propeller *propeller, int speed);
char* propellerToString(Propeller *propeller);

#endif //REQUESTMESERVER_PROPELLER_H

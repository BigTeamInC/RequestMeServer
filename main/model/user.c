#include "../route/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "user.h"

User randomUser() {

    User randomUser;

    time_t t;
    int namesCount = 3;
    srand((unsigned) time(NULL));
    int randomIndex = rand() % (namesCount);

    randomUser.name = names[randomIndex];
    randomUser.age = (rand() % (25 + 1 - 21 + 22));
    randomUser.money = 100;
    randomUser.description = "I am a random user created by randomUser() from user.c";

    printf("Random user data \n");
    printf("\t Name : %s \n", randomUser.name);
    printf("\t age : %d \n", randomUser.age);
    printf("\t money : %d \n", randomUser.money);
    printf("\t description : %s \n", randomUser.description);

    return randomUser;
}

char* userToString(User user) {

    char *res = malloc(1000);
    char *userAge = malloc(sizeof(char) * sizeof(int) * 4 + 1);
    char *userMoney = malloc(sizeof(char) * sizeof(int) * 4 + 1);

    sprintf(userAge,"%d", (&user)->age);
    sprintf(userMoney, "%d", (&user)->money);

    strcpy(res,"{ name : ");
    strcat(res,(&user)->name);
    strcat(res,", ");
    strcat(res,"age : ");
    strcat(res,userAge);
    strcat(res,", ");
    strcat(res,"description : ");
    strcat(res, (&user)->description);
    strcat(res,", ");
    strcat(res,"money : ");
    strcat(res,userMoney);
    strcat(res," }");

    return res;
}






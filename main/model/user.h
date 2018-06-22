#ifndef REQUESTMESERVER_USER_H
#define REQUESTMESERVER_USER_H

typedef struct  User{

    char *name;
    int age;
    int money;
    char *description;

} User;

void addNewFriend(User user, User aFriend);
void selfIntroduce(User user);
User randomUser();
char* userToString(User user);

#endif

#ifndef USERS_H
#define USERS_H

#include <stdbool.h>

struct User {
    char username[40];
    struct User* next;
};

struct User* createUser(const char* username);
void deleteUser(struct User* user);
struct User* findUser(struct User* head, const char* username);
bool addUser(struct User** head, const char* username);
void displayUsers(struct User* head);

#endif
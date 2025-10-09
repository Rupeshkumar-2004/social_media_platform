#ifndef USER_H
#define USER_H

struct User {
    char username[40];
    struct User* next;
};

struct User* createUser(const char* username);
void deleteUser(struct User* user);
struct User* findUser(struct User* head, const char* username);
void displayUsers(struct User* head);
bool addUser(struct User** head, const char* username);
bool deleteUserByUsername(struct User** head, const char* username);

#endif
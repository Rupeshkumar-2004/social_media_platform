#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "platform.h"
#include "post.h"
#include "comment.h"
#include "reply.h"
#include "users.h"

struct User* createUser(const char* username) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    if (!newUser) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newUser->username, username);
    newUser->next = NULL;
    return newUser;
}

void deleteUser(struct User* user) {
    if (user) {
        free(user);
    }
}

struct User* findUser(struct User* head, const char* username) {
    struct User* temp = head;
    while (temp) {
        if (strcmp(temp->username, username) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

bool addUser(struct User** head, const char* username) {
    if (!head || !username) return false;
    if (findUser(*head, username)) return false; // already exists
    struct User* newUser = createUser(username);
    if (!newUser) return false;
    newUser->next = *head;
    *head = newUser;
    return true;
}

void displayUsers(struct User* head) {
    struct User* temp = head;
    printf("Registered users:\n");
    while (temp) {
        printf("- %s\n", temp->username);
        temp = temp->next;
    }
}
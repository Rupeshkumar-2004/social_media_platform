#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

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

void displayUsers(struct User* head) {
    struct User* temp = head;
    while (temp) {
        printf("Username: %s\n", temp->username);
        temp = temp->next;
    }
}

bool addUser(struct User** head, const char* username) {
    if (findUser(*head, username)) {
        return false; // User already exists
    }
    struct User* newUser = createUser(username);
    if (!newUser) {
        return false; // Memory allocation failed
    }
    newUser->next = *head;
    *head = newUser;
    return true;
}

bool deleteUserByUsername(struct User** head, const char* username) {
    struct User* temp = *head;
    struct User* prev = NULL;
    while (temp) {
        if (strcmp(temp->username, username) == 0) {
            if (prev) {
                prev->next = temp->next;
            } else {
                *head = temp->next;
            }
            deleteUser(temp);
            return true;
        }
        prev = temp;
        temp = temp->next;
    }
    return false; // User not found
}
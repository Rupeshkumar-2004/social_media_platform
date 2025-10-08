#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//functions to create and manage replies to comments
#include "reply.h"  

Reply* createReply(const char* username, const char* content) {
    Reply* newReply = (Reply*)malloc(sizeof(Reply));
    if (!newReply) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newReply->username, username);
    strcpy(newReply->content, content);
    newReply->likes = 0;
    newReply->next = NULL;
    return newReply;
}

void likeReply(Reply* reply) {
    if (reply) {
        reply->likes++;
    }
}

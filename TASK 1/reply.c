#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "reply.h"  

//function to create a reply..
Reply* createReply(const char* username,const char* content) {
    Reply* newReply =(Reply*)malloc(sizeof(Reply));
    if(!newReply){
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newReply->username, username);
    strcpy(newReply->content, content);
    newReply->likes = 0;
    newReply->next = NULL;
    return newReply;
}

//function to like a reply..
void likeReply(Reply* reply) {
    if(reply) {
        reply->likes++;
    }
}

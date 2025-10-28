#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"reply.h"

// create a new reply
struct reply* create_reply(char* username, char* content){
    struct reply* new_reply=(struct reply*)malloc(sizeof(struct reply));
    if(new_reply==NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    username[strcspn(username,"\n")]=0;
    content[strcspn(content,"\n")]=0;
    new_reply->username=malloc(strlen(username)+1);
    new_reply->content=malloc(strlen(content)+1);
    strcpy(new_reply->username, username);
    strcpy(new_reply->content, content);
    new_reply->next=NULL;

    return new_reply;
}

//for freeing the allocated memory when deleted
void free_reply(struct reply* r){
    if(r==NULL){
        return;
    }
    free(r);
}
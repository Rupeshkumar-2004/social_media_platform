#include<stdlib.h>
#include<string.h>
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
    new_reply->next=NULL;

    return new_reply;
}

void free_reply(struct reply* r){
    if(r==NULL){
        return;
    }
    free(r);
}
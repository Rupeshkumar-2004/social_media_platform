#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"comment.h"


//create a comment
struct comment* create_Comment(char* username,char* content){
    struct comment* new_comment=(struct comment*)malloc(sizeof(struct comment));
    if(new_comment==NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    username[strcspn(username,"\n")]=0;
    content[strcspn(content,"\n")]=0;
    new_comment->username =malloc(strlen(username) + 1);
    new_comment->content  =malloc(strlen(content) + 1);
    new_comment->like=0;
    new_comment->replies=NULL;
    new_comment->next=NULL;

    return new_comment;
}

void free_comment(struct comment* c){
    if(c ==NULL){
        return;
    }

    struct reply* r = c->replies;
    while(r!=NULL){
        struct reply* next_reply = r->next;
        free_reply(r);
        r=next_reply;
    }

    free(c);
}
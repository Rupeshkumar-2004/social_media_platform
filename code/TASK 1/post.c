#include<stdlib.h>
#include<string.h>
#include"post.h"

// Function to create a new post
struct post* create_post(char* username,char* caption){
    struct post* new_post=(struct post*)malloc(sizeof(struct post));
    if(new_post==NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    username[strcspn(username,"\n")]='\0';
    caption[strcspn(caption,"\n")]='\0';
    new_post->username = malloc(strlen(username) + 1);
    new_post->caption  = malloc(strlen(caption) + 1);
    strcpy(new_post->username, username);
    strcpy(new_post->caption, caption);

    new_post->like=0;
    new_post->comments=NULL;
    new_post->next=NULL;

    return new_post;
}

void free_post(struct post* p){
    if(p == NULL){
        return;
    }

    free(p->username);
    free(p->caption);

    struct comment* c=p->comments;
    while(c != NULL){
        struct comment* next_comment =c->next;
        free_comment(c);
        c=next_comment;
    }

    free(p);
}
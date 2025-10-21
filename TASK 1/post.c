#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "post.h"

//function to create a post..
Post* createPost(const char* username,const char* caption) {
    Post* newPost = (Post*)malloc(sizeof(Post));
    if(!newPost){
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newPost->username, username);
    strcpy(newPost->caption, caption);
    newPost->comments = NULL;
    newPost->likes = 0;
    newPost->next = NULL;
    return newPost;
}

//function to like a post..
void likePost(Post* post) {
    if(post){
        post->likes++;
    }
}

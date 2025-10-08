#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "post.h"

Post* createPost(const char* username, const char* caption) {
    Post* newPost = (Post*)malloc(sizeof(Post));
    if (!newPost) {
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

void likePost(Post* post) {
    if (post) {
        post->likes++;
    }
}


//futher we have an option to delete a post and free memory
//futher we can implement a function to delete a comment from a post
//futher we can implement a function to unlike a post or comment
//futher we can implement a function to edit a post or comments
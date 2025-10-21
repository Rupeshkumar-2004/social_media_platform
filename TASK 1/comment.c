#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "comment.h"

Comment* createComment(const char* username, const char* content) {
    Comment* newComment = (Comment*)malloc(sizeof(Comment));
    if (!newComment) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newComment->username, username);
    strcpy(newComment->content, content);
    newComment->likes = 0;
    newComment->replies = NULL;
    newComment->next = NULL;
    return newComment;
}

void likeComment(Comment* comment) {
    if (comment) {
        comment->likes++;
    }
}
#ifndef COMMENT_H
#define COMMENT_H

#include "reply.h"

// Definition of Comment structure
typedef struct Comment{
    char username[40];
    char content[250];
    int likes;
    Reply* replies;
    struct Comment* next;
} Comment;

// Comment management functions (prototypes):
Comment* createComment(const char* username, const char* content);
void likeComment(Comment* comment);

#endif
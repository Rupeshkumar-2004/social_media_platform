#ifndef POST_H
#define POST_H

#include "comment.h"

typedef struct Post{
    char username[40];
    char caption[250];
    Comment* comments;
    int likes;
    struct Post* next;
}Post;

Post* createPost(const char* username, const char* caption);
void likePost(Post* post);

#endif
#ifndef POST_H
#define POST_H

#include "comment.h"

// Definition of Post structure
typedef struct Post{
    char username[40];
    char caption[250];
    Comment* comments;
    int likes;
    struct Post* next;
}Post;

// Post management functions (prototypes)..
Post* createPost(const char* username,const char* caption);
void likePost(Post* post);

#endif
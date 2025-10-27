#ifndef POST_H
#define POST_H

#include"comment.h"

struct post{
    char* username;
    char* caption;
    int like;
    struct comment* comments;
    struct post* next;
};

// Function declarations
struct post* create_post(char* username,char* caption);
void free_post(struct post* post);

#endif
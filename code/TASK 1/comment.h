#ifndef COMMENT_H
#define COMMENT_H

#include"reply.h"


struct comment{
    char username;
    char content;
    int like;
    struct reply* replies;
    struct comment* next;
};

//create a comment
struct comment* create_Comment(char* username,char* content);
void free_comment(struct comment* comment);
#endif
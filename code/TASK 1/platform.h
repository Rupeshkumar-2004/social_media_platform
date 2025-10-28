#ifndef PLARFORM_H
#define PLATFORM_H

#include<stdbool.h>

#include"post.h"
#include"comment.h"
#include"reply.h"

struct platform{
    struct post* posts;
    int post_number;
    struct post* last_viwed;
};

//functions declarations
struct platform* createPlatform();
bool add_post(char* username,char* caption);
bool delete_post(int n);
struct post* view_post(int n);
struct post* curr_post();
struct post* next_post();
struct post* prev_post();
void display_comments(struct comment *comment);
bool add_comment(char* username,char* content);
bool delete_comment(int n);
struct comment* view_comment();
bool add_reply(char* username,char* content,int n);
bool delete_reply(int n,int m);
void display_replies(struct reply *reply);
#endif
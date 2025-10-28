#ifndef REPLY_H
#define REPLY_H

struct reply{
    char *username;
    char *content;
    int like;
    struct reply* next;
};

//create a reply
struct reply* create_reply(char* username,char* content);
void free_reply(struct reply* r);
#endif
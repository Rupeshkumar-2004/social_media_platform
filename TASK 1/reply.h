#ifndef REPLY_H
#define REPLY_H

typedef struct Reply {
    char username[40];
    char content[250];
    struct Reply* next;
    int likes;
} Reply;

Reply* createReply(const char* username, const char* content);
void likeReply(Reply* reply);

#endif
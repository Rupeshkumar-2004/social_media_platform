#ifndef REPLY_H
#define REPLY_H

typedef struct Reply {
    char username[40];
    char text[250];
    struct Reply* next;
    int likes;
    
} Reply;
#endif
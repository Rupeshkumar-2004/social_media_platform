#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdbool.h>

#include "post.h"
#include "comment.h"
#include "reply.h"

// Definition of Platform structure
typedef struct Platform {
    Post* posts;
    int postCount;
    int commentCount;
    int replyCount;
    Post* LastViewedPost;
}Platform;

// Platform management functions (prototypes):
struct Platform* createPlatform();
bool addPost(struct Platform* platform,const char* username,const char* caption);
void displayAllPosts(const struct Platform* platform);
void displayPost(const Post* post);
bool deletePost(struct Platform* platform,const char* username,const char* caption,const int n);
bool deleteComment(struct Platform* platform,const char* username,const char* content,const int n);
bool deleteReply(struct Platform* platform,const char* username,const char* content);
Post* viewPost(const struct Platform* platform,const int n,const char* username);
Post* currPost(const struct Platform* platform);
Post* nextPost(struct Platform* platform);
Post* prevPosts(const struct Platform* platform);
bool addComment(struct Platform* platform,Post* post,const char* username,const char* content);
Comment* viewComments(const struct Platform* platform,const int n,const char* username);
bool addReply(struct Platform* platform,Comment* comment,const char* username,const char* content);
bool deleteReply(struct Platform* platform,const char* username,const char* content);

#endif
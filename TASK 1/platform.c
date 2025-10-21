#include<stdio.h>
#include<stdlib.h>
#include<string.h>  

#include "platform.h"
#include "post.h"
#include "comment.h"
#include "reply.h"


//function to create a platform..
struct Platform* createPlatform(){
    struct Platform* platform =(struct Platform*)malloc(sizeof(struct Platform));
    if(!platform){
        printf("Memory allocation failed\n");
        exit(1);
    }
    platform->posts = NULL;
    platform->postCount = 0;
    platform->commentCount = 0;
    platform->replyCount = 0;
    platform->LastViewedPost = NULL;
    return platform;
}

//function to add a post to the platform..
bool addPost(struct Platform* platform,const char* username,const char* caption){
    if(!platform) return false;
    Post* newPost =createPost(username, caption);
    if(!newPost) return false;
    if(!platform->posts) {
        platform->posts = newPost;
    }
    else{
        Post* temp = platform->posts;
        while (temp->next) temp = temp->next;
        temp->next = newPost;
    }
    platform->postCount++;
    return true;
}

//function to delete a post from the platform..
bool deletePost(struct Platform* platform,const char* username,const char* caption,const int n) {
    if(!platform||!platform->posts) return false;
    Post* temp =platform->posts;
    Post* prev =NULL;
    int count =0;
    while(temp){
        if (strcmp(temp->username,username) ==0 && strcmp(temp->caption,caption) == 0) {
            if (count ==n) {
                if(prev){
                    prev->next = temp->next;
                }else{
                    platform->posts = temp->next;
                }
                free(temp);
                platform->postCount--;
                return true;
            }
            count++;
        }
        prev =temp;
        temp =temp->next;
    }
    return false;
}
//function to view a specific post by index and username..
Post* viewPost(const struct Platform* platform,const int n, const char* username) {
    if (!platform||!platform->posts) return NULL;
    Post* temp =platform->posts;
    int count =0;
    while(temp){
        if(strcmp(temp->username,username) ==0) {
            if(count ==n){
                return temp;
            }
            count++;
        }
        temp =temp->next;
    }
    return NULL;
}

//function to get the current viewed post..
Post* currPost(const struct Platform* platform) {
    if(!platform||!platform->LastViewedPost) return NULL;
    return platform->LastViewedPost;
}

//function to get the next post..
Post* nextPost(struct Platform* platform) {
    if (!platform||!platform->LastViewedPost||!platform->LastViewedPost->next) return NULL;
    platform->LastViewedPost =platform->LastViewedPost->next;
    return platform->LastViewedPost;
}

//function to get the previous post..
Post* prevPosts(const struct Platform* platform) {
    if (!platform||!platform->LastViewedPost||platform->LastViewedPost ==platform->posts) return NULL;
    Post* temp =platform->posts;
    while (temp &&temp->next != platform->LastViewedPost) {
        temp =temp->next;
    }
    return temp;
}

//function to add a comment to a post..
bool addComment(struct Platform* platform,Post* post,const char* username,const char* content) {
    if(!platform||!post) return false;
    Comment* newComment =createComment(username,content);
    if(!newComment) return false;
    if(!post->comments){
        post->comments = newComment;
    }else{
        Comment* temp = post->comments;
        while (temp->next) temp = temp->next;
        temp->next = newComment;
    }
    platform->commentCount++;
    return true;
}

//function to delete a comment from a post..
bool deleteComment(struct Platform* platform,const char* username,const char* content,const int n) {
    if(!platform||!platform->posts) return false;
    Post* tempPost =platform->posts;
    while(tempPost) {
        Comment* tempComment =tempPost->comments;
        Comment* prevComment =NULL;
        int count =0;
        while(tempComment){
            if(strcmp(tempComment->username,username) ==0 && strcmp(tempComment->content,content) ==0) {
                if(count == n){
                    if(prevComment){
                        prevComment->next =tempComment->next;
                    }
                    else{
                        tempPost->comments = tempComment->next;
                    }
                    free(tempComment);
                    platform->commentCount--;
                    return true;
                }
                count++;
            }
            prevComment =tempComment;
            tempComment =tempComment->next;
        }
        tempPost =tempPost->next;
    }
    return false;
}

//function to view comments of a specific post by index and username..
Comment* viewComments(const struct Platform* platform,const int n,const char* username) {
    if(!platform||!platform->posts) return NULL;
    Post* tempPost = platform->posts;
    while(tempPost){
        if(strcmp(tempPost->username, username) ==0){
            Comment* tempComment =tempPost->comments;
            int count =0;
            while(tempComment){
                if(count == n){
                    return tempComment;
                }
                count++;
                tempComment =tempComment->next;
            }
        }
        tempPost =tempPost->next;
    }
    return NULL;
}

//function to add a reply to a comment..
bool addReply(struct Platform* platform,Comment* comment,const char* username,const char* content) {
    if (!platform||!comment) return false;
    Reply* newReply =createReply(username,content);
    if(!newReply) return false;
    if(!comment->replies){
        comment->replies =newReply;
    }else{
        Reply* temp =comment->replies;
        while (temp->next) temp =temp->next;
        temp->next =newReply;
    }
    platform->replyCount++;
    return true;
}

//function to delete a reply from a comment..
bool deleteReply(struct Platform* platform,const char* username,const char* content) {
    if(!platform||!platform->posts) return false;
    Post* tempPost =platform->posts;
    while(tempPost){
        Comment* tempComment =tempPost->comments;
        while(tempComment){
            Reply* tempReply =tempComment->replies;
            Reply* prevReply =NULL;
            while(tempReply){
                if(strcmp(tempReply->username,username) == 0 && strcmp(tempReply->content,content) == 0) {
                    if(prevReply){
                        prevReply->next =tempReply->next;
                    }
                    else{
                        tempComment->replies =tempReply->next;
                    }
                    free(tempReply);
                    platform->replyCount--;
                    return true;
                }
                prevReply =tempReply;
                tempReply =tempReply->next;
            }
            tempComment =tempComment->next;
        }
        tempPost =tempPost->next;
    }
    return false;
}

//function to display a specific post..
void displayPost(const Post* post) {
    if(!post) return;
    printf("Post by %s: %s\n", post->username,post->caption);
    printf("Likes: %d\n",post->likes);
    Comment* tempComment = post->comments;
    while(tempComment){
        printf("  Comment by %s: %s (Likes: %d)\n", tempComment->username, tempComment->content, tempComment->likes);
        Reply* tempReply = tempComment->replies;
        while(tempReply){
            printf("    Reply by %s: %s (Likes: %d)\n", tempReply->username, tempReply->content, tempReply->likes);
            tempReply =tempReply->next;
        }
        tempComment =tempComment->next;
    }
}

//function to display all posts in the platform..
void displayAllPosts(const struct Platform* platform) {
    if(!platform||!platform->posts){
        printf("No posts available.\n");
        return;
    }
    Post* temp = platform->posts;
    while(temp){
        displayPost(temp);
        temp =temp->next;
    }
}

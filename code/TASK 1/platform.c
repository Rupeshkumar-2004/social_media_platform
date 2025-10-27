#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"post.h"
#include"platform.h"
#include"post.h"
#include"comment.h"
#include"reply.h"


struct platform* global_platform=NULL;

//to create a platform
struct platform* createPlatform(){
    if(global_platform!=NULL){
        return global_platform;
    }
    global_platform=(struct platform*)malloc(sizeof(struct platform));
    global_platform->posts=NULL;
    global_platform->post_number=0;
    global_platform->last_viwed=NULL;
    return global_platform;
}

//to add a post
bool add_post(char* username,char* caption){
    struct post* new_post=create_post(username,caption);
    if(new_post==NULL){
        return false;
    }
    new_post->next=global_platform->posts;
    global_platform->posts=new_post;
    global_platform->post_number++;

    if(global_platform->last_viwed==NULL){
        global_platform->last_viwed=new_post;
    }

    return true;
}

struct post* view_post(int n){
    if(n<=0||global_platform->posts==NULL){
        return NULL;
    }

    struct post* curr_post=global_platform->posts;
    for(int curr=0;curr<n-1 && curr_post!=NULL;curr++){
        curr_post=curr_post->next;
    }

    if(curr_post==NULL){
        global_platform->last_viwed =global_platform->posts;
        return global_platform->posts;
    }

    global_platform->last_viwed=curr_post;
    return curr_post;
}

//last viewed post..
struct post* curr_post(){
    if(global_platform->last_viwed!=NULL){
        return global_platform->last_viwed;
    }

    return global_platform->posts;
}

//to view post just before the last viewed post
struct post* next_post(){
    struct post* curr=curr_post();
    if(curr==NULL){
        return NULL;
    }

    if(curr->next == NULL){
        global_platform->last_viwed =curr;
        return curr;
    }
    else{
        global_platform->last_viwed =curr->next;
        return curr->next;
    }
}

//to view the post just after last viwed
struct post* prev_post(){
    struct post* curr=curr_post();
    if(curr==NULL){
        return NULL;
    }
    if(curr==global_platform->posts){
        return curr;
    }

    struct post* prev=global_platform->posts;
    while(prev!=NULL && prev->next!=curr){
        prev=prev->next;
    }

    if(prev==NULL) {
        return NULL;
    }

    global_platform->last_viwed=prev;
    return prev;
}

//to delete a post
bool delete_post(int n){
    if(n<=0||global_platform->posts==NULL){
        return false;
    }

    struct post* prev_post=NULL;
    struct post* curr_post=global_platform->posts;

    for(int curr =0;curr<n-1;curr++){
        if(curr_post == NULL){
            return false;
        }
        prev_post =curr_post;
        curr_post = curr_post->next;
    }

    if(prev_post ==NULL){
        global_platform->posts=curr_post->next;
    }
    else{
        prev_post->next=curr_post->next;
    }

    free_post(curr_post);
    return true;
}
//adding comment to lastViwed comment
bool add_comment(char* username,char* content){
    struct post* post_to_add_comment = curr_post();
    if(post_to_add_comment ==NULL){
         return false;
    }

    struct comment* new_comment =create_Comment(username,content);
    if(new_comment == NULL){
        return false;
    }

    new_comment->next= post_to_add_comment->comments;
    post_to_add_comment->comments =new_comment;
    return true;
}

void display_replies(struct reply* reply);

void display_comments(struct comment *comment){
    if(!comment) return;
    if(comment->username&&comment->content){
        printf("%s %s\n",comment->username,comment->content);
    }
    if(comment->replies)
        display_replies(comment->replies);
    display_comments(comment->next);
}

//deleting a comment...
bool delete_comment(int n){
    if(n<=0) return false;
    struct post* curr_Post =curr_post();

    if(curr_Post==NULL || curr_Post->comments ==NULL){
        return false;
    }

    struct comment* prev_comment =NULL;
    struct comment* curr_comment =curr_Post->comments;

    for(int curr=0;curr<n-1;curr++){
        if(curr_comment ==NULL){
            return false;
        }
        prev_comment =curr_comment;
        curr_comment =curr_comment->next;
    }

    if(prev_comment==NULL){
        curr_Post->comments = curr_comment->next;
    }else{
        prev_comment->next =curr_comment->next;
    }

    free_comment(curr_comment);
    return true;
}

//return all the comments in lastViwed post
struct comment* view_comment(){
    struct post* lastViwed_post=curr_post();
    if(lastViwed_post ==NULL){
        return NULL;
    }
    return lastViwed_post->comments;
}

//add reply to nth recent comment..
bool add_reply(char* username, char* content,int n){
    if(n<=0){
        return false;
    }
    struct post* last_viewed_post =curr_post();
    if(last_viewed_post ==NULL || last_viewed_post->comments ==NULL){
        return false;
    }

    struct comment* comments =last_viewed_post->comments;
    for(int curr =0;curr<n-1;curr++){
        if(comments == NULL){
            return false;
        }
        comments =comments->next;
    }

    struct reply* new_reply=create_reply(username,content);
    if(new_reply ==NULL){
        return false;
    }
    new_reply->next=comments->replies;
    comments->replies=new_reply;

    return true;
}

//delete mth recent reply from nth comment
bool delete_reply(int n,int m){
    if(n<=0 || m<=0){
        return false;
    }
    struct post* last_viewed_post =curr_post();
    if(last_viewed_post ==NULL || last_viewed_post->comments ==NULL){
        return false;
    }

    struct comment* comments =last_viewed_post->comments;
    for(int curr =0;curr<n-1;curr++){
        if(comments == NULL){
            return false;
        }
        comments =comments->next;
    }

    struct reply* prev_reply =NULL;
    struct reply* curr_reply =comments->replies;

    for(int curr=0;curr<m-1;curr++){
        if(curr_reply ==NULL){
            return false;
        }
        prev_reply =curr_reply;
        curr_reply =curr_reply->next;
    }

    if(prev_reply ==NULL){
        comments->replies=curr_reply->next;
    }
    else{
        prev_reply->next=curr_reply->next;
    }

    free_reply(curr_reply);
    return true;
}


void display_replies(struct reply *reply) {
    if(!reply) return;
    if(reply->username&&reply->content)
        printf("%s %s\n",reply->username,reply->content);
    display_replies(reply->next);
}

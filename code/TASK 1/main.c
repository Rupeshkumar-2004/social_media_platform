#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "platform.h"


static void showMenu(void) {
    puts("Available Commands:");
    puts("create_platform");
    puts("add_post <user> <caption>");
    puts("delete_post <n>");
    puts("view_post <n>");
    puts("current_post");
    puts("next_post");
    puts("previous_post");
    puts("add_comment <user> <content>");
    puts("view_comments");
    puts("delete_comment <n>");
    puts("add_reply <user> <reply> <n>");
    puts("delete_reply <n> <m>");
    puts("display");
    puts("exit(quit)");
}

static void cmd_create(void){
    createPlatform();
    printf("Platform initialized.\n");
}

static void cmd_addPost(const char *args){
    char user[128],caption[256];
    if(sscanf(args,"%s %[^\n]", user, caption)!=2){
        printf("give input like.. add_post <user> <caption>\n");
        return;
    }
    if(!add_post(user, caption)){
        printf("Failed to create post.\n");
    }
}

static void cmd_deletePost(const char *args){
    int n;
    if(sscanf(args,"%d",&n)!=1){
        printf("give input like.. delete_post <n>\n");
        return;
    }
    if(!delete_post(n)){
        printf("No such post: %d\n",n);
    }
}

static void cmd_viewPost(const char *args){
    int n;
    if(sscanf(args,"%d",&n)!=1){
        printf("give input like..view_post <n>\n");
        return;
    }
    struct post *p=view_post(n);
    if(p){
        printf("%s %s\n",p->username,p->caption);
    }
    else{
        printf("Post %d not found.\n",n);
    }
}

static void cmd_curr(){
    struct post *p=curr_post();
    if(p){
        printf("%s %s\n",p->username,p->caption);
    }
    else{
        printf("No post currently selected.\n");
    }
}

static void cmd_next(){
    struct post *p = next_post();
    if(p){
        printf("%s %s\n",p->username,p->caption);
    }
    else{
        printf("Next post unavailable.\n");
    }
}

static void cmd_prev(){
    struct post *p =prev_post();
    if(p){
        printf("%s %s\n",p->username,p->caption);
    }
    else{
        printf("Previous post unavailable.\n");
    }
}

static void cmd_addComment(const char *args) {
    char user[128],text[256];
    if (sscanf(args,"%s %[^\n]",user,text)!=2){
        printf("give command like this..add_comment <user> <content>\n");
        return;
    }
    if(!add_comment(user, text))
        printf("No active post to comment on.\n");
}

static void cmd_deleteComment(const char *args) {
    int n;
    if(sscanf(args,"%d",&n)!=1){
        printf("give command like this..delete_comment <n>\n");
        return;
    }
    if(!delete_comment(n))
        printf("Comment %d not found.\n", n);
}

static void cmd_viewComments(void) {
    struct comment *c=view_comment();
    display_comments(c);
}

static void cmd_addReply(const char *args) {
    char user[128],content[256];
    int comment_number;

    // Extract last integer argument
    char *pos =strrchr(args,' ');
    if(!pos||sscanf(pos+1,"%d",&comment_number)!=1){
        printf("give command like this..add_reply <user> <reply> <comment_number>\n");
        return;
    }
    *pos = '\0';
    if(sscanf(args,"%s %[^\n]",user,content)!=2){
        printf("give command like this..add_reply <user> <reply> <comment_number>\n");
        return;
    }
    if(!add_reply(user,content,comment_number)){
        printf("Failed to reply to comment %d.\n",comment_number);
    }
}

static void cmd_deleteReply(const char *args) {
    int n, m;
    if(sscanf(args,"%d %d",&n,&m)!=2){
        printf("give command lik this..delete_reply <comment_no> <reply_no>\n");
        return;
    }
    if(!delete_reply(n,m))
        printf("Unable to delete reply %d\n",m);
}

typedef void (*command_handler)(const char *);

typedef struct{
    const char *name;
    command_handler handler;
}command_entry;

static const command_entry commands[]={
    {"create_platform",(command_handler)cmd_create},
    {"add_post",cmd_addPost},
    {"delete_post",cmd_deletePost},
    {"view_post",cmd_viewPost},
    {"current_post",(command_handler)cmd_curr},
    {"next_post",(command_handler)cmd_next},
    {"previous_post",(command_handler)cmd_prev},
    {"add_comment",cmd_addComment},
    {"delete_comment",cmd_deleteComment},
    {"view_comments",(command_handler)cmd_viewComments},
    {"add_reply",cmd_addReply},
    {"delete_reply",cmd_deleteReply},
    {"display",(command_handler)showMenu},
    {NULL,NULL}
};

int main(void) {
    char input[512];
    showMenu();
    createPlatform();

    for(;;){
        if(!fgets(input,sizeof(input),stdin)){
            break;
        }
        input[strcspn(input,"\n")]='\0';
        char *p=input;
        while(isspace((unsigned char)*p)) p++;
        if (!*p){
            continue;
        }
        if (!strcmp(p,"exit")||!strcmp(p,"EXIT"))
            break;

        char cmd[64];
        sscanf(p,"%s",cmd);
        char *args=p+strlen(cmd);
        while(*args&&isspace((unsigned char)*args)){
            args++;
        }

        int found = 0;
        for (const command_entry *ce=commands;ce->name;++ce){
            if(!strcmp(cmd,ce->name)){
                ce->handler(args);
                found=1;
                break;
            }
        }
        if(!found)
            printf("Unknown command:'%s'\n",cmd);
    }

    puts("Session ended. Goodbye!");
    return 0;
}

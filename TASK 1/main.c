#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "platform.h"
#include "post.h"
#include "comment.h"
#include "reply.h"
#include "users.h"

int main(){
    printf("Welcome to AquaRegia --The Social Media Platform!\n");
    struct Platform *platform = createPlatform();
    if(!platform){
        printf("Failed to initialise platform.\n");
        return 1;
    }else{
        printf("Platform initialised successfully.\n");
    }

    printf("=============================================\n");
    struct User* users = NULL;
    char current_user[40] = "";

    // Top-level loop: register/login/exit
    while(1){
        printf("\nTop Menu:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. List Users\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        int topc = 0;
        scanf("%d", &topc);
        if(topc == 4) break;
        if(topc == 1){
            char newname[40];
            printf("Enter new username: ");
            scanf("%39s", newname);
            if(addUser(&users, newname)) printf("Registered %s\n", newname);
            else printf("Username already exists.\n");
            continue;
        }
        if(topc == 3){ displayUsers(users); continue; }
        if(topc != 2) { printf("Invalid choice.\n"); continue; }

        // Login
        printf("Enter username to login: ");
        scanf("%39s", current_user);
        if(!findUser(users, current_user)){
            printf("User not found. Please register first.\n");
            continue;
        }

        printf("Hello, %s!\n", current_user);

        // User session loop
        while(1){
    printf("1. Add Post\n");
    printf("2. Display My Posts\n");
    printf("3. Display All Posts\n");
    printf("4. Delete My Post\n");
    printf("5. Search Posts & Reply\n");
    printf("6. View Posts (interactive)\n");
    printf("7. Delete Comment\n");
    printf("8. Delete Reply\n");
    printf("9. Logout\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
            if(choice == 9) { printf("Logging out %s...\n", current_user); break; }
        switch(choice){
            case 1: {
                char caption[256];
                printf("Enter caption: ");
                getchar(); // consume newline
                fgets(caption, sizeof(caption), stdin);
                caption[strcspn(caption, "\n")] = 0; // remove newline
                if(addPost(platform, current_user, caption))
                    printf("Post added successfully.\n");
                else
                    printf("Failed to add post.\n");
                break;
            }
            case 2: {
                // Display only current user's posts
                if(!platform){
                    printf("Please create a platform first.\n");
                    break;
                }
                Post* temp = platform->posts;
                int found = 0;
                while(temp){
                    if(strcmp(temp->username, current_user) == 0){
                        displayPost(temp);
                        found = 1;
                    }
                    temp = temp->next;
                }
                if(!found) printf("You have no posts.\n");
                break;
            }
            case 3: {
                // Display All Posts
                if(!platform){
                    printf("Please create a platform first.\n");
                    break;
                }
                displayAllPosts(platform);
                break;
            }
            case 4: {
                // Restrict deletion to posts owned by the logged-in user
                if(!platform){
                    printf("Please create a platform first.\n");
                    break;
                }
                char caption[256];
                int n;
                printf("Enter caption of your post to delete: ");
                getchar(); // consume newline
                fgets(caption, sizeof(caption), stdin);
                caption[strcspn(caption, "\n")] = 0;
                printf("Enter occurrence number (0 for first occurrence): ");
                scanf("%d", &n);
                if(deletePost(platform, current_user, caption, n)) 
                    printf("Post deleted successfully.\n");
                else 
                    printf("Failed to delete post (not found or not owned by you).\n");
                break;
            }
            case 5: {
                // Search posts by username and allow replying to a comment on a selected post
                char searchUser[40];
                printf("Enter username to search posts: ");
                scanf("%39s", searchUser);
                Post* temp = platform->posts;
                int idx = 0;
                int matches = 0;
                while(temp){
                    if(strcmp(temp->username, searchUser) == 0){
                        printf("[%d] %s\n", idx, temp->caption);
                        matches++;
                    }
                    temp = temp->next;
                    idx++;
                }
                if(matches == 0){
                    printf("No posts found for user %s.\n", searchUser);
                    break;
                }
                int pick;
                printf("Enter index of post to open (use index shown): ");
                scanf("%d", &pick);
                // find picked post by scanning again
                temp = platform->posts;
                idx = 0;
                Post* chosen = NULL;
                while(temp){
                    if(idx == pick && strcmp(temp->username, searchUser) == 0){
                        chosen = temp; break;
                    }
                    temp = temp->next; idx++;
                }
                if(!chosen){
                    printf("Invalid selection.\n");
                    break;
                }
                // list comments on chosen post
                Comment* c = chosen->comments;
                if(!c){
                    printf("No comments on this post. Would you like to add one? (y/n): ");
                    char yc; getchar(); scanf("%c", &yc);
                    if(yc == 'y'){
                        char content[250];
                        printf("Enter your comment: ");
                        getchar();
                        fgets(content, sizeof(content), stdin);
                        content[strcspn(content, "\n")] = 0;
                        if(addComment(platform, chosen, current_user, content))
                            printf("Comment added.\n");
                        else printf("Failed to add comment.\n");
                    }
                    break;
                }
                int cidx = 0;
                while(c){
                    printf("[%d] %s: %s\n", cidx, c->username, c->content);
                    c = c->next; cidx++;
                }
                int pickc;
                printf("Enter comment index to reply to: ");
                scanf("%d", &pickc);
                c = chosen->comments; cidx = 0;
                while(c && cidx < pickc){ c = c->next; cidx++; }
                if(!c){ printf("Invalid comment selection.\n"); break; }
                getchar();
                char replyContent[250];
                printf("Enter your reply: ");
                fgets(replyContent, sizeof(replyContent), stdin);
                replyContent[strcspn(replyContent, "\n")] = 0;
                if(addReply(platform, c, current_user, replyContent))
                    printf("Reply added.\n");
                else printf("Failed to add reply.\n");
                break;
            }
            case 6: {
                // Interactive post viewer: pick a post and perform actions (like/comment/reply/like comment/like reply)
                if(!platform || !platform->posts){ printf("No posts available.\n"); break; }
                Post* temp = platform->posts;
                int idx = 0;
                while(temp){
                    printf("[%d] %s (by %s)\n", idx, temp->caption, temp->username);
                    temp = temp->next; idx++;
                }
                int pick;
                printf("Enter post index to open (-1 to cancel): ");
                scanf("%d", &pick);
                if(pick < 0) break;
                temp = platform->posts; idx = 0;
                Post* chosen = NULL;
                while(temp){ if(idx == pick){ chosen = temp; break; } temp = temp->next; idx++; }
                if(!chosen){ printf("Invalid post selection.\n"); break; }
                // Post actions loop
                while(1){
                    displayPost(chosen);
                    printf("Actions: 1) Like Post 2) Add Comment 3) Like Comment 4) Add Reply to Comment 5) Like Reply 6) Back\n");
                    printf("Choose action: ");
                    int act; scanf("%d", &act);
                    if(act == 6) break;
                    if(act == 1){ likePost(chosen); printf("Post liked. Likes: %d\n", chosen->likes); }
                    else if(act == 2){
                        char content[250]; printf("Enter comment: "); getchar(); fgets(content, sizeof(content), stdin); content[strcspn(content, "\n")] = 0;
                        if(addComment(platform, chosen, current_user, content)) printf("Comment added.\n"); else printf("Failed to add comment.\n");
                    }
                    else if(act == 3){
                        // list comments
                        Comment* c = chosen->comments; int ci = 0;
                        if(!c){ printf("No comments to like.\n"); continue; }
                        while(c){ printf("[%d] %s: %s (Likes: %d)\n", ci, c->username, c->content, c->likes); c = c->next; ci++; }
                        int pickc; printf("Enter comment index to like: "); scanf("%d", &pickc);
                        c = chosen->comments; ci = 0; while(c && ci < pickc){ c = c->next; ci++; }
                        if(!c){ printf("Invalid comment selection.\n"); } else { likeComment(c); printf("Comment liked. Likes: %d\n", c->likes); }
                    }
                    else if(act == 4){
                        Comment* c = chosen->comments; int ci = 0; if(!c){ printf("No comments to reply to.\n"); continue; }
                        while(c){ printf("[%d] %s: %s\n", ci, c->username, c->content); c = c->next; ci++; }
                        int pickc; printf("Enter comment index to reply to: "); scanf("%d", &pickc);
                        c = chosen->comments; ci = 0; while(c && ci < pickc){ c = c->next; ci++; }
                        if(!c){ printf("Invalid comment selection.\n"); } else { char replyContent[250]; getchar(); printf("Enter reply: "); fgets(replyContent, sizeof(replyContent), stdin); replyContent[strcspn(replyContent, "\n")] = 0; if(addReply(platform, c, current_user, replyContent)) printf("Reply added.\n"); else printf("Failed to add reply.\n"); }
                    }
                    else if(act == 5){
                        Comment* c = chosen->comments; int ci = 0; if(!c){ printf("No comments/replies to like.\n"); continue; }
                        while(c){ printf("Comment [%d] %s: %s\n", ci, c->username, c->content); Reply* r = c->replies; int ri = 0; while(r){ printf("  Reply [%d] %s: %s (Likes: %d)\n", ri, r->username, r->content, r->likes); r = r->next; ri++; } c = c->next; ci++; }
                        int pickc; printf("Enter comment index which contains the reply: "); scanf("%d", &pickc);
                        Comment* cc = chosen->comments; int ci2 = 0; while(cc && ci2 < pickc){ cc = cc->next; ci2++; }
                        if(!cc){ printf("Invalid comment selection.\n"); continue; }
                        Reply* rr = cc->replies; if(!rr){ printf("No replies to like under that comment.\n"); continue; }
                        int pickr; printf("Enter reply index to like: "); scanf("%d", &pickr);
                        int ri2 = 0; while(rr && ri2 < pickr){ rr = rr->next; ri2++; }
                        if(!rr){ printf("Invalid reply selection.\n"); } else { likeReply(rr); printf("Reply liked. Likes: %d\n", rr->likes); }
                    }
                    else printf("Invalid action.\n");
                }
                break;
            }
            case 7: {
                char commentOwner[40], content[250];
                int n;
                printf("Enter username of the comment owner: ");
                scanf("%39s", commentOwner);
                printf("Enter content of the comment to delete: ");
                getchar();
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = 0;
                printf("Enter occurrence number (0 for first occurrence): ");
                scanf("%d", &n);
                if(deleteComment(platform, commentOwner, content, n))
                    printf("Comment deleted.\n");
                else
                    printf("Failed to delete comment.\n");
                break;
            }
            case 8: {
                char commentOwner[40], postOwner[40];
                char commentContent[250];
                char replyContent[250];
                printf("Enter post owner's username: ");
                scanf("%39s", postOwner);
                printf("Enter comment owner's username: ");
                scanf("%39s", commentOwner);
                printf("Enter comment content to reply to: ");
                getchar();
                fgets(commentContent, sizeof(commentContent), stdin);
                commentContent[strcspn(commentContent, "\n")] = 0;
                printf("Enter your reply: ");
                fgets(replyContent, sizeof(replyContent), stdin);
                replyContent[strcspn(replyContent, "\n")] = 0;
                // find the comment
                Comment* found = NULL;
                Post* tp = platform->posts;
                while(tp){
                    if(strcmp(tp->username, postOwner) == 0){
                        Comment* tc = tp->comments;
                        while(tc){
                            if(strcmp(tc->username, commentOwner) == 0 && strcmp(tc->content, commentContent) == 0){
                                found = tc; break;
                            }
                            tc = tc->next;
                        }
                    }
                    if(found) break;
                    tp = tp->next;
                }
                if(found){
                    if(addReply(platform, found, current_user, replyContent))
                        printf("Reply added.\n");
                    else
                        printf("Failed to add reply.\n");
                } else printf("Comment not found.\n");
                break;
            }
            case 10: {
                char replyOwner[40], replyContent[250];
                printf("Enter reply owner's username: ");
                scanf("%39s", replyOwner);
                printf("Enter content of the reply to delete: ");
                getchar();
                fgets(replyContent, sizeof(replyContent), stdin);
                replyContent[strcspn(replyContent, "\n")] = 0;
                if(deleteReply(platform, replyOwner, replyContent))
                    printf("Reply deleted.\n");
                else
                    printf("Failed to delete reply.\n");
                break;
            }
        } // end switch
        } // end user session loop
    } // end top-level loop

    printf("Exiting application.\n");
    return 0;
}
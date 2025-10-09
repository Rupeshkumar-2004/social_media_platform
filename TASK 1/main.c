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
    printf("Do you have an account? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if(choice == 'n'){
        printf("Please create an account first.\n");
        int flag = 0;
        printf("Enter your desired username: ");
        char username[50];
        scanf("%s", username);
        struct User* users = NULL;
        while(flag == 0){
            if(addUser(&users, username)){
                printf("Account created successfully. You can now log in.\n");
                flag = 1;
            } else {
                printf("Username already exists. Please try a different one: ");
                scanf("%s", username);
            }
        }
    }

    printf("Enter your username to get started(): ");
    char username[50];
    scanf("%s", username);

    printf("Hello, %s!\n", username);
    printf("What would you like to do today?\n");

    while(1){
        printf("\nMenu:\n");
        printf("1. Add Post\n");
        printf("2. Display All Posts\n");
        printf("3. Delete Post\n");
        printf("4. Add Comment\n");
        printf("5. View Comments\n");
        printf("6. Delete Comment\n");
        printf("7. Add Reply\n");
        printf("8. Delete Reply\n");
        printf("9. Logout\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice == 9) break;
        switch(choice){
            case 1: {
                char username[50], caption[256];
                printf("Enter caption: ");
                getchar(); // to consume the newline character
                fgets(caption, sizeof(caption), stdin);
                caption[strcspn(caption, "\n")] = 0; // remove newline character
                if(addPost(platform, username, caption)) 
                    printf("Post added successfully.\n");
                else 
                    printf("Failed to add post.\n");
                break;
            }
            case 2: {
                if(!platform){
                    printf("Please create a platform first.\n");
                    break;
                }
                displayAllPosts(platform);
                break;
            }
            case 3: {
                if(!platform){
                    printf("Please create a platform first.\n");
                    break;
                }
                char username[50], caption[256];
                int n;
                printf("Enter username of the post owner: ");
                scanf("%s", username);
                printf("Enter caption of the post to delete: ");
                getchar(); // to consume the newline character
                fgets(caption, sizeof(caption), stdin);
                caption[strcspn(caption, "\n")] = 0; // remove newline character
                printf("Enter occurrence number (0 for first occurrence): ");
                scanf("%d", &n);
                if(deletePost(platform, username, caption, n)) 
                    printf("Post deleted successfully.\n");
                else 
                    printf("Failed to delete post.\n");
                break;
            }
            case 4: {
                
            }
        }
    }
}
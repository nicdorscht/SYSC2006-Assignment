/*****************
    Student Name 	= Nicholas Dorscht
    Student Number	= 101298132
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

user_t *add_user(user_t *users, const char *username, const char *password){
    if(users == NULL){
        users = malloc(sizeof(user_t));
        assert(users != NULL);

        users->next = NULL;
        strcpy(users->username, username);
        strcpy(users->password, password);
        users->friends = NULL;
        users->posts = NULL;

        return users;

    } else if (strcmp(username, users->username) < 0) {
        user_t *temp = malloc(sizeof(user_t));
        assert(temp != NULL);

        temp->next = users;
        temp->friends = NULL;
        temp->posts = NULL;
        strcpy(temp->username, username);
        strcpy(temp->password, password);

        return temp;
    } else {
        user_t *ptr = users;
        user_t *prev = NULL;

        for( ; ptr->next != NULL && strcmp(username, ptr->username) > 0; ) { 
            printf("Comp: %d", strcmp(username, ptr->username));
            prev = ptr;
            ptr = ptr->next;
        }

        if(ptr->next == NULL){
            user_t *temp = malloc(sizeof(user_t));
            assert(temp != NULL);

            temp->next = NULL;
            temp->friends = NULL;
            temp->posts = NULL;
            strcpy(temp->username, username);
            strcpy(temp->password, password);
            ptr->next = temp;
        } else {
            user_t *temp = malloc(sizeof(user_t));
            assert(temp != NULL);

            temp->next = ptr;
            prev->next = temp;

            temp->friends = NULL;
            temp->posts = NULL;

            strcpy(temp->password, password);
            strcpy(temp->username, username);
        }

        return users;
    }

    return users;
}

user_t *find_user(user_t *users, const char *username){
    user_t *ptr = users;

    for( ; ptr != NULL; ptr = ptr->next){
        if(strcmp(ptr->username, username) == 0){
            return ptr;
        }
    }

    return NULL;
}

void add_friend(user_t *user, const char *friend){

}

void add_post(user_t *user, const char *text){
    post_t *new_post = malloc(sizeof(post_t));
    assert(new_post != NULL);

    new_post->next = NULL;
    strcpy(new_post->content, text);

    if(user->posts == NULL){
        user->posts = new_post;
    } else {
        post_t *ptr = user->posts;
        for( ; ptr->next != NULL; ptr = ptr->next);

        ptr->next = new_post;
    }
}

_Bool delete_post(user_t *user){
    if(user->posts == NULL) {
        return false;
    }

    post_t *ptr = user->posts;
    for( ; ptr->next->next != NULL; ptr = ptr->next);

    free(ptr->next);
    ptr->next = NULL;

    return true;
}

void display_all_user_posts(user_t *user){
    printf(
        "----------------------------------------------\n"
        "\t\tPosts from %s\n"
        "----------------------------------------------\n"
        , user->username
    );

        post_t *ptr = user->posts;

        for( ; ptr != NULL; ptr = ptr->next){
            printf("\n%s\n", ptr->content);
        }

        printf("\n");
}

void print_menu(){
    printf(
            "\n*******************************************\n"
            "\t\tMAIN MENU\n"
            "*******************************************\n"
            "1. Register a new user\n"
            "2. Manage a user's profile (change password)\n"
            "3. Manage a user's posts (add/remove)\n"
            "4. Manage a user's friends (add/remove)\n"
            "5. Display a user's posts\n"
            "6. Exit\n\n"
            "Enter your choice: "
    );
}

int get_int(int l_limit, int h_limit){
   int num = 0;

   scanf("%d", &num);

   while(num < l_limit || num > h_limit){
      printf("Number must be between %d and %d, enter a new number: ", l_limit, h_limit);

      scanf("%d", &num);
   }

   return num;
}

void change_password(user_t *users){

    char username[30];
    char password[15];

    printf("Enter a username to update their password: ");
    scanf(" %s", username);
    user_t *user_to_change = find_user(users, username);

    if(user_to_change == NULL){
        printf(
            "\n----------------------------------------------\n"
            "\t\tUser not found"
            "\n----------------------------------------------\n"
            );
            return;
    }

    printf("Enter password: ");
    scanf(" %s", password);

    if(strcmp(password, user_to_change->password) != 0){
        printf(
        "\n----------------------------------------------\n"
        "\t\tIncorrect Password"
        "\n----------------------------------------------\n"
        );
        return;
    }

    char new_password[15];
    printf("Enter new password: ");
    scanf(" %s", new_password);

    strcpy(user_to_change->password, new_password);
}

void post_menu(user_t *users){
    char username[30];

    printf("Enter a username to see their posts: ");
    scanf( "%s", username);

    user_t *ptr = find_user(users, username);

    if(ptr == NULL){
        printf(
        "\n----------------------------------------------\n"
        "\t\tUser not found"
        "\n----------------------------------------------\n"
        );
        return;
    }

    printf(
        "\n----------------------------------------------\n"
        "\t\tManaging %s's posts"
        "\n----------------------------------------------\n"
        , ptr->username);

    if(ptr->posts == NULL){
        printf("Note: No posts available for %s\n", ptr->username);
    } 

    while(true){
        printf(
        "1. Add a new post\n"
        "2. Remove a post\n"
        "3. Return to main menu\n"
        "Enter your choice: "
        );

        int post_choice = get_int(1, 3);

        switch(post_choice){
            case 1:
                char content[250];
                printf("Enter your post's content: ");

                scanf(" %[^\n]s", content);

                add_post(ptr, content);
                display_all_user_posts(ptr);
            break;

            case 2:
                if(delete_post(ptr)){
                    display_all_user_posts(ptr);
                } else {
                    printf("User %s has no posts to delete\n", ptr->username);
                }
            break;

            case 3:
                return;
            break;

            default:
                return;
        }
    }
}
/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
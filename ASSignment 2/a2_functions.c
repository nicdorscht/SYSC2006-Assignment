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
#include <ctype.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

user_t *add_user(user_t *users, const char *username, const char *password)
{
    user_t *new_user = malloc(sizeof(user_t));
    assert(new_user != NULL);

    new_user->friends = NULL;
    new_user->next = NULL;
    new_user->posts = NULL;
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);

    if (users == NULL)
    {
        return new_user;
    }

    user_t *ptr = users;
    user_t *prev = NULL;

    if (strcmp(ptr->username, username) > 0)
    {
        new_user->next = users;
        return new_user;
    } 

    for (; ptr != NULL; prev = ptr, ptr = ptr->next)
    {
        if (strcmp(ptr->username, username) > 0)
        {
            new_user->next = ptr;
            prev->next = new_user;
            return users;
        }
    }

    prev->next = new_user;
    return users;
}

user_t *find_user(user_t *users, const char *username)
{
    user_t *ptr = users;

    for (; ptr != NULL; ptr = ptr->next)
    {
        if (strcmp(ptr->username, username) == 0)
        {
            return ptr;
        }
    }

    return NULL;
}

friend_t *create_friend(const char *username)
{
    friend_t *new_friend = malloc(sizeof(friend_t));
    assert(new_friend != NULL);

    new_friend->next = NULL;
    new_friend->posts = NULL;
    strcpy(new_friend->username, username);

    return new_friend;
}

void add_friend(user_t *user, const char *friend)
{

    friend_t *new_friend = create_friend(friend); 

    if (user->friends == NULL)
    {
        user->friends = new_friend;
        return;
    }

    friend_t *ptr = user->friends;
    friend_t *prev = NULL;

    if (strcmp(ptr->username, friend) > 0)
    {
        new_friend->next = ptr;
        user->friends = new_friend;
        return;
    }

    for (; ptr != NULL; prev = ptr, ptr = ptr->next)
    {
        if (strcmp(ptr->username, friend) > 0)
        {
            new_friend->next = ptr;
            prev->next = new_friend;
            return;
        }
    }

    prev->next = new_friend;
}

_Bool delete_friend(user_t *user, char *friend_name)
{
    if (user->friends == NULL)
    {
        printf("No friends to delete!\n");
        return false;
    }

    friend_t *ptr = user->friends;
    friend_t *prev = NULL;

    if (strcmp(ptr->username, friend_name) == 0)
    {
        user->friends = ptr->next;

        free(ptr);
        ptr = NULL;

        return true;
    }

    for (; ptr != NULL; prev = ptr, ptr = ptr->next)
    {
        if (strcmp(ptr->username, friend_name) == 0)
        {
            prev->next = ptr->next;
            free(ptr);
            ptr = NULL;

            return true;
        }
    }
    return false;
}

post_t *create_post(const char *text)
{
    post_t *new_post = malloc(sizeof(post_t));
    assert(new_post != NULL);

    new_post->next = NULL;
    strcpy(new_post->content, text);

    return new_post;
}

void add_post(user_t *user, const char *text)
{
    post_t *new_post = create_post(text);

    if (user->posts == NULL)
    {
        user->posts = new_post;
    }
    else
    {
        post_t *ptr = user->posts;
        for (; ptr->next != NULL; ptr = ptr->next)
            ;

        ptr->next = new_post;
    }
}

_Bool delete_post(user_t *user)
{
    if (user->posts == NULL)
    {
        return false;
    }

    if (user->posts->next == NULL)
    {
        free(user->posts);
        user->posts = NULL;
        return true;
    }

    post_t *ptr = user->posts;
    for (; ptr->next->next != NULL; ptr = ptr->next)
        ;

    free(ptr->next);
    ptr->next = NULL;

    return true;
}

void display_user_friends(user_t *user)
{
    printf("List of %s's friends:\n", user->username);

    if (user->friends == NULL)
    {
        printf("No friends\n");
        return;
    }

    friend_t *ptr = user->friends;

    for (int i = 1; ptr != NULL; ptr = ptr->next, i++)
    {
        printf("%d. %s\n", i, ptr->username);
    }
}

void display_all_user_posts(user_t *user)
{

    if (user->posts == NULL)
    {
        return;
    }

    printf(
        "----------------------------------------------\n"
        "\tPosts from %s\n"
        "----------------------------------------------\n",
        user->username);

    post_t *ptr = user->posts;

    for (; ptr != NULL; ptr = ptr->next)
    {
        printf("\n%s\n", ptr->content);
    }

    printf("\n");
}

void display_posts_by_n(user_t *user, int number)
{
    char name[30];

    printf("Enter friend who's posts you wish to see: ");
    scanf(" %s", name);

    friend_t *friend_ptr = find_friend(user->friends, name);

    if (friend_ptr == NULL)
    {
        printf("Friend not found\n");
        return;
    }
    if (*(*(friend_ptr)).posts == NULL)
    {
        printf("User has no posts\n");
        return;
    }

    post_t *post_ptr = *(*(friend_ptr)).posts;

    while (post_ptr != NULL)
    {
        for (int i = 0; i < number && post_ptr != NULL; post_ptr = post_ptr->next, i++)
        {
            printf("\n%s\n", post_ptr->content);
        }

        printf("\nSee more? (y/n): ");
        if (!get_yn())
        {
            return;
        }
        else if (post_ptr == NULL)
        {
            printf("\nNo more posts to display\n");
            return;
        }
    }
}

void print_menu()
{
    printf(
        "\n*******************************************\n"
        "\t\tMAIN MENU\n"
        "*******************************************\n"
        "1. Register a new user\n"
        "2. Login existing user\n"
        "3. Exit\n\n"
        "Enter your choice: ");
}

void teardown(user_t *users)
{
    if (users == NULL)
    {
        return;
    }

    user_t *ptr = users;

    for (; ptr != NULL;)
    {
        user_t *temp = ptr->next;
        teardown_friends(ptr);
        teardown_posts(ptr);
        free(ptr);
        ptr = temp;
    }
}

int get_int(int l_limit, int h_limit)
{
    int num = 0;

    scanf("%d", &num);

    while (num < l_limit || num > h_limit)
    {
        printf("Number must be between %d and %d, enter a new number: ", l_limit, h_limit);

        scanf("%d", &num);
    }

    return num;
}

void change_password(user_t *user)
{
    char new_password[15];
    printf("Enter new password: ");
    scanf(" %s", new_password);

    while(strlen(new_password) < 8){
        printf("Password must be at least 8 characters. Enter new password: ");
        scanf(" %s", new_password);
    }

    strcpy(user->password, new_password);
}

void post_menu(user_t *user)
{
    while (true)
    {

        printf(
            "\n----------------------------------------------\n"
            "\tManaging %s's posts"
            "\n----------------------------------------------\n",
            user->username);

        if (user->posts == NULL)
        {
            printf("Note: No posts available for %s\n", user->username);
        }

        printf(
            "1. Add a new post\n"
            "2. Remove a post\n"
            "3. Return to main menu\n"
            "Enter your choice: ");

        int post_choice = get_int(1, 3);

        switch (post_choice)
        {
        case 1:
            char content[250];
            printf("Enter your post's content: ");

            scanf(" %[^\n]s", content);

            add_post(user, content);
            display_all_user_posts(user);
            break;

        case 2:
            if (delete_post(user))
            {
                display_all_user_posts(user);
            }
            else
            {
                printf("User %s has no posts to delete\n", user->username);
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

void friends_menu(user_t *users, user_t *user)
{
    while (true)
    {

        printf(
            "\n----------------------------------------------\n"
            "\tManaging %s's friends"
            "\n----------------------------------------------\n",
            user->username);

        printf(
            "1. Add a new friend\n"
            "2. Remove a friend\n"
            "3. Return to main menu\n"
            "Enter your choice: ");

        int friend_choice = get_int(1, 3);
        char name[30];

        switch (friend_choice)
        {
        case 1:
            printf("Enter new friends name: ");
            scanf(" %s", name);

            user_t *ptr = find_user(users, name);
            if(ptr == NULL){
                printf("User not found\n");
                break;
            }

            add_friend(user, name);

            for(friend_t *new_friend = user->friends; new_friend != NULL; new_friend = new_friend->next){
                if(strcmp(name, new_friend->username) == 0){
                    new_friend->posts = &(ptr->posts);
                }
            }
            break;

        case 2:
            display_user_friends(user);

            printf("Enter friends name to delete: ");
            scanf(" %s", name);

            if (delete_friend(user, name))
            {
                printf("Friend %s was deleted\n", name);
                display_user_friends(user);
            }
            else
            {
                printf("Invalid friend name");
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

_Bool get_yn()
{
    char ans;

    scanf(" %c", &ans);

    while (true)
    {
        if (ans == 'y' || ans == 'Y')
        {
            return true;
        }
        else if (ans == 'n' || ans == 'N')
        {
            return false;
        }

        printf("Enter y or n: ");
        scanf(" %c", &ans);
    }
}

void teardown_posts(user_t *user)
{
    if (user->posts == NULL)
    {
        return;
    }

    post_t *ptr = user->posts;

    for (; ptr != NULL;)
    {
        post_t *temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
}

void teardown_friends(user_t *user)
{
    if (user->friends == NULL)
    {
        return;
    }

    friend_t *ptr = user->friends;

    for (; ptr != NULL;)
    {
        friend_t *temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
}

char *string_to_lower(char *s){
    for(char *ptr = s; *ptr != '\0'; ptr++){
        *ptr = tolower(*ptr);
    }

    return s;
}

user_t *login_user(user_t *users, const char* username, const char* password){
    user_t *ptr = find_user(users, username);
    if(ptr == NULL){
        printf("Invalid Username\n");
        return NULL;
    }

    if(strcmp(ptr->password, password) != 0){
        printf("Invalid Password\n");
        return NULL;
    }

    return ptr;
}

void print_logged_menu(const char* username){
    printf(
        "\n**************************\n"
        "\tWelcome %s"
        "\n**************************\n"
        "1. Manage Profile (Change Password)\n"
        "2. Manage Posts (add/remove)\n"
        "3. Manage Friends (add/remove)\n"
        "4. Display Friends Posts\n"
        "5. Exit\n"
        "Enter your choice: "
        , username);
}

void logged_menu(user_t *users, user_t *user){
    while(true){
        print_logged_menu(user->username);

        int choice = get_int(1, 5);

        switch (choice)
        {
        case 1:
            change_password(user);
            break;

        case 2:
            post_menu(user);
            break;
        
        case 3:
            friends_menu(users, user);
            break;

        case 4:
            display_posts_by_n(users, 3);
            break;

        case 5:
            return;
            break;
        default:
            break;
        }
    }
}

friend_t *find_friend(friend_t *friends, const char *friend){
    friend_t *ptr = friends;

    for( ; ptr != NULL; ptr = ptr->next){
        if(strcmp(ptr->username, friend) == 0){
            return ptr;
        }
    }

    return NULL;
}

void add_CSV_friends(user_t *users){
    for(user_t *u = users; u != NULL; u = u->next){
        for(friend_t *f = u->friends; f != NULL; f = f->next){
            user_t *ptr = find_user(users, f->username);

            assert(ptr != NULL);

            f->posts = &(ptr->posts);
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
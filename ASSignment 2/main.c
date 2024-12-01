/********* main.c ********
    Student Name 	= Nicholas Dorscht
    Student Number	= 101298132
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#define NUM_POSTS 3

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);
    add_CSV_friends(users);

    fclose(csv_file);

    // Print main menu
    // Main loop

    while (true)
    {
        char username[30];
        char password[15];

        print_menu();
        int user_choice = get_int(1, 3);

        switch (user_choice)
        {
        case 1:
            printf("Enter a username: ");
            scanf(" %s", username);

            if(find_user(users, string_to_lower(username)) != NULL) {
                printf("Username already in use!\n");
                break;
            }

            printf("Enter an up to 15 character password: ");
            scanf(" %s", password);

            while(strlen(password) < 8){
                printf("Password must be at least 8 characters. \nEnter new password: ");
                scanf(" %s", password);
            }
            
            users = add_user(users, string_to_lower(username), password);
            break;

        case 2:
            printf("Enter a username: ");
            scanf(" %s", username);

            strcpy(username, string_to_lower(username));

            printf("Enter password: ");
            scanf(" %s", password);

            user_t *user = login_user(users, username, password);

            if(user == NULL) { break; }

            logged_menu(users, user);

            break;

        case 3: 
            printf("Thank you for using Facebook!\n");
            teardown(users);
            return EXIT_SUCCESS;
            break;

        default:
            continue;
        }
    }
}
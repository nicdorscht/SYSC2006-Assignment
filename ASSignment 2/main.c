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

    fclose(csv_file);
 
    //Print main menu
        //Main loop

        while(true){

            print_menu();
            int user_choice = get_int(1, 6);

            switch(user_choice){
                case 1: 
                    char username[30];
                    char password[15];

                    printf("Enter a username: ");
                    scanf(" %s", username);
                    printf("Enter an up to 15 character password: ");
                    scanf(" %s", password);

                    users = add_user(users, username, password);
                break;

                case 2:
                    change_password(users);
                break;

                case 3:
                    post_menu(users);
                break;

                case 4:
                    friends_menu(users);
                break;

                case 5:
                    display_posts_by_n(users, NUM_POSTS);
                break;

                case 6:
                    printf("Thank you for using Facebook!\n");
                    teardown(users);
                    return EXIT_SUCCESS;
                    break;

                default:
                    continue;
            }
        }
}
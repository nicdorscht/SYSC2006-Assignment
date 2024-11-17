/********* main.c ********
    Student Name 	=
    Student Number	=
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

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
    printf(
        "*******************************************\n"
        "\t\tMAIN MENU\n"
        "*******************************************\n"
        "1. Register a new user\n"
        "2. Manage a user's profile (change password)\n"
        "3. Manage a user's posts (add/remove)\n"
        "4. Manage a user's friends (add/remove)\n"
        "5. Display a user's posts\n"
        "6. Exit"
        );
}
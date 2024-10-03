/********* main.c ********
	
	Student Name 	= Nicholas Dorscht
	Student Number	= 101298132
*/

//Complete the includes
#include <stdlib.h>
#include <stdio.h>
#include "a1_functions.h"

#define MAX_MILESTONES 5

int main()
{

    char project_name[100];
    unsigned short int num_milestones = 0;
    milestone_t milestone_list[MAX_MILESTONES];

    /** 1-  Display a welcome message **/
    printf("\n/**********Welcome to the project management system!**********\\\n\n");

    /** 2- Get the project's name and number of milestones **/
    printf("Enter project name: ");
    get_input_str(project_name);

    printf("\nEnter number of milestones: ");
    num_milestones = get_input_usi();

    while(num_milestones < 1 || num_milestones > 5){
        printf("The number of milestones must be between 1 and 5\nEnter number of milestones: ");
        num_milestones = get_input_usi();
    }
    
    /** 3- Initialize all milestones and activities.
     * You need an array of milestones. 
     * The capacity of the array must be the max number of milestones the program 
     * can handle as per the instructions **/
    for(int i = 0; i < num_milestones; i++){
        printf("Enter number of activities for Milestone %d: ", i + 1);
        unsigned short int num_activities = get_input_usi();

        while(num_activities < 1 || num_activities > 3){
            printf("Number of activities must be between 1 and 3\nEnter number of activities for Milestone %d: ", i + 1);
            num_activities = get_input_usi();
        }

        init_milestone(&milestone_list[i], num_activities);
    }
    
    /** 4- Initialize the project **/
    

    /** 5- Print the main menu **/

   

    /** 6- Get user choice and handle it as per the instructions**/
    

    return EXIT_SUCCESS;
}
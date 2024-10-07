/********* main.c ********
	
	Student Name 	= Nicholas Dorscht
	Student Number	= 101298132
*/

//Complete the includes
#include <stdlib.h>
#include <stdio.h>
#include "a1_functions.h"

#define MAX_MILESTONES 5
#define MAX_ACTIVITIES 3

int main()
{
    char project_name[100];
    unsigned short int num_milestones = 0;
    milestone_t milestone_list[MAX_MILESTONES];
    int num_activities_per_milestone[MAX_MILESTONES];
    unsigned short int milestone_ids[MAX_MILESTONES] = {0};
    unsigned short int activity_ids[MAX_MILESTONES * MAX_ACTIVITIES] = {0};

    /** 1-  Display a welcome message **/
    printf("\n/********** Welcome to the project management system! **********\\\n\n");

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
        printf("\n/******** Milestone %d ********\\\n\n", i + 1);

        printf("Enter number of activities for Milestone %d: ", i + 1);
        unsigned short int num_activities = get_input_usi();

        while(num_activities < 1 || num_activities > 3){
            printf("Number of activities must be between 1 and 3\nEnter number of activities for Milestone %d: ", i + 1);
            num_activities = get_input_usi();
        }

        init_milestone(&milestone_list[i], num_activities);
        num_activities_per_milestone[i] = num_activities;

        dupe_id(milestone_ids, activity_ids, &milestone_list[i]);
    }
    
    /** 4- Initialize the project **/
    project_t project = init_project(project_name, milestone_list, num_milestones, num_activities_per_milestone);

    /** 5- Print the main menu **/
     print_main_menu();
   

    /** 6- Get user choice and handle it as per the instructions**/
    


    return EXIT_SUCCESS;
}
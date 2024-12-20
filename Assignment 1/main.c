/********* main.c ********
	
	Student Name 	= Nicholas Dorscht
	Student Number	= 101298132
*/

//Complete the includes
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "a1_functions.h"

int main()
{
    char project_name[100];
    unsigned short int num_milestones = 0;
    milestone_t *milestone_list;

    node_t *milestoneIDs = malloc(sizeof(node_t));
    assert(milestoneIDs != NULL);
    *milestoneIDs = (node_t) {0, NULL};

    node_t *activityIDs = malloc(sizeof(node_t));
    assert(activityIDs != NULL);
    *activityIDs = (node_t) {0, NULL};

    /** 1-  Display a welcome message **/
    printf("\n/********** Welcome to the project management system! **********\\\n\n");

    /** 2- Get the project's name and number of milestones **/
    printf("Enter project name: ");
    get_input_str(project_name);

    printf("\nEnter number of milestones: ");
    num_milestones = get_input_usi();

    milestone_list = malloc(sizeof(milestone_t) * num_milestones);
    assert(milestone_list != NULL);

    
    /** 3- Initialize all milestones and activities.
     * You need an array of milestones. 
     * The capacity of the array must be the max number of milestones the program 
     * can handle as per the instructions **/
    for(int i = 0; i < num_milestones; i++){
        printf("\n/******** Milestone %d ********\\\n\n", i + 1);

        printf("Enter number of activities for Milestone %d: ", i + 1);
        unsigned short int num_activities = get_input_usi();

        init_milestone(&milestone_list[i], num_activities, milestoneIDs, activityIDs);
    }
    
    /** 4- Initialize the project **/
    project_t project = init_project(project_name, milestone_list, num_milestones);

    /** 5- Print the main menu **/
     print_main_menu();
   

    /** 6- Get user choice and handle it as per the instructions**/
    while(true){

        unsigned short int user_choice = get_input_usi();

        while(user_choice < 1 || user_choice > 3){
            printf("Invalid Entry, enter a new value\n");
            user_choice = get_input_usi();
        }

        switch (user_choice)
        {
        case 1:
            change_submenu(milestone_list, num_milestones, &project);
            update_project(milestone_list, num_milestones, &project);
            break;

        case 2:
            print_project_stats(project, milestone_list, num_milestones);
            break;

        case 3:
            free_everyting(milestone_list, num_milestones);
            free_linked_list(milestoneIDs);
            free_linked_list(activityIDs);
            
            return EXIT_SUCCESS;
        }

        print_main_menu();
    }


    return EXIT_SUCCESS;
}
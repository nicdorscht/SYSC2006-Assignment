/********* a1_functions.h ********
	
	Student Name 	= Nicholas Dorscht
	Student Number	= 101298132
*/

#ifndef __A1_FUNCTIONS_H__

#define __A1_FUNCTIONS_H__

#endif

#include "a1_data_structures.h"
#include <stdbool.h>

/********** ID CHECKING EXPLANATION *************/
/*
   In order to simplify the id checking process, I first implemented a linked list, using a node struct,
   allowing the number of stored IDs to grow with the user's needs. I then changed the function 
   declarations for init_milestone and init_activity to include a pointer to the Id lists. This allowed 
   me to check the ID as soon as it was entered, instead of having to wait for the end of each milestone. 
   This meant that the user could only be met with one invalid ID at a time, instead of having to deal with several 
   at the end of every milestone. This process also vastly simplified the dupe_id function, shrinking it as it only needed
   to check through one Id at a time, instead of looping thorough an entire milestone, saving complexity and time.
*/


/********** DON'T MODIFY - FROM HERE **********/
/* 
   Get unsigned short integer user input.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
unsigned short int get_input_usi(void);

/*
   Get float user input. The value must be positive.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
float get_input_f(void);

/* 
   Initialize all fields in an activity as per the instructions (3)
*/
void init_activity(activity_t * activity_to_int, node_t *activityIDs);
/* 
   Initialize all fields in the milestone as per the instructions (3)
   The implementation of your function MUST call the function init_activity.
*/
void init_milestone(milestone_t *milestone_to_int, unsigned short int num_activities, node_t *milestoneIDs, node_t *activityIDs);


/* 
   Initialize all fields in the project as per the instructions (4)
   number_activities contains the number of activities per milestone
*/
project_t init_project(char name[], milestone_t *milestone_list, int number_milestones);


/* 
   Print the main menu as per the instructions (5)
*/
void print_main_menu(void);

/*
   Print out milestone stats as per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void print_milestone_stats(const milestone_t * list_milestones, int num_milestones);

/*
   Print out project stats as per the instructions (6)
   number_activities contains the number of activities per milestone
   The implementation MUST call print_stats_milestone
*/
void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones);

/*
   Update activity per the instructions (6)
*/
void update_activity(activity_t * activity_to_update);
/*
   Update milestone per the instructions (6)
*/
void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone);

/*
   Update project per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void update_project(const milestone_t * milestone_array, int num_milestones, project_t * my_project);

/********** DON'T MODIFY - UNTIL HERE **********/


// Extra function prototypes/declarations go here
void get_input_str(char destination[]);

void get_id(unsigned short int * id);

void dupe_id(node_t *IDList, unsigned short int *id);

void change_submenu(milestone_t * milestone_array, int num_milestones, project_t * my_project);

void free_everyting(milestone_t *milestone_list, int num_milestones);

void free_linked_list(node_t *list_head);
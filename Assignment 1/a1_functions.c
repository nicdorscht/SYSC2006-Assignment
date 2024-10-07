/********* a1_functions.c ********
	
	Student Name 	= Nicholas Dorscht
	Student Number	= 101298132
*/

#include "a1_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SALARY 30
#define MAX_ACTIVITIES 3
#define DAY_LENGTH 8
#define MAX_MILESTONES 5

unsigned short int get_input_usi(void){

	short int num = 0;

	scanf("%hi", &num);					//Take a signed int so that a negative number doesn't flip to max value

	while(num <= 0){
		printf("Must be a positive integer: ");
		scanf("%hi", &num);
	}

	return (unsigned short int) num;	//Cast back to unsigned short int
}

float get_input_f(void){
	float num = 0;

	scanf("%d", &num);

	while(num <= 0){
		printf("Must be a positive number: ");
		scanf("%d", &num);
	}

	return num;
}

void init_activity(activity_t * activity_to_int){

	get_id(&activity_to_int->id);

	printf("Enter activity name: ");
	get_input_str(activity_to_int->name);

	printf("Input activity duration in hours: ");
	activity_to_int->planned_duration = get_input_usi();

	activity_to_int->planned_cost = activity_to_int->planned_duration * SALARY;
	activity_to_int->actual_cost = 0;
	activity_to_int->actual_duration = 0;
	activity_to_int->completed = false;
}

void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities){

	get_id(&milestone_to_int->id);

	printf("Enter milestone name: ");
	get_input_str(milestone_to_int->name);

	for(int i = 0; i < num_activities; i++){
		printf("\n/**** Activity %d ****\\\n\n", i + 1);
		init_activity(&milestone_to_int->activity_list[i]);	
	}

	milestone_to_int->completed = false;
	milestone_to_int->actual_cost = 0;
	milestone_to_int->actual_duration = 0;
}

project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities){
	float planned_cost = 0;
	unsigned short int planned_duration = 0;

	for(int i = 0; i < number_milestones; i++){
		for(int j = 0; j < number_activities[i]; j++){
			planned_cost += milestone_list[i].activity_list[j].planned_cost;
			planned_duration += milestone_list[i].activity_list[j].planned_duration;
		}
	}

	planned_duration = (planned_duration + (DAY_LENGTH - 1)) / DAY_LENGTH;

	project_t proj = {"Temp", planned_cost, 0, planned_duration, 0, false};
	strcpy(proj.name, name);

	return proj;
}

void print_main_menu(void){
	printf("\nPlease select one of the following options:\n"
			"1. Update Activity\n"
			"2. Print stats\n"
			"3. Exit\n"
			);
}

void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities){
	for(int i = 0; i < num_milestones; i++){
		if(list_milestones[i].completed == true){
			printf("Milestone: %s\n"
				"The milestone was $%d %s\n"
				"The milestone was %d days %s\n\n",
				list_milestones[i].name,
				abs(list_milestones[i].actual_cost),
				list_milestones[i].activity_list >= 0 ? "over budget" : "under budget",
				list_milestones[i].actual_duration,
				list_milestones[i].actual_duration >= 0 ? "delayed" : "early"
				);
		} else {
			float total_cost = 0;
			unsigned short int total_duration = 0;
			unsigned short int completed_activities = 0;
			unsigned short int total_activities = 0;
			for(int j = 0; j < number_activities[i]; j++){
				if(list_milestones[i].activity_list[j].id > 0){// Check for valid id
					total_cost += list_milestones[i].activity_list[j].planned_cost;
					total_duration += list_milestones[i].activity_list[j].planned_duration;
					total_activities++;

					if(list_milestones[i].activity_list[j].completed){
						completed_activities++;
					}
				}
			}

			printf("Milestone: %s\n"
			"Activities Completed: %hi/%hi\n"
			"Planned Duration: %hi hours\n"
			"Planned Cost: $%.2f\n\n",
			list_milestones[i].name, completed_activities, total_activities, total_duration, total_cost);
		}
	}
}

void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities){
	printf("\n/***** %s *****\\\n"
	"Project Status: %s\n\n",
	details.name, details.completed ? "Complete" : "Incomplete");

	print_milestone_stats(list_milestones, num_milestones, number_activities);
}

void update_activity(activity_t * activity_to_update){
	printf("Enter actual duration for activity %s (%d): ", activity_to_update->name, activity_to_update->id);
	activity_to_update->actual_duration = get_input_usi();

	activity_to_update->actual_cost = activity_to_update->actual_duration * SALARY;

	printf("Is the activity %s (%d) complete? 1/0: ", activity_to_update->name, activity_to_update->id);
	unsigned short int complete_choice = get_input_usi();

	if(complete_choice == 1) {
		activity_to_update->completed = true;
	} else{
		activity_to_update->completed = false;
	}
}

void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone){
	for(int i = 0; i < activities_in_milestone; i++){
		if(milestone_to_update->activity_list[i].completed == false){
			return;
		} else {
			milestone_to_update->actual_cost += milestone_to_update->activity_list[i].actual_cost;
			milestone_to_update->actual_duration += milestone_to_update->activity_list[i].actual_duration;
		}
	}

	milestone_to_update->completed = true;
}

void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project){
	_Bool completed = true;
	unsigned short int temp_dur = 0;
	
	for(int i = 0; i < num_milestones; i++){
		if(milestone_array[i].completed == false){
			completed = false;
		}

		my_project->actual_cost += milestone_array[i].actual_cost;
		temp_dur += milestone_array[i].actual_duration;
	}

	my_project->actual_duration = temp_dur / 8;
	my_project->completed = completed;
}

void get_input_str(char destination[]){
	scanf("%s", destination);
}

void get_id(short unsigned int * id){

	short int temp;
	printf("Enter ID: ");
	temp = get_input_usi();

	while(temp < 1){
		printf("ID must be a positive integer");
		temp = get_input_usi();
	}

	*id = (unsigned short int) temp;
}

_Bool dupe_id(unsigned short int * milestone_ids, unsigned short int * activity_ids, milestone_t * milestone_ptr){
	//Check for milestone id first
	for(int i = 0; i < MAX_MILESTONES; i++){ //Loop over existing ids to check for duplicates
		if(milestone_ids[i] == 0){ // Check if at end of existing ids, if so add id and break the loop
			milestone_ids[i] = milestone_ptr->id;
			break;
		}
		while(milestone_ptr->id == milestone_ids[i]){ // Id id is the same loop until user enters a unique one
			printf("Milestone %s's ID is a duplicate, please enter a new one.\n", milestone_ptr->name);
			get_id(&milestone_ptr->id);
			i = 0;		//Reset to start of id array so that user can't enter one that is earlier in the array
		}
	}
	//Now check for activity id
	for(int i = 0; i < MAX_ACTIVITIES; i++){ // Loop over all activities in the milestone
		for(int j = 0; j < MAX_ACTIVITIES * MAX_MILESTONES; j++){ // Loop over all existing activity ids
			if(activity_ids[j] == 0){
				activity_ids[j] = milestone_ptr->activity_list[i].id;
				break;
			}

			while(milestone_ptr->activity_list[i].id == activity_ids[j]){//Check for repeated ID
				printf("Activity %s's ID (%d) is a duplicate, please enter a new one.\n"
				, milestone_ptr->activity_list[i].name, milestone_ptr->activity_list[i].id);

				get_id(&milestone_ptr->activity_list[i].id);
				j = 0;
			}
		}
	}	
}

void change_submenu(milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project){
	printf("/*****Activities*****\\\n");
	printf("ID\t\tName\t\tStatus\n");

	for(int i = 0; i < num_milestones; i++){
		for(int j = 0; j < number_activities[i]; j++){
			activity_t current = milestone_array[i].activity_list[j];
			printf("%d\t\t%s\t\t%s\n", current.id, current.name, current.completed ? "\033[0;32m" "Complete \033[0m" : "\033[0;31m" "Incomplete \033[0m");
		}
	}

	printf("Enter the id of the activity you wish to change: ");
	unsigned short int choice = get_input_usi();

	_Bool valid_id = false;

	while(true){
		for(int i = 0; i < num_milestones; i++){
			for(int j = 0; j < number_activities[j]; j++){
				if(milestone_array[i].activity_list[j].id == choice){
					valid_id = true;
					update_activity(&milestone_array[i].activity_list[j]);
					update_milestone(&milestone_array[i], number_activities[i]);
					break;
				}
			}
		}
		if(!valid_id){
			printf("Invalid ID. Enter new ID: ");
			choice = get_input_usi();
		} else {
			break;			
		}
	}
}
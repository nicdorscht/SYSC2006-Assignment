/********* a1_functions.c ********

	Student Name 	= Nicholas Dorscht
	Student Number	= 101298132
*/

#include "a1_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define SALARY 30
#define DAY_LENGTH 8

unsigned short int get_input_usi(void)
{

	short int num = 0;

	scanf("%hi", &num); // Take a signed int so that a negative number doesn't flip to max value

	while (num <= 0)
	{
		printf("Must be a positive integer: ");
		scanf("%hi", &num);
	}

	return (unsigned short int)num; // Cast back to unsigned short int
}

float get_input_f(void)
{
	float num = 0;

	scanf("%d", &num);

	while (num <= 0)
	{
		printf("Must be a positive number: ");
		scanf("%d", &num);
	}

	return num;
}

void init_activity(activity_t *activity_to_int, node_t *activityIDs)
{
	get_id(&activity_to_int->id);

	dupe_id(activityIDs, &activity_to_int->id);

	printf("Enter activity name: ");
	get_input_str(activity_to_int->name);

	printf("Input activity duration in hours: ");
	activity_to_int->planned_duration = get_input_usi();

	activity_to_int->planned_cost = activity_to_int->planned_duration * SALARY;
	activity_to_int->actual_cost = 0;
	activity_to_int->actual_duration = 0;
	activity_to_int->completed = false;
}

void init_milestone(milestone_t *milestone_to_int, unsigned short int num_activities, node_t *milestoneIDs, node_t *activityIDs)
{

	get_id(&milestone_to_int->id);
	dupe_id(milestoneIDs, &milestone_to_int->id);

	printf("Enter milestone name: ");
	get_input_str(milestone_to_int->name);

	milestone_to_int->activity_list = malloc(sizeof(activity_t) * num_activities);
	assert(milestone_to_int->activity_list != NULL);

	for (int i = 0; i < num_activities; i++)
	{
		printf("\n/**** Activity %d ****\\\n\n", i + 1);
		init_activity(&milestone_to_int->activity_list[i], activityIDs);
	}

	milestone_to_int->num_activities = num_activities;
	milestone_to_int->completed = false;
	milestone_to_int->actual_cost = 0;
	milestone_to_int->actual_duration = 0;
}

project_t init_project(char name[], milestone_t *milestone_list, int number_milestones)
{
	float planned_cost = 0;
	unsigned short int planned_duration = 0;

	for (int i = 0; i < number_milestones; i++)
	{
		for (int j = 0; j < milestone_list[i].num_activities; j++)
		{
			planned_cost += milestone_list[i].activity_list[j].planned_cost;
			planned_duration += milestone_list[i].activity_list[j].planned_duration;
		}
	}

	planned_duration = (planned_duration + (DAY_LENGTH - 1)) / DAY_LENGTH;

	project_t proj = {"Temp", planned_cost, 0, planned_duration, 0, false};
	strcpy(proj.name, name);

	return proj;
}

void print_main_menu(void)
{
	printf("\nPlease select one of the following options:\n"
		   "1. Update Activity\n"
		   "2. Print stats\n"
		   "3. Exit\n");
}

void print_milestone_stats(const milestone_t *list_milestones, int num_milestones)
{
	for (int i = 0; i < num_milestones; i++)
	{
		if (list_milestones[i].completed == true)
		{
			printf("Milestone: %s\n"
				   "The milestone was $%d %s\n"
				   "The milestone was %d hours %s\n\n",
				   list_milestones[i].name,
				   abs(list_milestones[i].actual_cost),
				   list_milestones[i].activity_list >= 0 ? "over budget" : "under budget",
				   abs(list_milestones[i].actual_duration),
				   list_milestones[i].actual_duration >= 0 ? "delayed" : "early");
		}
		else
		{
			float total_cost = 0;
			unsigned short int total_duration = 0;
			unsigned short int completed_activities = 0;
			unsigned short int total_activities = 0;
			for (int j = 0; j < list_milestones[i].num_activities; j++)
			{
				if (list_milestones[i].activity_list[j].id > 0)
				{ // Check for valid id
					total_cost += list_milestones[i].activity_list[j].planned_cost;
					total_duration += list_milestones[i].activity_list[j].planned_duration;
					total_activities++;

					if (list_milestones[i].activity_list[j].completed)
					{
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

void print_project_stats(project_t details, const milestone_t *list_milestones, int num_milestones)
{
	printf("\n/***** %s *****\\\n"
		   "Project Status: %s\n\n",
		   details.name, details.completed ? "Complete" : "Incomplete");

	unsigned short int temp_days = 0;

	if (details.completed)
	{
		printf("Project was %d days %s\n"
			   "Project was $%d %s budget.\n\n",
			   abs(details.actual_duration - details.planned_duration), details.actual_duration - details.planned_duration > 0 ? "late" : "early",
			   abs(details.actual_cost - details.planned_cost), details.actual_cost - details.planned_cost > 0 ? "over" : "under");
	}

	print_milestone_stats(list_milestones, num_milestones);
}

void update_activity(activity_t *activity_to_update)
{
	printf("Enter actual duration for activity %s (%d): ", activity_to_update->name, activity_to_update->id);
	activity_to_update->actual_duration = get_input_usi();

	printf("Enter actual cost for activity %s (%d): ", activity_to_update->name, activity_to_update->id);
	activity_to_update->actual_duration = get_input_usi();

	printf("Is the activity %s (%d) complete? y/n: ", activity_to_update->name, activity_to_update->id);
	char complete_choice;

	scanf(" %c", &complete_choice);

	if (complete_choice == 'y' || complete_choice == 'Y')
	{
		activity_to_update->completed = true;
	}
	else
	{
		activity_to_update->completed = false;
	}
}

void update_milestone(milestone_t *milestone_to_update, int activities_in_milestone)
{
	for (int i = 0; i < activities_in_milestone; i++)
	{
		if (milestone_to_update->activity_list[i].completed == false)
		{
			return;
		}
		else
		{
			milestone_to_update->actual_cost += milestone_to_update->activity_list[i].actual_cost;
			milestone_to_update->actual_duration += milestone_to_update->activity_list[i].actual_duration;
		}
	}

	milestone_to_update->completed = true;
}

void update_project(const milestone_t *milestone_array, int num_milestones, project_t *my_project)
{
	_Bool completed = true;
	unsigned short int temp_dur = 0;
	unsigned short int temp_cost = 0;

	for (int i = 0; i < num_milestones; i++)
	{
		if (milestone_array[i].completed == false)
		{
			completed = false;
		}
		else
		{
			temp_cost += milestone_array[i].actual_cost;
			temp_dur += milestone_array[i].actual_duration;
		}
	}

	my_project->actual_cost = temp_cost;
	my_project->actual_duration = (temp_dur + (DAY_LENGTH - 1)) / DAY_LENGTH;
	my_project->completed = completed;
}

void get_input_str(char destination[])
{
	scanf("%s", destination);
}

void get_id(unsigned short int *id)
{

	short int temp;
	printf("Enter ID: ");
	temp = get_input_usi();

	while (temp < 1)
	{
		printf("ID must be a positive integer");
		temp = get_input_usi();
	}

	*id = (unsigned short int)temp;
}

void dupe_id(node_t *IDList, unsigned short int *id)
{
	node_t *ptr = IDList;

	while(true){
		if(ptr->ID == *id){
			printf("Duplicate ID, enter a new one: ");
			get_id(id);
			ptr = IDList;
		} else if(ptr->next != NULL){
			ptr = ptr->next;
		} else{
			ptr->next = malloc(sizeof(node_t));
			ptr = ptr->next;
			*ptr = (node_t) {*id, NULL};
			break;
		}
	}
}

void change_submenu(milestone_t *milestone_array, int num_milestones, project_t *my_project)
{
	printf("/*****Activities*****\\\n");
	printf("ID\t\tName\t\tStatus\n");

	_Bool all_complete = true;

	for (int i = 0; i < num_milestones; i++)
	{
		for (int j = 0; j < milestone_array[i].num_activities; j++)
		{
			activity_t current = milestone_array[i].activity_list[j];
			printf("%d\t\t%s\t\t%s\n", current.id, current.name, current.completed ? "\033[0;32m"
																					 "Complete \033[0m"
																				   : "\033[0;31m"
																					 "Incomplete \033[0m");
			if (current.completed == false)
			{
				all_complete = false;
			}
		}
	}

	if (all_complete)
	{
		printf("\nAll activities complete, nothing to update.\n");
		return;
	}

	printf("Enter the id of the activity you wish to change: ");
	unsigned short int choice = get_input_usi();

	_Bool valid_id = false;

	while (true)
	{
		for (int i = 0; i < num_milestones; i++)
		{
			for (int j = 0; j < milestone_array[i].num_activities; j++)
			{
				if (milestone_array[i].activity_list[j].id == choice)
				{
					valid_id = true;
					update_activity(&milestone_array[i].activity_list[j]);
					update_milestone(&milestone_array[i], milestone_array[i].num_activities);
					break;
				}
			}
		}
		if (!valid_id)
		{
			printf("Invalid ID. Enter new ID: ");
			choice = get_input_usi();
		}
		else
		{
			break;
		}
	}
}

void free_everyting(milestone_t *milestone_list, int num_milestones){
	for(int i = 0; i < num_milestones; i++){
		free(milestone_list->activity_list);
	}

	free(milestone_list);
}

void free_linked_list(node_t *list_head){
	if(list_head->next != NULL){
		free_linked_list(list_head->next);
	}

	free(list_head);
}
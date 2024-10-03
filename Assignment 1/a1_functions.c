/********* a1_functions.c ********
	
	Student Name 	= Nicholas Dorscht
	Student Number	= 101298132
*/

#include "a1_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
	
}

void init_milestone(milestone_t * milestone_to_int, unsigned short int num_activities){

}

project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int * number_activities){

}

void print_main_menu(void){

}

void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities){

}

void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities){

}

void update_activity(activity_t * activity_to_update){

}

void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone){

}

void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project){
	
}

void get_input_str(char destination[]){
	scanf("%s", destination);
}
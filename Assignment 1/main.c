/********* main.c ********
	
	Student Name 	= Nicholas Dorscht
	Student Number	= 101298132
*/

//Complete the includes
#include <stdlib.h>
#include <stdio.h>
#include "a1_functions.h"



int main()
{

    char project_name[100];
    unsigned short int num_milestones = 0;

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

    
    
    /** 4- Initialize the project **/
    

    /** 5- Print the main menu **/

   

    /** 6- Get user choice and handle it as per the instructions**/
    

    return EXIT_SUCCESS;
}
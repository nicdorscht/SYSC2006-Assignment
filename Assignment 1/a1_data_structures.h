/********* a1_data_structures.h ********
	
	Student Name 	= Nicholas Dorscht
	Student Number	= 101298132
*/
#include <stdbool.h>

#ifndef __A1_DATA_STRUCTURES_H__

#define __A1_DATA_STRUCTURES_H__
#define NUM_ACTIVITIES 3

#endif
/********** DON'T MODIFY FROM HERE **********/

typedef struct activity {
    unsigned short int id;
    char name[100];
    float planned_cost, actual_cost;
    unsigned short int planned_duration, actual_duration;
    _Bool completed;
}activity_t;

typedef struct milestone {
    unsigned short int id;
    char name[100];
    activity_t activity_list[NUM_ACTIVITIES];
    _Bool completed;
    float actual_cost;
    short int actual_duration;
}milestone_t;

typedef struct project {
    char name[100]; 
    float planned_cost, actual_cost;
    unsigned short int planned_duration, actual_duration;
    _Bool completed;
}project_t;

/********** DON'T MODIFY UNTIL HERE **********/
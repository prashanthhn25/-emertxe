#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define MAXPARTICIPANTS 30
#define NOTUNIQUE 1
#define UNIQUE 2

int checkUnique(int array[], int size);

int main()
 {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int no_of_participants, iter;
    int participantId[MAXPARTICIPANTS];
    int i, j;
    int modVal;
    int modShortVals[MAXPARTICIPANTS];
    int flag2;
    int checkResult;
	
    //get the total number of participants	    	
    scanf("%d", &no_of_participants);

    //check for out of range
    if (no_of_participants < 1)
    {
        printf("ERROR: Out of range\n");
        return 1;
    }
    else if (no_of_participants > 30)
    {
        printf("ERROR: Out of range\n");
        return 1;
    }
    else
    {
	printf("no_of_participants: %d\n", no_of_participants);
	//to get 4 digit ids from user printf("i: %d", i);
        for(i = 0; i < no_of_participants; i++)
	{
		 printf("i: %d -> ", i);
	    scanf("%d", &participantId[i]);
	
	    if(participantId[i] < 1000)
	    {
		printf("ERROR: Id should be 4 digits\n");
        	return 1;
	    }
	    if(participantId[i] > 9999)
	    {
		printf("ERROR: Id should be 4 digits\n");
        	return 1;
	    }	
	}

	//check for unique id entry
	checkResult = checkUnique(participantId, no_of_participants);
	if (checkResult == NOTUNIQUE)
	{
		printf("Error Not Unique\n");
		return 1;
	}
	
	//to get the shortids 
	for(modVal =0; ; modVal++)
	{
		flag2 = 0;
	    //get the mod values	
	    for(i = 0; i < no_of_participants; i++)
	    {
		modShortVals[i] = participantId[i]%(2+modVal);
	    }
		
	    //check for unique id
	    checkResult = checkUnique(modShortVals, no_of_participants);
	    if (checkResult == NOTUNIQUE)
	    {
		flag2 = 1;
	    }
			
	    if(!flag2)
	    {
		printf("%d \n", modVal+2);
	        break; 
	    }
		
	}
    }   
       return 0;
}

int checkUnique(int array[], int size)
{
	int i, j;

	for(i = 0; i < size; i++)
	{
	    for(j = (i+1); j < size; j++)
	    {
		if(j != i)
		{
			if(array[j] == array[i])
			{
		    		return NOTUNIQUE;
		   	}
		}

	    }
	}

	return UNIQUE;
}

#include "textindex.h"

void wordCountHTInit(File_Word_Table *temptable)
{
	
    	int i;

	//initialize the values for the table
	for( i = 0; i < INITIAL_SIZE; i++)
	{
		temptable -> wordCountTable[i] = NULL;
	}

}

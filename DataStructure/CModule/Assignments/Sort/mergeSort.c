#include "sort.h"


int mergeSort(int array[], int narray)
{
	int i, mid;

	if (narray == 1)
	{	
		return SUCCESS;
	}

	//initailize
	mid = narray/2;

	//allocate memory
	int *left = (int *)malloc (mid * sizeof(int));
	if(NULL == left)
	{
		printf("No memory\n");
		return FAILURE;
	}

	int *right = (int *)malloc ((narray-mid) * sizeof(int));
	if(NULL == right)
	{
		printf("No memory\n");
		return FAILURE;
	}

	for (i = 0; i < mid; i++)
	{
		left[i] = array[i];
	}

	for (i = mid; i < narray; i++)
	{
		right[i-mid] = array[i];
	}

	mergeSort(left, mid);
	mergeSort(right, (narray - mid));

	merge(array, narray, left, mid, right, (narray - mid));

	free(left);
	free(right);	
}

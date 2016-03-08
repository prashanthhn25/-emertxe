/*
 * To check whether a given number is odd or even and
 * it's signedness using Nested if
 *
 * Eg: If input is -1, it should print -1 is negative odd number.
 *
 */

#include <stdio.h>

int main()
{
	int givenNum;
	
	printf("Enter a number:\n");
	scanf("%d", &givenNum);

    /* To check for positive number */
	if( givenNum > 0 )
    {
        /* To check for positive even and odd number */
		if ( givenNum % 2 == 0 )
		{
			printf("%d is positive even number.\n", givenNum);
		}
		else
		{
			printf("%d is positive odd number.\n", givenNum);
		}
	}
     /* To check for negative number */
	else if( givenNum < 0 )
	{
         /* To check for negative even and odd number */
		if (givenNum % 2 == 0 )
		{
			printf("%d is negative even number.\n", givenNum);
		}
		else
		{
			printf("%d is negative odd number.\n", givenNum);
		}
	}
     /* To check for zero */
	else
	{
		printf("%d is zero.\n", givenNum);
	}
	
	return 0;
}	

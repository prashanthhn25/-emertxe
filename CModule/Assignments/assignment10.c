/*
 * Q. Read n and generate fibonacci nos. <= n
 *
 *  a. Read positive number n from user.
 *  b. Do error checking.
 *      -> Check n is negative or not.
 *      -> If negative continue from a.
 *      -> else do step c.
 *  c. Print all fibonacci numbers from 0 to n
 *  d. Prompt for Continue option.
 *
 *  Prerequisites:
 *  --------------
 *  Looping Concepts.
 *
 *  Sample Execution
 *  ----------------
 *
 *  Enter a Positive Number: 10
 *
 *  Fibonacci series between 0 and 10 --->
 *
 *  0 1 1 2 3 5 8
 *
 *  Continue (y/n):
 */

#include <stdio.h>

int main()
{
	int givenNum;
    int fib1, fib2, temp, flag;
    char option;
    
    do
    {
        fib1 = 0;
        fib2 = 1;
        flag = 0;
        
        /* Do error checking */
        do
        {
            /* Read positive number n from user. */
            printf("Enter a Positive Number: ");
            scanf("%d", &givenNum);
            
            /* Negative number check */
            if (givenNum < 0)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        } while (flag);
    
        /* Print all fibonacci numbers from 0 to givenNum */
        printf("Fibonacci series between 0 and %d --->\n", givenNum);
        
        /* generate the fibonacii numbers <= givenNum */
        while (fib1 <= givenNum)
        {
            printf("%d ", fib1);
            temp = fib1;
            fib1 += fib2;
            fib2 = temp;
        }
        printf("\n");
        
        /* Prompt for Continue option */
        printf("Continue (y/n): ");
        scanf("\n%c", &option);
        
        if ( option == 'y' )
        {
            continue;
        }
        else
        {
            break;
        }
    } while (1);
    
	return 0;
}	

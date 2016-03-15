/*  Q. Recursive factorial without using any 
 *   other function than main
 *
 *  a. Read number n from user.
 *  b. Call main function from main for calculating factorial.
 *  c. Prompt for continue option.
 *
 *  Hint: Use static variables.
 *
 *  Prerequisites:
 *  --------------
 *  Recursive function concepts.
 *  Static storage class concepts.
 *
 *  Sample Execution
 *  ----------------
 *
 *  Enter n: 7
 *
 *  Factorial of 7: 5040
 *
 *  Continue (y/n):
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int n, returnValue;
    static char buf[16];
    
    char c;

        /* Do arg count check */
        if (argc < 2)
        {
            printf("Enter n: ");
            scanf("%d", &n);
        }
        else
        {
            /* get the int value from argv */
            n = atoi(argv[1]);
        }

        /* check for initial valid number */
        if (n <= 0)
        {
            returnValue = 1;
        }
        else
        {
            if (n == 1)
            {
                returnValue = 1;
            }
            else
            {
                sprintf(buf, "%d", n - 1);
                /* pt is the pointer to the value in buf */
                char *pt = buf;
                
                /* take the value stored in address of previous value (n-1) */
                char **pt2 = &pt - 1;
                
                /* Call main function from main for calculating factorial */
                returnValue = main(2, pt2) * n;
            }
            
        }
        printf("Factorial of %d: %d \n", n, returnValue);

        return returnValue;
    
}



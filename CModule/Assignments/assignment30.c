/*  
 * Q. Print bits of float & double. Check IEEE std.
 *
 *  a. Read the choice from user.
 *      -> float or double
 *  b. Read the fractional number from user.
 *  c. Print the bits of the entered number.
 *
 *  Concepts to apply
 *  -----------------
 *  IEEE standard
 *  floating point numbers
 *  Bitwise Operators.
 *
 *  Sample Execution
 *  ----------------
 *
 *  Enter the Choice:
 *      1. float
 *      2. double
 *
 *  Choice: 1
 *
 *  Enter the float value: 2.3
 *
 *  Sign    Mantissa                        Exponent
 *  ---------------------------------------------------------
 *   0     10000000   0 0 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1 0 0 1 1
 *
 *  Continue(y/n):
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "bitwise_lib.c"

int main()
{
    int choice;
    char option;
    float num;
    
    do
    {
        printf("Enter the Choice:\n \t1. float \t2. double\n");
    
        printf("Choice: ");
        scanf("%d", &choice);
        
        printf("Enter the float value: ");
        scanf("%f", &num);
        
        
        
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

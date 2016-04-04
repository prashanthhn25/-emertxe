/*
 *  Q. Read a float. 
 *     Print the demoted integer value without assigning to int
 *
 *
 */

#include <stdio.h>

int main()
{
    float fx;
    
    /* Swap int values */
    printf("Enter a float value: ");
    scanf("%f", &fx);
    
    printf("float actual value: %f \n", fx);
    printf("demoted int value: %.0f \n", fx);
    return 0;
}
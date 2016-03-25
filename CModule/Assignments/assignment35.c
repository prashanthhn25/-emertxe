/*  
 *  Q. Implement int itoa(int n, char *s)
 *
 *  a. Convert integer n into a string and store the string in s.
 *  b. Return the length of string from the function.
 *
 *  Note: Call the function as
 *      -> itoa(n, arr);
 *  After this function, arr should contain n as string.
 *
 *  Sample Execution
 *  ----------------
 *
 *  Enter the number: 100
 *
 *  You entered 100
 *
 *  Continue(y/n):
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 256
#define MAXVAL 20000000
#define MINVAL -20000000

#define isNum(x) (((x) >= '0') && ((x) <= '9'))? 1:0

int itoa(int n, char *s);

int main()
{
    char strBuf[MAXLEN];
    char option;
    int number =0;
    
    do
    {
        
        /* Enter the string and store */
        printf("Enter the number: ");
        /* check if only int values are considered */
        if(! scanf("%d", &number))
        {
            printf("Error: Invalid number\n");
            break;
        }
       
        /* Error Check for limit */
        if ((number < MINVAL) || (number > MAXVAL))
        {
            printf("Error: Invalid Number. Retry\n");
            return 1;
        }
        
        printf("length of the string: %d", itoa(number, strBuf));
        
        /* Call getword and print the output*/
        printf("\nYou entered %s\n", strBuf);
        
        /* Prompt for Continue option */
        printf("Continue (y/n): ");
        scanf("\n%c", &option);
        
        if ( option == 'y' )
        {
            *strBuf = '\0';
            getchar();
            continue;
        }
        else
        {
            break;
        }

    } while(1);
    return 0;
}


/*  a. Convert integer n into a string and store the string in s.
 *  b. Return the length of string from the function.
 */
int itoa(int n, char *s)
{
    int count = 0, temp, i;
    
    /* Check for buf size */
    if(s == NULL)
    {
        return 0;
    }
   
    /* if number is 0 then just give zero */
    if(n == 0)
    {
        *s = '0';
        return 1;
    }
    
    /* if num is negative int */
    if(n < 0)
    {
        n *= (-1); /* make the num positive for next evaluation */
        *s++ = '-'; /* store the '-' in s[0] and */
        count++; /* increment count for string length */
    }
    
    /* to acess s buf from s[n-1] where n is the number of digits and also to add null at nth place */
    for(temp = n; temp > 0; temp /= 10, s++);
    *s = '\0';
    
    /* fill the ASCII value of each digit by getting from lsb into s[n-1] --> s[0] place */
    for(temp = n; temp > 0; temp /= 10)
    {
        
        *--s = temp % 10 + '0';
        count++; /* increment the str len */
    }


    /* returns the string len */
    rewind(stdin);
    return count;
    
}
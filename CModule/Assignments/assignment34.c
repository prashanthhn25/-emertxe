/*  
 * Q. Implement i) int getword(char *word)
 *
 *  a. Create a function named getword.
 *  b. Function should read a string from user and 
 *      store them in the char address.
 *  c. Function should return the length of word.
 *
 *
 *  Sample Execution
 *  ----------------
 *
 *  Enter the Word: Hello Dennis Ritchie
 *
 *  You entered Hello
 *
 *  Continue(y/n):
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 256
#define MAXVAL 2000000000
#define MINVAL -2000000000

int getword(char *word);
int main()
{
    char word[MAXLEN];
    char option;
    
    do
    {
        /* Enter the string and store */
        printf("Enter the Word: ");
        fgets (word, MAXLEN, stdin);
        
        /* Call getword and print the output*/
        printf("You entered %d\n", getword(word));
        
        /* Prompt for Continue option */
        printf("Continue (y/n): ");
        scanf("\n%c", &option);
        
        if ( option == 'y' )
        {
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


/*The function will recieve a string and covert the
 *  number stored in the string into exact integer number.
 *  b. And return the number.
 */
int my_atoi(char *myInput)
{
    
    int s = 1, intVal = 0, i = 0;
    
    /* check for boundary condition */
    if ( '\0' == *myInput )
    {
        return 0;
    }
    
    /* check for negative value */
    if ( myInput[0] == '-')
    {
        /* If first digit is -, let s = 1 and start i from next */
        s = -1;
        i++;
    }
    else if ( myInput[0] == '+')
    {
        /* If first digit is +, let s = 1 and start i from next */
        s = 1;
        i++;
    }
    /* check for each char */
    for (; myInput[i] != '\0' ; i++)
    {
        /* check if it is a number */
        if (isNum(myInput[i]))
        {
            /* update intVal by adding new value with 10* previous val - the ASCII value of 0 */
            intVal = intVal*10 + myInput[i] - '0';
        }
        /* To check to break, as we only iterate till first word */
        if ((myInput[i] == ' ') || (myInput[i] == '\t') || (myInput[i] == '\n'))
        {
            break;
        }
    }

    /* return the int value multiplied by the sign s */
    return (s * intVal);
}

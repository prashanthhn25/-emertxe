/* Function Prototypes and Definitions to do string
 *  manipulations 
 *  
 *  functions in ntype library.
 *
 *      -> void swap_generic(void * aptr, void * bptr, int size);
 *      -> int my_atoi(char *myInput);
 *      -> int bin2dec(char binary[], int bits);
 *      -> void print_Menu(char sptr[][MAX_COL], int rows);
 */

/* Swaps int, String, float, cha, double, array */
void swap_generic(void * aptr, void * bptr, int size)
{
    int i;
    char temp;
    
    for ( i = 0; i < size; i++ )
    {
        temp = * (char *) aptr;
        * (char *) aptr++ = * (char *) bptr;
        * (char *) bptr++ = temp;
    }
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
        /* If it is not starting with a num */
        if (!isNum(myInput[i]))
        {
            break;
        }
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
    
    /* Check for out of range */
    
    if (((s * intVal) < MINVAL) || ((s * intVal) > MAXVAL))
    {
        printf("Error: Out of range\n");
        exit(1);
    }
    
    /* return the int value multiplied by the sign s */
    return (s * intVal);
}

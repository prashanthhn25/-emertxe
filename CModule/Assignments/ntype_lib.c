/* Function Prototypes and Definitions to do number
 *  manipulations 
 *  
 *  functions in ntype library.
 *
 *      -> int my_ispositive(int var);
 *      -> int my_iszero(int var);
 *      -> int bin2dec(char binary[], int bits);
 *      -> void print_Menu(char sptr[][MAX_COL], int rows);
 */

#define MAX_COL 10000

/*
 * To check if the passed value is positive number or not.
 * If true returns 1 else 0
 */
int my_ispositive(int var)
{
    if( (var*-1) < 0 )
    {
        return 1;
    }
    return 0;
}

/*
 * To check if the passed value is zero or not.
 * If true returns 1 else 0
 */
int my_iszero(int var)
{
    if( var == 0 )
    {
        return 1;
    }
    return 0;
}

/* To convert from binary to decimal
 */
int bin2dec(char binary[], int bits)
{
    int i, decimal = 0;
    int bitval = 0, mask = 1;
    
    for (i = 0; i < bits; i++)
    {
        if ((*(binary + bits - i - 1)) == '1')
        {
            bitval = 1;
        }
        else
        {
            bitval = 0;
        }
    
        decimal += (bitval * (mask<< i) );
    }
    return decimal;
}

/* To print Menu */
void print_Menu(char sptr[][MAX_COL], int rows)
{
    int i;
    
    for (i = 0; i < rows; i++)
    {
        printf("%d %s \n", i+1, *(sptr+i));
    }
}

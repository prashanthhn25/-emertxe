/*
 *  Q. Implement calc mean for all types
 *
 *  a. Enter the number of elements to store in the array 
 *   through the command line
 *  b. Read the type of data to store
 *  c. Enter the elements into the array.
 *  d. Pass them to calc mean function
 *  e. Should return mean value.
 *
 *  Concepts to apply:
 *  ------------------
 *
 *  Void pointers
 *  Function pointers
 *
 *  Sample Execution:
 *  -----------------
 *
 *  ./a.out 4
 *
 *  Enter the elements:	10 20 30 40
 *
 *  The mean value: 25.00
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 150
#define MAXVAL 20000000
#define MINVAL -20000000

union Storage
{
    float floatStore[MAXLEN];
    int intStore[MAXLEN];
    double doubleStore[MAXLEN];
};

float calc_mean(void *aptr, int no_of_elements, int size_l);

int main(int argc, char **argv)
{
    int len;
    char *types[6] = {"int", "Float", "Double"};
    int choice, i;
    union Storage store;
    
    /* Do arg count check */
    if (argc != 2)
    {
        printf("Invalid entry: ./assignment45 <length_of_array>\n");
        exit(1);
    }
    else
    {
        len = atoi(argv[1]);
        /*  Enter the number of elements to store in the array
         *   through the command line*/
        if ((len <= 0) || (len > MAXLEN))
        {
            printf("Error: Invalid number of elements. Retry\n");
            return 1;
        }
    }
    
    /* Read the type of data to store */
    printf("1. INT \n2. Float \n3. Double \n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    printf("Enter the elements:	\n");
    switch (choice) {
        case 1:
            /*  Enter the elements into the array */
            for (i = 0; i < len; i++)
            {
                scanf("%d", &store.intStore[i]);
                
                /* Error Check for limit */
                if (((store.intStore[i]) < MINVAL) || ((store.intStore[i]) > MAXVAL))
                {
                    printf("Error: Element value is Out of range. Retry\n");
                    return 1;
                }
            }
            
            /* Pass them to calc mean function */
            printf("The mean value: %f", calc_mean(store.intStore, len, sizeof(int)));
            break;
            
        default:
            printf("Invalid option\n");
            break;
    }
    return 0;
}

float calc_mean(void *aptr, int no_of_elements, int size_l)
{
    return -1;
}
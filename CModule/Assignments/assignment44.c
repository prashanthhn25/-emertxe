/*
 *  Q. Implement binary search for int, double, string.
 *
 *  a. Enter the length of array from command line.
 *  b. Read the type of data to search
 *  c. Initialise the array of mentioned type with variables
 *      read from user.
 *  d. Read the key element to search.
 *  e. Sort the element in ascending order.
 *  f. Return the position of element in the array.
 *
 *  Concepts to apply:
 *  ------------------
 *  Void pointers
 *  Function pointers
 *
 *  Sample Execution:
 *  -----------------
 *
 *  ./a.out 4
 *
 *  1. INT
 *  2. Char
 *  3. Float
 *  4. Double
 *  5. String
 *
 *  Choice: 1
 *
 *  Enter 4 elements of type int
 *
 *  1. 1
 *  2. 2
 *  3. 7
 *  4. 4
 *
 *  After sorting: 1 2 4 7
 *
 *  Enter the key element to search: 1
 *
 *  Element 1 is at position 0 of array.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stype_lib.c"

#define MAXLEN 150
#define MAXVAL 20000000
#define MINVAL -20000000

int compare_int(void *a, void *b);
int compare_char(void *a, void *b);
int compare_float(void *a, void *b);
int compare_double(void *a, void *b);

void generic_sort(void* aptr, int no_of_elements, int (*compare_fp)(void *, void *), int size_len);

int generic_binarySearch(void *val, void *aptr, int no_of_element, int (*compare_fp)(void *, void *), int size_length);

int char_binarySearch(char val, char *aptr, int no_of_element);

union Storage
{
    float floatStore[MAXLEN];
    int intStore[MAXLEN];
    char charStore[MAXLEN];
    double doubleStore[MAXLEN];
    
    int searchIntVal;
    float searchFloatVal;
    char searchCharVal;
    double searchDoubleVal;
    
};

int main(int argc, char **argv)
{
    int len;
    char *types[6] = {"int", "Char", "Float", "Double"};
    int choice, i;
    
    union Storage store;
    
    float floatStore[MAXLEN];
    int intStore[MAXLEN];
    char charStore[MAXLEN];
    double doubleStore[MAXLEN];
    
    int searchIntVal;
    float searchFloatVal;
    char searchCharVal;
    double searchDoubleVal;
    
    /* Do arg count check */
    if (argc != 2)
    {
        printf("Invalid entry: ./assignment44 <length_of_array>");
        exit(1);
    }
    else
    {
        len = atoi(argv[1]);
        /*  Enter the length of array from command line */
        if ((len <= 0) || (len > MAXLEN))
        {
            printf("Error: Invalid length of array. Retry\n");
            return 1;
        }
    }
    
    /* Read the type of data to search */
    printf("1. INT \n2. Char \n3. Float \n4. Double \n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    printf("Enter %d elements of type %s\n", len, types[choice-1] );
    
    switch (choice) {
        case 1:
            /* Initialise the array of mentioned type with variables
             *      read from user.
             */
            for (i = 0; i < len; i++)
            {
                printf("%d.", i);
                scanf("%d", &store.intStore[i]);
                
                /* Error Check for limit */
                if (((store.intStore[i]) < MINVAL) || ((store.intStore[i]) > MAXVAL))
                {
                    printf("Error: Element value is Out of range. Retry\n");
                    return 1;
                }
            }
            
            /* Sort the element in ascending order and print */
            printf("After sorting: ");
            generic_sort(&store.intStore, len, compare_int, sizeof(int));
            for (i = 0; i < len; i++)
            {
                printf("%d ", store.intStore[i]);
            }
            
            /* Read the key element to search */
            printf("\nEnter the key element to search: ");
            scanf("%d", &store.searchIntVal);
            
            /* Error Check for limit */
            if ((store.searchIntVal < MINVAL) || (store.searchIntVal > MAXVAL))
            {
                printf("Error: Search Element value is Out of range. Retry\n");
                return 1;
            }
            
            /* To search for the key and Return the position in the sorted array. */
            if ( (generic_binarySearch(&store.searchIntVal, &store.intStore, len, compare_int, sizeof(int))) == -1)
            {
                printf("Element not found\n");
            }
            else
            {
                printf("Element %d is at position %d of sorted array. \n", store.searchIntVal, (generic_binarySearch(&store.searchIntVal, &store.intStore, len, compare_int, sizeof(int))) );
            }
            
            break;
        case 2:
            /* Initialise the array of mentioned type with variables
             *      read from user.
             */
            for (i = 0; i < len; i++)
            {
                printf("%d.", i);
                /* check for only printable char */
                scanf("\n%c", &store.charStore[i]);
                if (((store.charStore[i]) < ' ') || ((store.charStore[i]) > '~'))
                {
                    /* Error Check for char */
                    printf("Error: Element is not a char. Retry\n");
                    fflush(stdin);
                    fseek(stdin, 0L, SEEK_SET);
                    return 1;
                }
            }
            
            /* Sort the element in ascending order and print */
            printf("After sorting: ");
            generic_sort(store.charStore, len, compare_char, sizeof(char));
            for (i = 0; i < len; i++)
            {
                printf("%c ", store.charStore[i]);
            }
            
            /* Read the key element to search */
            printf("\nEnter the key element to search: ");
            scanf("\n%c", &store.searchCharVal);
            printf("%c", store.searchCharVal);
            
            if ((store.searchCharVal < ' ') || (store.searchCharVal > '~'))
            {
                /* Error Check for char */
                printf("Error: Element is not a char. Retry\n");
                fflush(stdin);
                fseek(stdin, 0L, SEEK_SET);
                return 1;
            }
            fflush(stdin);
            rewind(stdin);
            fseek(stdin, 0L, SEEK_SET);
            
            /* To search for the key and Return the position in the sorted array. */
            
            if ((char_binarySearch(store.searchCharVal, store.charStore, len)) == -1)
            {
                printf("Element not found\n");
            }
            else
            {
                printf("Element %c is at position %d of sorted array. \n", store.searchCharVal, (char_binarySearch(store.searchCharVal, store.charStore, len)) );
            }
            
            break;
        case 3:
            /* Initialise the array of mentioned type with variables
             *      read from user.
             */
            for (i = 0; i < len; i++)
            {
                printf("%d.", i);
                scanf("%f", &store.floatStore[i]);
                
                /* Error Check for limit */
                if (((store.floatStore[i]) < MINVAL) || ((store.floatStore[i]) > MAXVAL))
                {
                    printf("Error: Element value is Out of range. Retry\n");
                    return 1;
                }
                
            }
            
            /* Sort the element in ascending order and print */
            printf("After sorting: ");
            generic_sort(store.floatStore, len, compare_float, sizeof(float));
            for (i = 0; i < len; i++)
            {
                printf("%f ", store.floatStore[i]);
            }
            
            /* Read the key element to search */
            printf("\nEnter the key element to search: ");
            scanf("%f", &store.searchFloatVal);
            
            /* Error Check for limit */
            if ((store.searchFloatVal < MINVAL) || (store.searchFloatVal > MAXVAL))
            {
                printf("Error: Search Element value is Out of range. Retry\n");
                return 1;
            }
            
            /* To search for the key and Return the position in the sorted array. */
            if ( (generic_binarySearch(&store.searchFloatVal, &store.floatStore, len, compare_float, sizeof(float))) == -1)
            {
                printf("Element not found\n");
            }
            else
            {
                printf("Element %f is at position %d of sorted array. \n", store.searchFloatVal, (generic_binarySearch(&store.searchFloatVal, &store.floatStore, len, compare_float, sizeof(float))) );
            }
            
            break;
        case 4:
            /* Initialise the array of mentioned type with variables
             *      read from user.
             */
            for (i = 0; i < len; i++)
            {
                printf("%d.", i);
                scanf("%lf", &store.doubleStore[i]);
                
                /* Error Check for limit */
                if (((store.doubleStore[i]) < MINVAL) || ((store.doubleStore[i]) > MAXVAL))
                {
                    printf("Error: Element value is Out of range. Retry\n");
                    return 1;
                }
            }
            
            /* Sort the element in ascending order and print */
            printf("After sorting: ");
            generic_sort(store.doubleStore, len, compare_double, sizeof(double));
            for (i = 0; i < len; i++)
            {
                printf("%lf ", store.doubleStore[i]);
            }
            
            /* Read the key element to search */
            printf("\nEnter the key element to search: ");
            scanf("%lf", &store.searchDoubleVal);
            
            /* Error Check for limit */
            if ((store.searchDoubleVal < MINVAL) || (store.searchDoubleVal > MAXVAL))
            {
                printf("Error: Search Element value is Out of range. Retry\n");
                return 1;
            }
            
            /* To search for the key and Return the position in the sorted array. */
            if ( (generic_binarySearch(&store.searchDoubleVal, &store.doubleStore, len, compare_double, sizeof(double))) == -1)
            {
                printf("Element not found\n");
            }
            else
            {
                printf("Element %lf is at position %d of sorted array. \n", store.searchDoubleVal, (generic_binarySearch(&store.searchDoubleVal, &store.doubleStore, len, compare_double, sizeof(double))) );
            }
            
            break;
            
        default:
            break;
    }
    return 0;
}

/* Compare ints */
int compare_int(void *a, void *b)
{
    if (*(int *)b < *(int *)a) return 5;
    if (*(int *)b > *(int *)a) return -5;
    return 0;
}

/* Compare char */
int compare_char(void *a, void *b)
{
    const char *c = (char *)a;
    const char *d = (char *)b;
    return strcmp(c, d);
}

/* Compare float */
int compare_float(void *a, void *b)
{
    if (*(float *)b < *(float *)a) return 5;
    if (*(float *)b > *(float *)a) return -5;
    return 0;
}

/* Compare double */
int compare_double(void *a, void *b)
{
    if (*(double *)b < *(double *)a) return 5;
    if (*(double *)b > *(double *)a) return -5;
    return 0;
}

/* Generic Bubble sort of elements in assending order */
void generic_sort(void* aptr, int no_of_elements, int (*compare_fp)(void *, void *), int size_len)
{
    int i, j;
    
    for (i = 0; i < no_of_elements; i++)
    {
        for (j = 0; j < no_of_elements - i - 1; j++)
        {
            if ( compare_fp((aptr + j * size_len), (aptr + (j + 1) * (size_len))) > 0) {
                swap_generic((aptr + j * size_len), (aptr + (j + 1) * (size_len)), size_len );
            }
        }
    }
}


/* Generic Binary Search */
int generic_binarySearch(void *val, void *aptr, int no_of_element, int (*compare_fp)(void *, void *), int size_length)
{
    int low, high, mid;
    char temptest1 = 'a', temptest2 = 'a';
    
    low = 0;
    high = no_of_element -1;
    while(low < high)
    {
        mid = (low + high) / 2;
        
        if (compare_fp(val, (aptr + (mid) * (size_length))) <= 0)
        {
            high = mid;
        }
        else
        {
            low = mid+1;
        }
        
        printf("comapre:%c and %c--> %d \n", *(char *)val, *(char *)(aptr + (mid) * (size_length)), compare_fp(val, (aptr + (mid) * (size_length))));
        printf("try: %d\n", compare_char(&temptest1, &temptest2));
    }
    
    return (compare_fp(val, (aptr + (low) * (size_length))) == 0)? low: -1;
}

/* Binary Search for char */
int char_binarySearch(char val, char *aptr, int no_of_element)
{
    int low, high, mid;
    char tempVal, result;
    
    low = 0;
    high = no_of_element - 1;
    
    while(low <= high)
    {
        mid = (low + high) / 2;
        tempVal = *(aptr + mid);
        printf("mid: %d--> %d \n", mid, (strcmp(&val, &tempVal)) );
        
        if ((strcmp(&val, &tempVal)) < 0)
        {
            high = mid - 1;
        }
        else
        {
            low = mid+1;
        }
        
    }
    printf("2low = %d: 2high = %d:\n", low,high);
    /* yet to do */
    result = *(aptr + low);
    //if ((strcmp(&val, aptr[low])) == 0)
    printf("val: %d,result: %d-->%d\n", val, result, strcmp(&val, &result));
    return -1;
}


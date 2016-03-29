/*  
 *  Q. Read n & n persons names of (i) maxlen 32 and avglen a.
 *  Sort and print the names.
 *
 *  a. Enter
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXNAMES 256
#define MAXLEN 32

void sortPersonName(char * array[], int personCount);
void swap_generic(void * aptr, void * bptr, int size);

int main()
{
    int nPerson, i, j;
    
    char **storenPerson;
    
    printf("Enter the count of person : ");
    scanf("%d", &nPerson);
    
    if ((nPerson < 0) || (nPerson > MAXNAMES))
    {
        printf("Error: Size is Out of range. Retry\n");
        return 1;
    }
    
    /* Memory to store n person Names */
    char ** const sptr = (char**)malloc(sizeof(char*) * nPerson);
    
    if (NULL == sptr) {
        printf("Error: Malloc allocation Failure \n");
        return 1;
    }
    
    /* Memory to save each names of maxlen 32*/
    for (i = 0; i < nPerson; i++)
    {
        sptr[i] = (char*)malloc(sizeof(char) * (MAXLEN+1));
        
        if (NULL == sptr[i]) {
            printf("Error: Malloc allocation Failure for Person [%d] \n", i);
            return 1;
        }

    }
    
    storenPerson = sptr;
    
    for (i = 0; i < nPerson; i++)
    {
        printf("[person %d] -> ", i);
        scanf("%s", storenPerson[i]);
        
        /* check for names with maxlen 32 */
        if (strlen(storenPerson[i]) > MAXLEN) {
            printf("Error: name length of persdon %d is > 32. Retry\n", i);
            return 1;
        }
    }
    
    
    /* Printing the person elements in sorted order. */
    printf("After sorting: ");
    sortPersonName(storenPerson, nPerson);
   
    for (i = 0; i < nPerson; i++)
    {
        printf("%s ", storenPerson[i]);
    }
    
    free(sptr);
    storenPerson = NULL;
    
    printf("\n");
    return 0;
}


/* Sorting floating numbers - Bubble sort using generic swap */
void sortPersonName(char * array[], int personCount)
{
    int i, j;
    
    for (i = 0; i < personCount; i++)
    {
        for (j = 0; j < personCount - i - 1; j++)
        {
            if ((strcmp(*(array+j), *(array+j+1)) > 0 ))
            {
                swap_generic(*(array+j), *(array+j+1), MAXLEN);
            }
        }
    }
}

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

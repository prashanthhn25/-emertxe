/*  
 * Q. Take 8 consecutive bytes in memory. 
 *  Provide a menu to manipulate or display the value of 
 *  variable of type t (input) & in-dexed at i (i/p)
 *
 *  a. Allocate 8 consecutive bytes in memory.
 *  b. Provide a display menu
 *      -> 1. Add element
 *      -> 2. Remove element
 *      -> 3. Display element
 *      -> 4. Exit from the program
 *  c. It should allow to add elements of different data types.
 *
 *
 *  Sample Execution
 *  ----------------
 *
 *  1. Add element
 *  2. Remove element
 *  3. Display element
 *  4. Exit from the program
 *
 *  Choice ---> 1
 *
 *	Enter the type you have to insert:
 *  1. int
 *  2. char
 *  3. float
 *  4. double
 *  Choice ---> 2
 *
 *  Enter the char : k
 *
 *  1. Add element
 *  2. Remove element
 *  3. Display element
 *  4. Exit from the program
 *
 *  Choice ---> 3
 *  -------------------------
 *  0 -> k
 *  -------------------------
 *
 *  1. Add element
 *  2. Remove element
 *  3. Display element
 *  4. Exit from the program
 *
 *  Choice ---> 1
 *
 *      Enter the type you have to insert:
 *  1. int
 *  2. char
 *  3. float
 *  4. double
 *  Choice ---> 1
 *
 *  Enter the int : 10
 *
 *  1. Add element
 *  2. Remove element
 *  3. Display element
 *  4. Exit from the program
 *
 *  Choice ---> 3
 *  ------------------------
 *  0 -> 1   (char)
 *  1 -> 10  (int)
 *  ------------------------
 *
 *  1. Add element
 *  2. Remove element
 *  3. Display element
 *  4. Exit from the program
 *
 *  Choice --->
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ntype_lib.c"


#define ARR_ROW 4
#define ARR_COL 10000

void add_Element(char (* typeOfData)[], void *ptr, void *ptr2, int size);

int main()
{
    int choice, typechoice;
    
    int num;
    //int checkCopy=0;
    void * pointerTodataTypeValue;
    char character;
    float fnum;
    double dnum;
    
    /* Allocate 8 consecutive bytes in memory */
    char * const ptr = (char *) malloc(8 * sizeof(char));
    
    if (NULL == ptr)
    {
        printf("Error: Memory allocation failed\n");
        return 1;
    }
    pointerTodataTypeValue = (char *)ptr;
    
    /* Menu */
    char mainMenu[ARR_ROW][ARR_COL] = { "Add element", "Remove element", "Display element", "Exit from the program" };
    
    char typeMenu[ARR_ROW][ARR_COL] = { "int", "char", "float", "double" };
    
    print_Menu(mainMenu, ARR_ROW);
    printf("Choice ---> ");
    scanf("%d", &choice);
    
    switch (choice)
    {
        case 1:
            printf("\tEnter the type you have to insert:\n");
            print_Menu(typeMenu, ARR_ROW);
            printf("Choice ---> ");
            scanf("%d", &typechoice);
            
            switch (typechoice) {
                case 1:
                    printf("Enter the %s : \n", *(typeMenu+typechoice-1));
                    scanf("%d", &num);
                    //add_Element((typeMenu+typechoice-1), &num, &checkCopy, sizeof(num));
                     //printf("in checkCopy --> %d \n",  checkCopy);
                    add_Element((typeMenu+typechoice-1), &num, pointerTodataTypeValue, sizeof(num));
                    printf("in checkCopy --> %d \n",  *((int *)pointerTodataTypeValue));
                    printf("size of content of pointerTodataTypeValue = %lu\n", sizeof(*((int *)pointerTodataTypeValue)));
                    break;
                    
                case 2:
                    printf("Enter the %s : \n", *(typeMenu+typechoice-1));
                    scanf("\n%c", &character);
                    add_Element((typeMenu+typechoice-1), &character, pointerTodataTypeValue, sizeof(character));
                    printf("in checkCopy --> %c \n",  *((char *)pointerTodataTypeValue));
                    printf("size of content of pointerTodataTypeValue = %lu\n", sizeof(*((char *)pointerTodataTypeValue)));
                    break;
                    
                case 3 ... 4:
                    printf("Enter the %s : \n", *(typeMenu+typechoice-1));
                    
            
                    break;
                    
                default:
                    printf("Invalid option\n");
                    break;
            }
            break;
            
        default:
            break;
    }
    
    return 0;
}

void add_Element(char (* typeOfData)[], void *ptr, void *ptr2, int size)
{
    int i;
    char *a = ptr;
    char *b = ptr2;
    
    printf("Enter the %s : \n", *(typeOfData));
    for (i = 0; i < size; i++)
    {
        b[i] = a[i];
    }
   
}

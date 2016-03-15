/*
 *  Q. Given a number between 1-365 (incl), find which day is it
 *
 *
 */

#include <stdio.h>

int main()
{
    
    int dayNumber;
    
    /* days */
    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    
    
    const unsigned short int __mon_yday[2][13] =
    {
        /* Normal years.  */
        { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
        /* Leap years.  */
        { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
    };
    
    /* Enter the number */
    printf("Enter the number between 1-365 (incl): ");
    scanf("%d", &dayNumber);
    
    dayNumber%=7;
    printf("Day is : %s\n", *(days+dayNumber));
    
    return 0;
}	

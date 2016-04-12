/*
 *  Q. Read a float. 
 *     Print the demoted integer value without assigning to int
 *
 *
 */

 union _FLOATNUM
 {
	float FLOATNUM;
	
	struct _FLOATRANGE
	{
		unsigned MANTESSA :23;
		unsigned EXPONENT :8;
		unsigned char SIGN :1;
		
		 
	} floatRange;
	
 } floatNum;
#include <stdio.h>

int main()
{
    float fx;
    
    /* Swap int values */
    printf("Enter a float value: ");
    scanf("%f", &fx);
    
	floatNum.FLOATNUM = fx;
	
    //printf("float actual value: %d \n", floatNum.floatRange.EXPONENT);
    printf("demoted int value: %.f \n", fx);
    return 0;
}
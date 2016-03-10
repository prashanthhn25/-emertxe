//to find the max of two numbers

#include<stdio.h>
int main()
{
	int num1=10;
	int num2=20;
	
	if (num1 > num2)
	{
		printf("%d is greater\n",num1);
	}
	else if (num2 > num1)
	{
		printf("%d is greater\n",num2);
	}

	else
	{
		printf("both are equal\n");
	}
	return 0;
}

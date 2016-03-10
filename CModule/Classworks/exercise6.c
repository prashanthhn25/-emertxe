#include<stdio.h>
int main()
{

	int option;
	printf("Enter the value:\n ");
	scanf("%d",&option);

	switch (option)
	{
		default:
			printf("Try again\n");
			//upon uncommenting the below line, default will be excuted only if default case and then falls through
			//break; 
		case 10:
		case 20:
			printf("%d is pressed\n",option);	
			break;
	}
	return 0;
}
	


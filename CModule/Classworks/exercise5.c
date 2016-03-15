// to check whether a character is in upper case/lower case/digit

#include<stdio.h>

int main()
{
	char ch;
	
	printf("Enter a character:\n ");
	ch=getchar();
	
	
	if (ch >= 'A' && ch <= 'Z')
	{
		printf("%c is in upper case\n ", ch);
	}
	else if (ch >= 'a' && ch <= 'z')
	{
		printf("%c is in lower case\n ", ch);
	}
	else if (ch >= '0' && ch <= '9')
	{
		printf("%c is digit\n ", ch);
	}
	else 
	{
		printf("Non of the above are alpha nummeric\n");
	}

}

#include "stack.h"

int expressionEvaluation(int valueA, int valueB, char sym )
{
	switch(sym)
	{
		case '+':
			return ((valueA - '0') + (valueB - '0'));
			break;
		case '-':
			return ((valueA - '0') - (valueB - '0'));
			break;
		case '*':
			return ((valueA - '0') * (valueB - '0'));
			break;
		case '/':
			return ((valueA - '0') / (valueB - '0'));
			break;
		case '%':
			return ((valueA - '0') % (valueB - '0'));
			break;
		default:
			break;
	}	
}		



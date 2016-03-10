#!/bin/bash
<<COMMENT
To check if the input is real number or not [1.1,-1.1,0,1]
Usuage ./isNumber.sh -1.21
COMMENT

isRealNumber()
{
if ! echo $1 | grep -Eq ^\-?[0-9]?+\.?[0-9]+$
then
	echo "Error: $1 is Invalid Real Number"
	echo "Usage: enter valid real numbers"
	exit 1
fi
}

<<COMMENT
To check if the input is Integer or not [-2,-1,0,1,2,3,4..]
Usuage ./isNumber.sh -1 
COMMENT
isInteger()
{
if ! echo $1 | grep -Eq ^\-?[0-9]?+$
then
	echo "Error: $1 is Invalid Integer Number"
	echo "Usage: enter valid Integer numbers"
	exit 1
fi
} 

<<COMMENT
To check if the input is Integer or not [0,1,2,3,4..]
Usuage ./isNumber.sh 0 
COMMENT
isWholeNumber()
{
if ! echo $1 | grep -Eq ^\[0-9]?+$
then
	echo "Error: $1 is Invalid Whole Number"
	echo "Usage: enter valid Whole numbers"
	exit 1
fi
} 

<<COMMENT
To check if the input is Integer or not [1,2,3,4..]
Usuage ./isNumber.sh 1 
COMMENT
isNaturalNumber()
{
if ! echo $1 | grep -Eq ^\[1-9]?+$
then
	echo "Error: $1 is Invalid Natural Number"
	echo "Usage: enter valid Natural numbers"
	exit 1
fi
} 

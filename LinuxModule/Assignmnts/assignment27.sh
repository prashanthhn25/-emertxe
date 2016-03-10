#!/bin/bash
<<COMMENT
To convert string lower to upper and upper to lower
COMMENT

#------------------------------------------

#check for argument count
if [ $# -ne 1 ]
then
	echo "Error: No string is provided"
	echo "Usage: please provide the string:
		eg: ./assignment27.sh <string>"
	exit 1
fi

echo "Enter the options: 
1-> to convert lower to upper 
2-> to convert upper to lower"

read option

case $option in
	1) 
	   echo $1 | tr [:lower:] [:upper:]	
	   ;;
	2)
	   echo $1 | tr [:upper:] [:lower:]
	   ;;
	*)
	   echo "Error: Invalid option"
	   ;;
esac



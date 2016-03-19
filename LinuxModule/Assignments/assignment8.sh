#!/bin/bash
<<COMMENT
Write a script to print the given number in reverse order
i/p: 1234 o/p: 4321
COMMENT

#check for argument count
if [ $# -lt 1 ]
then
	echo "Error: Invalid argument count"
	echo "Usuage: ./assignment8.sh 1234"
	exit 1
fi


#check if the argument is digit

#regular epression starts and ends with digits
re='^[0-9]+$'
if ! [[ $1 =~ $re ]]
then
    echo "error: Not a number" >&2
    exit 1
fi

echo $1 | rev
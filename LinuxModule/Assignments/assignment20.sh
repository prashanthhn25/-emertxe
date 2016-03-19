#!/bin/bash
<<COMMENT
To print contents of file from given number to next given number of lines.
Usage: ./assignment20.sh 5 5 myfile
Output: prints contains of 'myfile' file from line 5 to next 5 line of the file 
COMMENT


# isNumber file is included as it has isNaturalNumber function
. ./isNumber.sh 

#----------------------------------------------

#check for argument count
if [ $# -ne 3 ]
then
	echo "Error: Invalid argument count"
	echo "Usuage: ./assignment20.sh 5 5 myfile" 
	exit 1
fi

#check for natural numbers for the line numbers
isNaturalNumber $1
isNaturalNumber $2

file=$3
#check if the file is present or not in the current directory
if [ ! -f $file ]
then
	echo "Error: No such file exists"
	exit 1
fi

#---------------------------------------------------------

#to print contents of file($3) from given number ($1) to next given number of lines ($2)
var1=$1
var2=$(($1+$2))
sed -n "${var1},${var2}"p $file


#!/bin/bash
<<COMMENT
Recurssive function to print each argument passed to the function, regardless of how many arguments are passed.
COMMENT

#check for argument count
if [ $# -lt 1 ]
then
	echo "Error: Invalid argument count"
	echo "Usuage: ./assignment32.sh arg1 arg2 arg3" 
	exit 1
fi

arrayOfArg=($@)

printArguments()
{
	#if there is only one value print and return
	if [ $# -eq 1 ] 
	then
		echo $1
		return
	fi
	
	#Get the argument list into temp array and print first arg
	temparray=($@)
	echo $1

	#set a recurArray  to empty, else it will not be cleared on recurrsive call
	recurArray=()

	#get the shifted values to print the remaining arg excluding first
	for (( i=0; i<${#temparray[@]}; i++ ))
	do
		recurArray+=(${temparray[$(($i+1))]})
	done
	
	#recursively call for teh remaining arguments 
	printArguments ${recurArray[@]}
}

printArguments ${arrayOfArg[@]}

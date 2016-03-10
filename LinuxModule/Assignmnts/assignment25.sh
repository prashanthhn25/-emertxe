#!/bin/bash
<<COMMENT
Takes any number of directories as command-line arguments and then lists the contents of each of these directories
COMMENT

#----------------------------------------------

#check for minimum 1 argument to be entered
if [ $# -lt 1 ]
then
	echo "Error: Invalid input. Enter a minimum of 1 arg (directory)]"
	echo "eg: ./ assignment25.sh <mydirectory1> <mydirectory2>" 
	exit 1
fi

myDirectoryArray=($@)

#check for valid directory
for (( i=0; i < ${#myDirectoryArray[@]}; i++ ))
do
	if [ ! -d ${myDirectoryArray[$i]} ]
	then
		echo "${myDirectoryArray[$i]} is not a directory"
	else
		#if valid, change to that directory and list 
		echo "${myDirectoryArray[$i]}: "
		cd ${myDirectoryArray[$i]};ls	
	fi
done 



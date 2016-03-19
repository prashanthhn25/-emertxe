#!/bin/bash
<<COMMENT
To find all the swp files from given directory
COMMENT

#check for argument count
if [ $# -ne 1 ]
then
	echo "Error: Invalid argument count"
	echo "Usuage: ./assignment23.sh <myDirectory>" 
	exit 1
fi

path=$1
#check if the path is directory or not 
if [ ! -d $path ]
then
	echo "Error: No such directory exists"
	exit 1
fi

find $path -name ".*.swp"

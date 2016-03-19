#!/bin/bash
<<COMMENT
output each directory name prior to listing the files within that directory
COMMENT

#check for minimum 1 integer to be entered
if [ $# -lt 1 ]
then
	echo "ERROR: Invalid input. enter the directory [minimum 1arg]"
	echo "eg: ./ assignment28.sh ." 
	exit 1
fi

path=$1
#check if the given path is directory path or not
if [ ! -d $path ]
then
	echo "Error: No such directory exists"
	exit 1
fi

#recurssively list within that directory along with the directory name
ls -R $1



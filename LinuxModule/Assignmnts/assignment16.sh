#!/bin/bash
<<COMMENT
To rename a file/directory and replace by lower/uper case letters
	eg : directory --> DIRECTORY
	   : File --> file
COMMENT

#------------------------------------------

#check for argument count
if [ $# -ne 1 ]
then
	echo "Error: No file/directory name is given"
	echo "Usage: Please provide the file/directory path:
		eg: ./assignment16.sh <path of file/directory>"
	exit 1
fi

path=$1

#check if the given file/directory path exists or not
if [ ! -e $path ]
then
	echo "Error: No such file/directory exists"
	exit 1
fi

#----------------------------------------

#if the given path is directory
if [ -d $path ]
then
	#get the capital lettered name
	newName=`echo $path | tr [:lower:] [:upper:]`

	#check if newName file/directory path exists 
	if [ -e $newName ]
	then
		echo "Error: $newName file/directory  exists. Will not rename"
		exit 1
	else
		mv "$path" "$newName"		
	fi
#if the given path is file
elif [ -f $path ]
then
	#get the small lettered name
	newName=`echo $path | tr [:upper:] [:lower:]`

	#check if newName file/directory path exists 
	if [ -e $newName ]
	then
		echo "Error: $newName file/directory exists. Will not rename"
		exit 1
	else
		mv "$path" "$newName"		
	fi
fi


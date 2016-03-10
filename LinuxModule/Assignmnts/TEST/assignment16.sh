#!/bin/bash
<<COMMENT
To rename a file/directory and replace by lower/uper case letters
COMMENT

#------------------------------------------

#check for argument count
if [[ $# -ne 1 ]]
then
	echo "Error: no file/directory name is given"
	echo "Usage: please provide the file/directory path:
		eg: ./assignment16.sh <path of file/directory>"
	exit 1
fi

path="${1}"

#check if the given file/directory path exists or not
if [ ! -e $path ]
then
	echo "Error: No such file/directory exists"
	exit 1
fi

firstLetter=${path:0:1} 

if [[ $firstLetter != [[:upper:]] ]] && [[ $firstLetter != [[:lower:]] ]]
then
	echo "Error: The file/directory doesn't start with alphabet"
	exit 1
fi

#----------------------------------------
if [ -d $path ]
then
	if [[ $firstLetter = [[:upper:]] ]]
	then
		echo "Already in correct format"
		exit 0
	elif  [[ $firstLetter = [[:lower:]] ]]
	then 
		caps=`echo $firstLetter | tr [:lower:] [:upper:]`
		newName=${caps}${path:1}

		#check if the given file/directory path starts with alphabets or not
		if [ -f $newName -o -d $newName ]
		then
			echo "Error: $newName file/directory currently exists."
			exit 1
		else
			mv "$path" "$newName"		
		fi
	fi
elif [ -f $path ]
then
	if [[ $firstLetter = [[:lower:]] ]]
	then
		echo "Already in correct format"
		exit 0
	elif  [[ $firstLetter = [[:upper:]] ]]
	then
		small=`echo $firstLetter | tr [:upper:] [:lower:]`
		newName=${small}${path:1}

		#check if the given file/directory path starts with alphabets or not
		if [ -f $newName -o -d $newName ]
		then
			echo "Error: $newName file/directory currently exists."
			exit 1
		else
			mv "$path" "$newName"		
		fi
	fi 
fi


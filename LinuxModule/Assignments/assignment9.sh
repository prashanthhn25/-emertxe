#!/bin/bash
<<COMMENT
Write a script to delete an empty line from a file. Take file name from user
COMMENT

#check for argument count
if [ $# -lt 1 ]
then
	echo "Error: Invalid argument count"
	echo "Usuage: ./assignment9.sh filename"
	exit 1
fi

file=$1
#check for file
if ! [ -e $file ]
then
    echo "Error: No such file"
    echo "Usuage: ./assignment9.sh filename"
exit 1
fi


#delete empty lines without taking a backup file
sed -i '' '/^$/d' $file
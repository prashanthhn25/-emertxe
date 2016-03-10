#!/bin/bash
<<COMMENT
To rename current working directory with given name
COMMENT

#------------------------------------------

#check for argument count
if [ $# -ne 1 ]
then
	echo "Error: no file/directory name is given"
	echo "Usage: please provide the file/directory name to be renamed with:
		eg: ./assignment17.sh <name of file/directory>"
	exit 1
fi

path=$1
currentDirectory=${PWD##*/}
#currentDirectory=`basename $PWD`
echo $currentDirectory
cd ../

#----------------------------------------

#check if the given file/directory path exists or not
if [ -e $path ]
then
	echo "Error: $path File/directory already exists in the parent directory"
	exit 1
else
	echo $currentDirectory
	mv "$currentDirectory" "$path"
fi


#!/bin/bash
<<COMMENT
Write a script to locks down file permission for a particular directory.
(remove all permission for groups and others)
COMMENT

#----------------------------------------------

#check for argument to be entered
if [ $# -ne 1 ]
then
	echo "Error: Invalid input. Enter an arg (directory)]"
	echo "eg: ./ assignment35.sh <mydirectory> "
	exit 1
fi

myDirectory=$1

#check for valid directory
if [ ! -d $myDirectory ]
then
    echo "$myDirectory is not a directory"
    echo "eg: ./ assignment35.sh <mydirectory> "
    exit 1
fi

# To give all rights to group and other for a given directory
#chmod -R go+x,go+r,go+w $myDirectory

# To remove all rights to group and other for a given directory
chmod -R go-x,go-r,go-w $myDirectory

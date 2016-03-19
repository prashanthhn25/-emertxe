#!/bin/bash
<<COMMENT
to search a user present in your system
COMMENT

#------------------------------------------

#check for argument count
if [ $# -ne 1 ]
then
    echo "Error: No user name is given"
    echo "Usage: ./assignment39.sh <username>"
    exit 1
fi


username=$1
grep "^$1" /etc/passwd

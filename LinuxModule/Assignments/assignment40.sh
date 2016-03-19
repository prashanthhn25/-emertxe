#!/bin/bash
<<COMMENT
Write a script to replace 20% lines in a c file randomly with the pattern <-DEL->
COMMENT

#----------------------------------------------

#check for argument to be entered
if [ $# -ne 1 ]
then
	echo "Error: Invalid input. Enter an arg (C file)]"
	echo "eg: ./ assignment40.sh <myfile> "
	exit 1
fi

myfile=$1

#check for valid directory
if [ ! -f $myfile ]
then
    echo "$myfile is not a file"
    echo "eg: ./ assignment40.sh <myfile> "
    exit 1
fi

#to get the total number of lines
totalLines=`cat $myfile | wc -l`

#to get 20% of total lines
twentyper=$(($(($totalLines*20))/100))

pattern="<--DEL-->"
#to generate 20% of random line numbers from totalLines
#cat /dev/urandom | LC_ALL=C tr -cd '1-5' | fold -w 1 | head -n 1
for ((i=0 ; i < $twentyper ;i++))
do
    randomval=$(($RANDOM%$totalLines))

    if [ "`sed -n "${randomval}"p $myfile`" = $pattern ]
    then
        randomval=$(($RANDOM%$totalLines))
        sed -i '' "${randomval}s/.*/<--DEL-->/" $myfile
    else
        sed -i '' "${randomval}s/.*/<--DEL-->/" $myfile
    fi
done



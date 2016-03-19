#!/bin/bash
<<COMMENT
To sort a given number set in assending or descending order depending on the user option
Usage: ./assignment14.sh 1 2 3 4 5 6

COMMENT

# isNumber file is included as it has isInteger function
. ./isNumber.sh 

#----------------------------------------------
 
#check for minimum 1 integer to be entered
if [ $# -lt 1 ]
then
	echo "Error: Invalid input. Enter a set of numbers [minimum 1arg]"
	echo "eg: ./ assignment14.sh 1 2 3 4"
	exit 1
fi

givenNumbers=($@)

#check for valid integers
for (( i=0; i < ${#givenNumbers[@]}; i++ ))
do
    isInteger ${givenNumbers[$i]}
done 

#----------------------------------------------

echo "Enter: 
'ASC' to sort in ascending order or 
'DSC' for descending order"
read order

case $order in
ASC) 	#sort assendingly
	sortedArray+=(`for (( i=0; i < ${#givenNumbers[@]}; i++ ));do
	echo ${givenNumbers[$i]};done | sort -g`)
	echo In Ascending Sorted Order: ${sortedArray[@]}
	;;
DSC) 	#sort descendingly
	sortedArray+=(`for (( i=0; i < ${#givenNumbers[@]}; i++ ));do
	echo ${givenNumbers[$i]};done | sort -rg`)
	echo In Descending Sorted Order: ${sortedArray[@]}
	;;
*)
	echo "Error: Invalid order entry"
	exit 1
	;;
esac


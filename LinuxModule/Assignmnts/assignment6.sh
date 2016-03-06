#!/bin/bash
#
# Script for arithmetic calculator using command line arguments
#

#check for arguments
if [ $# -ne 3 ]
then 
	echo "Error: Invaid number of arguments"
	echo "Usage: ./assignment6.sh 1 + 2"
fi

operator=$2

case ${operator} in
	+) echo `echo "$1 $2 $3" | bc`
	   ;; 
	-) echo `echo "$1 $2 $3" | bc`
	   ;;	
	%) echo `echo "$1 $2 $3" | bc`
	   ;;
	/) echo `echo "$1 $2 $3" | bc`
	   ;;
	\*) echo $(($1*$3))
	   ;;
	*) echo invalid
	   ;;
esac
	  	



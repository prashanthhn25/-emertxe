#!/bin/bash
#
# Read n and generate a pattern
#   1
#   23
#   456
#   78910
#

echo Enter n value:
read n

count=1

for (( i = 1; i <= n; i++ ))
do
	for (( j=1; j <= i; j++ ))
	do
		echo -n $count
		count=$(($count+1))
	done
   	echo " "
done


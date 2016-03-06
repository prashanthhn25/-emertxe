#!/bin/bash
#
# Read n and generate a pattern
#   1
#   12
#   123
#   1234
#

echo Enter n value:
read n

for (( i = 1; i <= n; i++ ))
do
	for (( j=1; j <= i; j++ ))
	do
		echo -n $j
	done
   	echo " "
done


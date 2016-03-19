#!/bin/bash
<<COMMENT
Chess board
COMMENT

echo "Chess Board"

for (( i=1; i<=8; i++))
do
	for (( j=1; j<=8; j++))
	do
		total=$(($i+$j))
		temp=$(($total%2))
		# for alternative blocks
		if [ $temp -eq 0 ]
		then
			echo -e -n "\033[47m" " "  #white
		else
			echo -e -n "\033[40m" " " #black
		fi
	done
	echo -e -n "\033[0m" " "
	echo ' '
done

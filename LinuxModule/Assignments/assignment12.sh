#!/bin/bash
<<COMMENT
To print the length of each and every string using arrays
Usage: bash assignment12.sh
COMMENT

echo "Enter a string: "
read string

#collect the words of the string in wordArray
for (( i=1; i<=`echo $string | wc -w`; i++ ))
do
	digit=`echo $string  | cut -d " " -f$i`
	wordArray+=($digit)
done

#collect the count of characters excluding null of each word in wordCountArray
for (( j=0; j<${#wordArray[@]}; j++ ))
do
	wordCountArray+=($((`echo ${wordArray[$j]} | wc -c`-1)))
done

echo ${wordCountArray[@]}




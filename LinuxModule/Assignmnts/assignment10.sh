#!/bin/bash
<<COMMENT
Write a script to perform arithmetic operation on given number depending on the operator
    eg: i/p 1234+ then o/p : 10
COMMENT

#check for argument count
if [ $# -lt 1 ]
then
	echo "Error: Invalid argument count"
	echo "Usuage: ./assignment10.sh 1234+"
	exit 1
fi

digit=$1
#to get the string count that also includes null
count=`echo $digit | wc -c`

#to get the digit count
digitCount=$(($count-2))

#to get the givenNuber
givenNumber=${digit:0:$digitCount}
echo "Given number: $givenNumber"

#to get the operator
operator=${digit:$digitCount:$count}
echo "operation done: $operator"

#to get first digit initially
result=${digit:0:1}

#do the said operation on each digit
for (( i=1; i<digitCount; i++))
do
    nextDigit=${digit:$i:1}
    result=$(($result$operator$nextDigit))
done

echo "result = $result"
#!/bin/bash
<<COMMENT
Fibonacci number: 0 1 1 2 3 5 8 13 ...
To get the greatest fibonacci numbers <= n where n is the entered number
COMMENT

echo "Enter the number n to get the greatest fibonacci numbers <= n"
read N

f1=0
f2=1
while [ $f1 -le $N ]
do
	f3=$f1
	f1=$(($f1+$f2))
	f2=$f3
done
echo "the greatest fibonacci numbers is [<= n]  : $f2"

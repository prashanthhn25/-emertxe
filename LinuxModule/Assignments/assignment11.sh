#!/bin/bash
<<COMMENT
Read n and generate fibonacii nos <= n
COMMENT

#read n
echo "Enter the value of n:"
read Num

f1=0
f2=1

echo "The Fibonacci Nos <= $Num is : "

i=0
while [ $f1 -le $Num ]
do
    echo -n "$f1 "
    fn=$((f1+f2))
    f1=$f2
    f2=$fn
done
echo

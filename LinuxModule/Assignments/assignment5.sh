#!/bin/bash
#
# Script for addition of two numbers for real numbers
#

echo "Enter the first number:"
read num1

echo "Enter the second number:"
read num2

result=`echo "$num1+$num2" | bc`

echo "addition of $num1 and $num2 is $result"


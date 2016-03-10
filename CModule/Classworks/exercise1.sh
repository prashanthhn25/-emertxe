#!/bin/bash
<<COMMENT
Pattern generation
COMMENT

echo "Enter the symbol"
read SYMBOL

echo "Enter the no of symbols"
read NO_OF_SYM

if [ $(($NO_OF_SYM%2)) -eq 0 ]
then
	echo "Error: INvalid no of lines. It should be odd"
	exit
fi

echo "Enter the no of lines"
read NO_OF_LINES

#echo "Maximum no of symbols"
#read MAX_NO

#echo "Minimum no of symbols"
#read MIN_NO

if [ $NO_OF_LINES -lt 1 ]
then
	echo "Error: INvalid no of lines"
	exit
fi

<<COMMENT
if [ $NO_OF_SYM -lt $MIN_NO ]
then
	echo "Error: INvalid no of lines"
	exit
fi
COMMENT

#calculate no of spaces
NO_OF_SPACES=$(($(($NO_OF_SYM/2))+1))

print_first_line()
{
	for (( count2=0; count2 < $2; count2++ ))
	do
		echo -n $1
	done
	return
}

print_space()
{
	for (( count=1; count < $(($1-1)); count++ ))
	do
		echo -n " "
	done
	return
}

print_middle_line()
{
	for (( count3=0; count3 < "$3"; count3++ ))
	do
		echo ' '
		echo -n $1
		print_space $2
		echo -n $1
	done
	echo ' '
	return
}



print_first_line $SYMBOL $NO_OF_SYM
print_middle_line $SYMBOL $NO_OF_SPACES $NO_OF_LINES
print_first_line $SYMBOL $NO_OF_SYM



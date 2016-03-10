#!/bin/bash
<<COMMENT
Pattern generation
%%%%%%%%% 
%   %   % 
%   %   % 
%   %   % 
%%%%%%%%% 
%   %   % 
%   %   % 
%   %   % 
%%%%%%%%%
COMMENT

echo "Enter the symbol"
read SYMBOL

echo "Enter the no of symbols"
read NO_OF_SYM

echo "Maximum no of symbols"
read MAX_NO

echo "Minimum no of symbols"
read MIN_NO

if [ $NO_OF_SYM -gt $MAX_NO ]
then
	echo "Error: INvalid no of lines"
	exit
fi

if [ $NO_OF_SYM -lt $MIN_NO ]
then
	echo "Error: INvalid no of lines"
	exit
fi
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

print_space_line()
{

	for (( count=1; count < $(($2-1)); count++ ))
	do
		echo ' '
		echo -n $1
		print_space $2
		echo -n $1
		print_space $2
		echo -n $1
	done
	return
}




print_first_line $SYMBOL $NO_OF_SYM
for (( count3=1; count3 < $(($NO_OF_SPACES-1)); count3++ ))
do
	print_space_line $SYMBOL $NO_OF_SPACES
done
echo ' '
print_first_line $SYMBOL $NO_OF_SYM
for (( count3=1; count3 < $(($NO_OF_SPACES-1)); count3++ ))
do
	print_space_line $SYMBOL $NO_OF_SPACES
done
echo ' '
print_first_line $SYMBOL $NO_OF_SYM



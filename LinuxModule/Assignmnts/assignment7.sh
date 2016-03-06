
#!/bin/bash
<<COMMENT
Write script to compare larger integer value from a n number of arguments using command line arguments
COMMENT

#check for argument count
if [ $# -lt 1 ]
then
    echo "Error: Invalid argument count"
    echo "Usuage: ./assignment7.sh 1 2 3"
    exit 1
fi

#consider the elements in an array
arrayOfArg=($@)
#consider the first element to be teh largest initially
largest=$1


#compare each element with the largest value
# if true, replace the largest with that element

for (( i=0; i<${#arrayOfArg[@]}; i++ ))
do
    if [ ${arrayOfArg[$i]} -gt $largest  ]
    then
        largest=${arrayOfArg[$i]}
    fi
done

echo $largest


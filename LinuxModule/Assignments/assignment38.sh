#!/bin/bash
<<COMMENT
for each directory in the $PATH, display the number of executable files in that directory
COMMENT

echo $PATH
#count the delimiters
count=`echo $PATH | sed 's/[^:]//g' | tr -d '\012' | wc -c`

#to find executables in each path
for (( i = 1 ; i < $(($count + 2)) ; i++))
do
    eachPath=`echo $PATH | cut -d ":" -f${i}`
    echo $eachPath

    #in MAC
    execfilecount=`find $eachPath -perm +0111 -type f| wc -l`
    echo $execfilecount

    #-executable doesnt work on MAC
    #execfilecount=`find $eachPath -executable | wc -l`
    #echo $execfilecount
done


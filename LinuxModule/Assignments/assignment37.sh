#!/bin/bash
<<COMMENT
Count the number of users with user IDs between 500 and 10000 on the system
COMMENT

#to get only the list and delete any lines that are commented into tempFile2
cat /etc/passwd > tempFile
sed '/^#/d' tempFile > tempFile2

#get the user name list and the Total username count
totalUserNames=`cat tempFile2 | cut -d":" -f1`
totalUserCount=`cat tempFile2 | cut -d":" -f1 | wc -l`

#get the user id
totalUserIds=`cat tempFile2 | cut -d":" -f3`


#to get the users with user IDs between 500 and 10000
for (( i=1; i<=$totalUserCount; i++ ))
do
    username=`echo $totalUserNames | cut -d" " -f$i`

    usedid=`echo $totalUserIds | cut -d" " -f$i`

    if [ $usedid -ge 500 ] && [ $usedid -le 10000 ]
    then
        echo "$username has $usedid id"

    fi
done

#clean the tempFiles
rm -f tempFile
rm -f tempFile2
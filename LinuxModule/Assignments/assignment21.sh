#!/bin/bash
<<COMMENT
Display the longest and shortest usernames on the system
COMMENT
echo "the longest and shortest usernames on the system are: "

#to get only the list and delete any lines that are commented into tempFile2
cat /etc/passwd > tempFile
sed '/^#/d' tempFile > tempFile2

#get the user name list and the Total username count
totalUserNames=`cat tempFile2 | cut -d":" -f1`
totalUserCount=`cat tempFile2 | cut -d":" -f1 | wc -l`

#-------------------------------------

# initialization
longlettercount=0
# letter count of first username 
shortlettercount=$((`echo $totalUserNames | cut -d" " -f1 | wc -m`-1))


#to get the longest and shortest usernames
for (( i=1; i<=$totalUserCount; i++ ))
do
	username=`echo $totalUserNames | cut -d" " -f$i`
	#username letter count is stored
	namecount=$((`echo $totalUserNames | cut -d" " -f$i | wc -m`-1))

	if [ $namecount -ge $longlettercount ]
	then
		#if the namecount is greater than previously saved longlettercount, update the longest word to be the current username and longlettercount to current namecount
		longestword=$username
		longlettercount=$namecount
	elif [ $namecount -le $shortlettercount ]
	then
		#if the namecount is smaller than previously saved shortlettercount, update the shortestword to be the current username and shortlettercount to current namecount
		shortestword=$username
		shortlettercount=$namecount
	fi
done

echo " shortest username: $shortestword "
echo " longest username: $longestword "

#clean the tempFiles
rm -f tempFile
rm -f tempFile2
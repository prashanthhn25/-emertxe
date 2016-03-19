#!/bin/bash
<<COMMENT
scriptname: sayHello.sh
This script runs as soon as you logon to the system, and it prints the message depening on system time.

NOTE:
When bash is invoked, it firs reads and executes commands from file /ec/profile, if that file exits.
After reading that file, it looks for ~/.bash_profile, ~/.bash_login,and ~/.profile, in that order, and reads and executes commands from the first one that exists and is readable.

The --noprofile option may be used when the shell is started to inhibit this behavior.

COMMENT

sysHTime=`date +%H`

if [ $sysHTime -ge 9 -a $sysHTime -le 13 ]
then 
	echo "Good Morning"
elif [ $sysHTime -ge 14 -a $sysHTime -lt 17 ]  
then
	echo "Good Afternoon"
elif [ $sysHTime -ge 17 -a $sysHTime -lt 21 ]
then
	echo "good Evening"
elif [ $sysHTime -ge 21 -o $sysHTime -le 9 ]
then
	echo "Good Night"
fi



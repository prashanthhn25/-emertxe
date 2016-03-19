#!/bin/bash
<<COMMENT
scriptname: sayHello.sh
This script runs as soon as you logon to the syatem, and it prints the message depening on system time. 
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



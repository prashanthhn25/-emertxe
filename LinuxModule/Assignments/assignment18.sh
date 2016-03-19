#!/bin/bash
<<COMMENT
Given the album name and corresponding directory, rename them properly by inserting index numbers
Usage: eg: given file numbers DSN001.jpg, DSN002.jpg as 
		linux_class_photos_001.jpg, linux_class_photos_002.jpg
COMMENT

#------------------------------------------

#check for argument count
if [ $# -ne 1 ]
then
	echo "Error: No directory/album name is given"
	echo "Usage: Please provide the album/directory path:" 
    echo "eg: ./assignment18.sh <path of album/directory>"
	exit 1
fi

path=$1

#check if the given file/directory path exists or not
if [ ! -e $path ]
then
	echo "Error: No such file/directory exists"
	exit 1
fi

#----------------------------------------
cd $1


count=`ls | wc -w`

for (( j=1; j <= $count; j++ ))
do
	newName=DSN00${j}
    mv ${newName}.jpg linux_class_photos_${j}.jpg
    #mv linux_class_photos_${j}.jpg DSN00${j}.jpg
done
echo Done

#!/bin/sh

echo "Reading a file line by line"

i=1
while read line
do
	echo "Line $i is $line"
	i=$(($i+1))
done < file.txt 


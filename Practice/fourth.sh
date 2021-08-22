#!/bin/sh
 
i=1

while [ $i -le 5 ]
do
	echo "value of i is $i"
	i=$(($i + 1 ))
done

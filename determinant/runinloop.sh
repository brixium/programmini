#!/usr/bin/env sh
i=1
while [ "$i" -le 9999 ]
do 
	./determinant < input.txt
	i=$((i+1))
	echo i is $i
done

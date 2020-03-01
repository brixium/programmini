#!/bin/sh
#script by me, @brixium
#works with bash, sh, ksh and zsh
#doesn't work with csh and tcsh
FOLDER="application"
fnumber=1
# for FNUMBER in {1..10} #doesnt work
# for (( fnumber=1; fnumber<=10; fnumber++ )) #only works with bash
while [ $fnumber -le 10 ]; #-le = less or equal
do
	# echo "Controllo se esiste la cartella ${FOLDER}${fnumber}"
	if [ -d ${FOLDER}${fnumber} ]
	then
		# echo "esiste"
		cd ${FOLDER}${fnumber}
		make -f Makefile.example
		rm *.o
		cd ..
	fi
	fnumber=$(( fnumber + 1))
done


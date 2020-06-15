#!/usr/bin/env bash

main () {
	local val=19

	local aux=$val
	local result=1

	while [ $aux -gt 0 ]
	do
		let result=$result\*$aux
		((aux=aux-1))
	done

	echo $result
}

main

#!/bin/bash

# Edit these variables to point to the right directory
executable="./mstprimdriver"
folder="TestCaseRandom/"

#################################################
#################################################
i=0
while true; do
    ((i++))

    inputFile="${folder}test${i}"

    if [ ! -f ${inputFile}.in ]; then
        break;
    fi

    ${executable} < ${inputFile}.in | diff ${inputFile}.out -

    if [ ! $? -eq 0 ]; then
    	echo ""
    	echo "Failed Test: ${i}"
        echo "Failing command: ${executable} < ${inputFile}.in | diff ${inputFile}.out -"
		exit 1
	fi
    echo "Finished Test: ${i}"
done

((i--))
echo ""
echo "Success!!"
echo "Total number of tests: ${i}"
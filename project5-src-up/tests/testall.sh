#!/bin/bash

#Build project 5
(cd .. && make clean)
(cd .. && make)


# Test driver
function runtest {
	prog=$1
	args_in=$2
	args_out=$3
	secs=$4
	descr="$args_in"

	echo "======= Test: $descr ==========="

	#Run tested program
	timeout $secs ./${prog} < $args_in > ${prog}.out
	diff ${prog}.out $args_out > diff.out
	if [ $? -eq 0 ]; then
		echo Test passed...;
	else
		echo "*****Test Failed*****";
		echo ------ Your Output ----------
		cat $prog.out
		echo ------ Expected Output ------
		cat $args_out
		echo ------ Difference -----------
		cat diff.out
		echo -----------------------------
	fi


	echo
}


if [ $# = 0 ] || [ "$1" = "-p1" ]
then
        echo "---Connected Components and seperation edges ----"
        cp ../program .
        runtest program test1-1.in test1-1.out 0.7
        runtest program test1-2.in test1-2.out 0.7
        runtest program test1-3.in test1-3.out 0.7
        runtest program test1-4.in test1-4.out 0.7
        rm program
fi

if [ $# = 0 ] || [ "$1" = "-p2" ]
then
	echo "---Dijsktra's Shortest Path----"
	cp ../program .
	runtest program test2-6.in test2-6.out 3
	runtest program test2-1.in test2-1.out 3
	runtest program test2-2.in test2-2.out 3
	runtest program test2-3.in test2-3.out 3
	runtest program test2-4.in test2-4.out 3
	runtest program test2-5.in test2-5.out 8
	rm program
fi


if [ $# = 0 ] || [ "$1" = "-p3" ]
then
        echo "---Euler Tour----"
        cp ../program .
        runtest program test3-1.in test3-1.out 3
        runtest program test3-2.in test3-2.out 3
        runtest program test3-3.in test3-3.out 3
        runtest program test3-4.in test3-4.out 100
        runtest program test3-5.in test3-5.out 200
        rm program
fi

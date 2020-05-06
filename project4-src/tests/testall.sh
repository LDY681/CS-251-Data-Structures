#!/bin/bash

#Build project 4
(cd .. && make clean)
(cd .. && make)

#Build the test cases
make clean
make


total=0
totalmax=0
tCount=0

rm -f total.txt *out



# Test driver
function runtest {
	prog=$1
	args=$2
	grade=$3
	totalmax=`expr $totalmax + $grade`;

	descr="$prog $args"

	echo "======= Test: $descr ==========="

	#Run tested program
	timeout 3 ./$prog $args > $prog.out
	./$prog.org $args > $prog.org.out
	diff $prog.out $prog.org.out > diff.out
	if [ $? -eq 0 ]; then
		echo Test passed...;
		printf "%-55s: %-3d of %-3d\n" "$descr " $grade $grade >> total.txt
		total=`expr $total + $grade`;
	else
		echo "*****Test Failed*****";
		echo ------ Your Output ----------
		cat $prog.out
		echo ------ Expected Output ------
		cat $prog.org.out
		echo ------ Difference -----------
		cat diff.out
		echo -----------------------------
		printf "%-55s: %-3d of %-3d\n" "$descr " 0 $grade >> total.txt
	fi

	echo
}

function runtest2 {
	prog=$1
	args=$2
	grade=$3
	bonus=$4
	if [ $4 -eq 0 ]; then
		totalmax=`expr $totalmax + $grade`;
	fi

	descr="$prog $args"

	echo "======= Test: $descr ==========="

	#Run tested program
	timeout 3 ./$prog $args
	if [ $? -eq 0 ]; then
		echo Test passed...;
		printf "%-55s: %-3d of %-3d\n" "$descr " $grade $grade >> total.txt
		total=`expr $total + $grade`;
	else
		echo "*****Test Failed*****";
		printf "%-55s: %-3d of %-3d\n" "$descr " 0 $grade >> total.txt
	fi

	echo
}

function generateMaps {
	prog=$1
	src=$2
	dest=$3
	args="$2 $3.out"
	timeout 120 ./$prog $args
	args="$2 $3.org.out"
	./$prog.org $args
}

function rundiff {
	out1=$1
	out2=$2
	testinput=$3
	grade=$4
	totalmax=`expr $totalmax + $grade`;
	descr=
		if [ "$testinput" != "none" ]; then
			descr="$testinput"
		else
			descr="diff $out1 $out2"
		fi

	echo "======= Test: $descr ==========="

	#Run diff of outputs
	diff $out1 $out2 > diff.out
	if [ $? -eq 0 ]; then
		echo Test passed...;
		printf "%-55s: %-3d of %-3d\n" "$descr " $grade $grade >> total.txt
		total=`expr $total + $grade`;
	else
		echo "*****Test Failed*****";
		printf "%-55s: %-3d of %-3d\n" "$descr " 0 $grade >> total.txt
	fi
	echo
}

function runSearch {
	prog=$1
	src=$2
	phrase=$3
	descr=$4
	grade=$5
	totalmax=`expr $totalmax + $grade`;

	echo "======= Test: $descr ==========="

	timeout 3 ./$prog $src $phrase > $descr.out
	./$prog.org $src $phrase > $descr.org.out

	# Run diff of outputs
	diff $descr.out $descr.org.out > diff.out
	if [ $? -eq 0 ]; then
		echo Test passed...;
		printf "%-55s: %-3d of %-3d\n" "$descr " $grade $grade >> total.txt
		total=`expr $total + $grade`;
	else
		echo "*****Test Failed*****";
		echo ------ Your Output ----------
		cat $descr.out
		echo ------ Expected Output ------
		cat $descr.org.out
		echo ------ Difference -----------
		cat diff.out
		echo -----------------------------
		printf "%-55s: %-3d of %-3d\n" "$descr " 0 $grade >> total.txt
	fi
	echo
}

# we only check for memory if the program is decompressing and compressing correctly
function rundiffandcheckmemleaks {
	infile=$1
	out1=$2
	out2=$3
	testinput=$4
	grade=$5
	totalmax=`expr $totalmax + $grade`;
	descr=
		if [ "$testinput" != "none" ]; then
			descr="$testinput"
		else
			descr="diff $out1 $out2"
		fi

	echo "======= Test: $descr ==========="

	#Run diff of outputs
	diff $out1 $out2  > diff.out
	if [ $? -eq 0 ]; then
		#cat $prog.out
		valgrind --leak-check=yes --error-exitcode=1 ../huffman -d $1 out 1> /dev/null 2>&1
		if [ $? -eq 0 ]; then
			echo Test passed...;
			printf "%-55s: %-3d of %-3d\n" "$descr " $grade $grade >> total.txt
			total=`expr $total + $grade`;
		else
			echo "*****Test Failed*****";
			printf "%-55s: %-3d of %-3d\n" "$descr " 0 $grade >> total.txt
		fi
	else
		echo "*****Test Failed*****";
		printf "%-55s: %-3d of %-3d\n" "$descr " 0 $grade >> total.txt
	fi
	echo
}

function printResults {
	echo
	echo   "-------------------------------------------------------------------"
	echo   "CS251: Search Engine : $USER   "
	echo   "-------------------------------------------------------------------"
	cat total.txt
	echo   "-------------------------------------------------------------------"
	echo   "CS251: $LAB. $USER" `date` " Total: " $total of $totalmax >> total.txt
	tail -1 total.txt
	tail -1 total.txt >> .local.total.out
}

if [ $# = 0 ] || [ "$1" = "-p1" ]
then
	echo "---Red-Black Tree Operations----"
	runtest2 test1-1 "" 7 0
	runtest2 test1-2 "" 14 0
	runtest test1-3 "" 14
	runtest test1-4 "" 14
	runtest2 test1-5 "" 14 0
	runtest2 test1-6 "" 7 0
	runtest2 test1-7 "" 8 1
	runtest2 test1-8 "" 2 1
fi

if [ $# = 0 ] || [ "$1" = "-p2" ]
then
	echo "---Scanning and Searching----"

	generateMaps ../scan "urls1.txt" "wordmap1"
	rundiff "wordmap1.out" "wordmap1.org.out" "test2-1" 4

	generateMaps ../scan "urls2.txt" "wordmap2"
	rundiff "wordmap2.out" "wordmap2.org.out" "test2-2" 4

	generateMaps ../scan "urls3.txt" "wordmap3"
	rundiff "wordmap3.out" "wordmap3.org.out" "test2-3" 4


	runSearch ../search "wordmap1.org.out" "science" "test2-4" 3

	runSearch ../search "wordmap1.org.out" "aliaga gustavo" "test2-5" 3

	runSearch ../search "wordmap2.org.out" "super nintendo entertainment system" "test2-6" 3

	runSearch ../search "wordmap2.org.out" "angry wizard" "test2-7" 3

	runSearch ../search "wordmap3.org.out" "LiNUx" "test2-8" 3

	runSearch ../search "wordmap3.org.out" "gnu vim neptune" "test2-9" 3

fi

printResults


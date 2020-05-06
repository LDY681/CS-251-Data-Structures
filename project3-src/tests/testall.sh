#!/bin/bash

#Build Huffman project
(cd .. && make clean)
(cd .. && make)

#Build the test cases
make clean
make


total=0
totalmax=0
tCount=0

rm -f total.txt tmp decoded.* *out total.txt



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
	totalmax=`expr $totalmax + $grade`;

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


function generateFiles {
	prog=$1
	mode=$2
	src=$3
	dest=$4
	args="$2 $3 $4"
	timeout 3 ./$prog $args
	args="$2 $3 $4.org"
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
	echo   "CS251: Huffman Encoding Lab : $USER   "
	echo   "-------------------------------------------------------------------"
	cat total.txt
	echo   "-------------------------------------------------------------------"
	echo   "CS251: $LAB. $USER" `date` " Total: " $total of $totalmax >> total.txt	
	tail -1 total.txt
	tail -1 total.txt >> .local.total.out
}

if [ $# = 0 ] || [ "$1" = "-p1" ]
then
	echo "---Min-Heap Operations----"
	runtest2 test1-1 "" 1
	runtest test1-2 "" 2
	runtest test1-3 "" 2
	runtest2 test1-4 "" 2
	runtest test1-5 "" 2
	runtest2 test1-6 "" 1
fi

if [ $# = 0 ] || [ "$1" = "-p2" ]
then
	echo "---Encoding----"
	generateFiles ../huffman "-e" "simple1.txt" "encodedsimple1.huff"
	rundiff "encodedsimple1.huff" "encodedsimple1.huff.org" "test2-1" 1

	generateFiles ../huffman "-e" "simple2.txt" "encodedsimple2.huff"
	rundiff "encodedsimple2.huff" "encodedsimple2.huff.org" "test2-2" 1

	generateFiles ../huffman "-e" "wiki1.txt" "encodedwiki1.huff"
	rundiff "encodedwiki1.huff" "encodedwiki1.huff.org" "test2-3" 1

	generateFiles ../huffman "-e" "wiki2.txt" "encodedwiki2.huff"
	rundiff "encodedwiki2.huff" "encodedwiki2.huff.org" "test2-4" 1

	generateFiles ../huffman "-e" "wiki3.txt" "encodedwiki3.huff"
	rundiff "encodedwiki3.huff" "encodedwiki3.huff.org" "test2-5" 1

	generateFiles ../huffman "-e" "puppy.bmp" "encodedpuppy.huff"
	rundiff "encodedpuppy.huff" "encodedpuppy.huff.org" "test2-6" 1

	generateFiles ../huffman "-e" "snow.bmp" "encodedsnow.huff"
	rundiff "encodedsnow.huff" "encodedsnow.huff.org" "test2-7" 1

	generateFiles ../huffman "-e" "tulips.bmp" "encodedtulips.huff"
	rundiff "encodedtulips.huff" "encodedtulips.huff.org" "test2-8" 1

	generateFiles ../huffman "-e" "SkipLists.pdf" "encodedSkipLists.huff"
	rundiff "encodedSkipLists.huff" "encodedSkipLists.huff.org" "test2-9" 1

	generateFiles ../huffman "-e" "HashTables.pdf" "encodedHashTables.huff"
	rundiff "encodedHashTables.huff" "encodedHashTables.huff.org" "test2-10" 1
fi

if [ $# = 0 ] || [ "$1" = "-p3" ]
then
	echo "---Decoding----"
	generateFiles ../huffman "-d" "encodedsimple1.huff" "decoded.simple1"
	rundiff "decoded.simple1" "simple1.txt" "test3-1" 7

	generateFiles ../huffman "-d" "encodedsimple2.huff" "decoded.simple2"
	rundiff "decoded.simple2" "simple2.txt" "test3-2" 7

	generateFiles ../huffman "-d" "encodedwiki1.huff" "decoded.wiki1"
	rundiff "decoded.wiki1" "wiki1.txt" "test3-3" 7

	generateFiles ../huffman "-d" "encodedwiki2.huff" "decoded.wiki2"
	rundiff "decoded.wiki2" "wiki2.txt" "test3-4" 7

	generateFiles ../huffman "-d" "encodedwiki3.huff" "decoded.wiki3"
	rundiff "decoded.wiki3" "wiki3.txt" "test3-5" 7

	generateFiles ../huffman "-d" "encodedpuppy.huff" "decoded.puppy"
	rundiff "decoded.puppy" "puppy.bmp" "test3-6" 7

	generateFiles ../huffman "-d" "encodedsnow.huff" "decoded.snow"
	rundiff "decoded.snow" "snow.bmp" "test3-7" 7

	generateFiles ../huffman "-d" "encodedtulips.huff" "decoded.tulips"
	rundiff "decoded.tulips" "tulips.bmp" "test3-8" 7

	generateFiles ../huffman "-d" "encodedSkipLists.huff" "decoded.SkipLists"
	rundiff "decoded.SkipLists" "SkipLists.pdf" "test3-9" 8

	generateFiles ../huffman "-d" "encodedHashTables.huff" "decoded.HashTables"
	rundiff "decoded.HashTables" "HashTables.pdf" "test3-10" 8

	#memory leaks check
	rundiffandcheckmemleaks "encodedHashTables.huff" "decoded.HashTables" "HashTables.pdf" "test3-11" 2
	rundiffandcheckmemleaks "encodedpuppy.huff" "decoded.puppy" "puppy.bmp" "test3-12" 2
	rundiffandcheckmemleaks "encodedsimple1.huff" "decoded.simple1" "simple1.txt" "test3-13" 2
	rundiffandcheckmemleaks "encodedwiki1.huff" "decoded.wiki1" "wiki1.txt" "test3-14" 2




fi

printResults
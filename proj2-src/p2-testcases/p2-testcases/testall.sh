#!/bin/sh

mkdir -p my_out
make clean
make
./stack < ./stack1.txt > ./my_stack1out.txt
./stack < ./stack2.txt > ./my_stack2out.txt
./stack < ./stack3.txt > ./my_stack3out.txt
./stack < ./stack4.txt > ./my_stack4out.txt
./stack < ./stack5.txt > ./my_stack5out.txt

./queue < ./queue1.txt > ./my_queue1out.txt
./queue < ./queue2.txt > ./my_queue2out.txt
./queue < ./queue3.txt > ./my_queue3out.txt
./queue < ./queue4.txt > ./my_queue4out.txt
./queue < ./queue5.txt > ./my_queue5out.txt

./expr_eval < ./expr_eval.txt > ./my_expr_eval_out.txt

diff -b ./stack1out.txt ./my_stack1out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Stack - testcase 1 failed."
else
        echo "Stack - testcase 1 passed."
fi
diff -b ./stack2out.txt ./my_stack2out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Stack - testcase 2 failed."
else
        echo "Stack - testcase 2 passed."
fi
diff -b ./stack3out.txt ./my_stack3out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Stack - testcase 3 failed."
else
        echo "Stack - testcase 3 passed."
fi
diff -b ./stack4out.txt ./my_stack4out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Stack - testcase 4 failed."
else
        echo "Stack - testcase 4 passed."
fi
diff -b ./stack4out.txt ./my_stack4out.txt > ./my_/diff.txt
if [ -s ./diff.txt ]
then
        echo "Stack - testcase 5 failed."
else
        echo "Stack - testcase 5 passed."
fi
diff -b ./queue1out.txt ./my_queue1out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Queue - testcase 1 failed."
else
        echo "Queue - testcase 1 passed."
fi
diff -b ./queue2out.txt ./my_queue2out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Queue - testcase 2 failed."
else
        echo "Queue - testcase 2 passed."
fi
diff -b ./queue3out.txt ./my_queue3out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Queue - testcase 3 failed."
else
        echo "Queue - testcase 3 passed."
fi
diff -b ./queue4out.txt ./my_queue4out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Queue - testcase 4 failed."
else
        echo "Queue - testcase 4 passed."
fi
diff -b ./queue5out.txt ./my_queue5out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Queue - testcase 5 failed."
else
        echo "Queue - testcase 5 passed."
fi
diff -b ./expr_eval_out.txt ./my_expr_eval_out.txt > ./diff.txt
if [ -s ./diff.txt ]
then
        echo "Expression evaluator testcases failed."
else
        echo "Expression evaluator textcases passed."
fi


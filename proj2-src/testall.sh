#!/bin/sh

mkdir -p my_out
make clean
make
./stack < ./testcases/stack1.txt > ./my_out/my_stack1out.txt
./stack < ./testcases/stack2.txt > ./my_out/my_stack2out.txt
./stack < ./testcases/stack3.txt > ./my_out/my_stack3out.txt
./queue < ./testcases/queue1.txt > ./my_out/my_queue1out.txt
./queue < ./testcases/queue2.txt > ./my_out/my_queue2out.txt
./queue < ./testcases/queue3.txt > ./my_out/my_queue3out.txt
./expr_eval < ./testcases/expr_eval.txt > ./my_out/my_expr_eval_out.txt
diff -b ./testcases/stack1out.txt ./my_out/my_stack1out.txt > ./my_out/diff.txt
if [ -s ./my_out/diff.txt ]
then
        echo "Stack - testcase 1 failed."
else
        echo "Stack - testcase 1 passed."
fi
diff -b ./testcases/stack2out.txt ./my_out/my_stack2out.txt > ./my_out/diff.txt
if [ -s ./my_out/diff.txt ]
then
        echo "Stack - testcase 2 failed."
else
        echo "Stack - testcase 2 passed."
fi
diff -b ./testcases/stack3out.txt ./my_out/my_stack3out.txt > ./my_out/diff.txt
if [ -s ./my_out/diff.txt ]
then
        echo "Stack - testcase 3 failed."
else
        echo "Stack - testcase 3 passed."
fi
diff -b ./testcases/queue1out.txt ./my_out/my_queue1out.txt > ./my_out/diff.txt
if [ -s ./my_out/diff.txt ]
then
        echo "Queue - testcase 1 failed."
else
        echo "Queue - testcase 1 passed."
fi
diff -b ./testcases/queue2out.txt ./my_out/my_queue2out.txt > ./my_out/diff.txt
if [ -s ./my_out/diff.txt ]
then
        echo "Queue - testcase 2 failed."
else
        echo "Queue - testcase 2 passed."
fi
diff -b ./testcases/queue3out.txt ./my_out/my_queue3out.txt > ./my_out/diff.txt
if [ -s ./my_out/diff.txt ]
then
        echo "Queue - testcase 3 failed."
else
        echo "Queue - testcase 3 passed."
fi
diff -b ./testcases/expr_eval_out.txt ./my_out/my_expr_eval_out.txt > ./my_out/diff.txt
if [ -s ./my_out/diff.txt ]
then
        echo "Expression evaluator testcases failed."
else
        echo "Expression evaluator textcases passed."
fi


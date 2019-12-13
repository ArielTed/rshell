#!/bin/sh

### pipe redirection test ###

../rshell << EOF
echo "ls -l | grep command"; ls -l | grep command
echo "echo This Is A Test File > testfile.txt && cat < testfile.txt | tr A-Z a-z | tee testfile1.txt | tr a-z A-Z > testfile2.txt"; echo This Is A Test File > testfile.txt && cat < testfile.txt | tr A-Z a-z | tee testfile1.txt | tr a-z A-Z > testfile2.txt
echo "cat < testfile.txt && cat < testfile1.txt && cat < testfile2.txt"; cat < testfile.txt && cat < testfile1.txt && cat < testfile2.txt
echo "rm testfile.txt && rm testfile1.txt && rm testfile2.txt; exit"; rm testfile.txt && rm testfile1.txt && rm testfile2.txt; exit
EOF

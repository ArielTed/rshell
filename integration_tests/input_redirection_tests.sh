#!/bin/sh

### input redirection test ###

../rshell << EOF
echo "echo This is a test file > testfile.txt && echo This is second line >> testfile.txt"; echo This is a test file > testfile.txt && echo This is second line >> testfile.txt
echo "wc -l < testfile.txt && echo File has two lines"; wc -l < testfile.txt && echo File has two lines
echo "echo This Is A Test File > testfile.txt; cat < testfile.txt; tr A-Z a-z < testfile.txt || tr a-z A-Z < testfile.txt"; echo This Is A Test File > testfile.txt; cat < testfile.txt; tr A-Z a-z < testfile.txt || tr a-z A-Z < testfile.txt
echo "rm testfile.txt && exit"; rm testfile.txt && exit
EOF

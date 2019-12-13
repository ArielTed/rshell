#!/bin/sh

### output redirection test ###

../rshell << EOF
echo "echo hello > testfile.txt && echo world >> testfile.txt && cat testfile.txt && rm testfile.txt"; echo hello > testfile.txt && echo world >> testfile.txt && cat testfile.txt && rm testfile.txt
echo "echo hello > testfile.txt || echo HELLO > testfile.txt && echo WORLD >> testfile.txt || echo world >> testfile.txt && cat testfile.txt && rm testfile.txt"; echo hello > testfile.txt || echo HELLO > testfile.txt && echo WORLD >> testfile.txt || echo world >> testfile.txt && cat testfile.txt && rm testfile.txt
echo "echo This is a test > testfile.txt; test -e testfile.txt && echo File exists.; rm testfile.txt"; echo This is a test > testfile.txt; test -e testfile.txt && echo File exists.; rm testfile.txt
echo "exit"; exit
EOF

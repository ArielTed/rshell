#!/bin/sh

### commented command test ###

../rshell << EOF
echo "echo Hello World #echo Goodbye"; echo Hello World #echo Goodbye
echo "ls #&& echo A"; ls #&& echo A
echo "echo “Hello && Goodbye“"; echo "Hello && Goodbye"
echo "exit"; exit
EOF

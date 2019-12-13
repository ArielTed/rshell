#!/bin/sh

### single command test ###

../rshell << EOF
echo "ls"; ls
echo "echo This is my comment."; echo This is my comment.
echo "date"; date
echo "df -h"; df -h
echo "ls -f"; ls -f
echo "cal"; cal
echo "exit"; exit
EOF

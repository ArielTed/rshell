#!/bin/sh

### multiple commands test ###

../rshell << EOF
echo "ls -a; echo Hello World!"; ls -a; echo Hello World!
echo "ls -a && echo hello && echo goodbye || echo world"; ls -a && echo hello && echo goodbye || echo world
echo "df -h || cal"; df -h || cal
echo "cal && df -h"; cal && df -h
echo "exit"; exit
EOF

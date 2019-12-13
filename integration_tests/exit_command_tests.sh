#!/bin/sh

### exit command test ###

../rshell << EOF
echo "ls && test -d ../integration_tests && exit"; ls && test -d ../integration_tests && exit
EOF
../rshell << EOF
echo "echo test && exit"; echo test && exit
EOF
../rshell << EOF
echo "echo B && exit #echo C"; echo B && exit #echo C
EOF

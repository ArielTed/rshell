#!/bin/sh

### literal test command test ###

../rshell << EOF
echo "test -e ../header/operator.hpp"; test -e ../header/operator.hpp
echo "test ../header/operator.hpp"; test ../header/operator.hpp
echo "test -f ../header/operator.hpp"; test -f ../header/operator.hpp
echo "test -d ../header/operator.hpp"; test -d ../header/operator.hpp
echo "test -d ../header"; test -d ../header
echo "test -f ../header"; test -f ../header
echo "exit"; exit
EOF

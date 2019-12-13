#!/bin/sh

### symbolic test command test ###

../rshell << EOF
echo "[ -e ../header/operator.hpp ]"; [ -e ../header/operator.hpp ]
echo "[ ../header/operator.hpp ]"; [ ../header/operator.hpp ]
echo "[ -f ../header/operator.hpp ]"; [ -f ../header/operator.hpp ]
echo "[ -d ../header/operator.hpp ]"; [ -d ../header/operator.hpp ]
echo "[ -d ../header ]"; [ -d ../header ]
echo "[ -f ../header ]"; [ -f ../header ]
echo "exit"; exit
EOF

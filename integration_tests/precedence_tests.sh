#!/bin/sh

### precedence test ###

printf "\nTest 1 : (echo A && echo B) || (echo C && echo D)"
../rshell << EOF
(echo A && echo B) || (echo C && echo D)
echo "exit"; exit
EOF

printf "\n\nTest 2 : ((echo A && echo B) || (echo C && echo D)) && echo E"
../rshell << EOF
((echo A && echo B) || (echo C && echo D)) && echo E
echo "exit"; exit
EOF

printf "\n\nTest 3 : (echo A && echo B);"
../rshell << EOF
(echo A && echo B);
echo "exit"; exit
EOF

printf "\n\nTest 4 : echo A || ((echo B && echo C && echo D && echo E)) && echo F"
../rshell << EOF
echo A || ((echo B && echo C && echo D && echo E)) && echo F
echo "exit"; exit
EOF

printf "\n\nTest 5 : echo A && (echo B && (echo F || echo G) && echo C && echo E && echo C) && echo D"
../rshell << EOF
echo A && (echo B && (echo F || echo G) && echo C && echo E && echo C) && echo D
echo "exit"; exit
EOF

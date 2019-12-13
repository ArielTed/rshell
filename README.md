RSHELL
================

Fall 2019

Introduction
-------

***rshell*** is a command shell developped in C++ which is capable of performing the following steps:
* Print a command prompt
* Read in a line of command(s) (and connector(s)) from standard input
* Execute the appropriate commands using fork, execvp, and waitpid
* Repeat until an exit command is executed

Commands will have the following format (note that the square brackets represent optional portions of an input):
```
$ executable [argumentList] [connector] [executable] ...
```
where there can be any number of commands (which are composed of executables and argument lists) separated by connectors. The executable can be any executable program located at one of the PATH environment variable locations and the [argumentList] is a list of zero or more arguments separated by spaces.

It is designed with a composite pattern consisting of connector class (which acts as the composite class) and a command class (which acts as the leaf).

UML
-------

![Diagram](https://github.com/ArielTed/rshell/blob/master/images/OMT.png?raw=true)

Parsing
------------
I used string class from the C++ standard library to help me parse the user's string. Then I combined the Tokens to create both the Command's objects and Connector's objects.

![Diagram](https://github.com/ArielTed/rshell/blob/master/images/Tokens.png?raw=true)

Execute based on Tree Representation
------------
From there I construct an expression tree that will recursively call execute(), which will call execvp to run the specific commands and flags. Each iteration of a leaf will return a boolean value which will be evaluated by the connectors to determine whether the tree should travel to the right leaf or skip and return back up the tree.

![Diagram](https://github.com/ArielTed/rshell/blob/master/images/tree.png?raw=true)

and with Precedence Operator

![Diagram](https://github.com/ArielTed/rshell/blob/master/images/PrecedenceTree.png?raw=true)

Rshell Features
------------
**Can run most of bash commands**<br />

*Note: 'cd' command only affects the working directory of the current process, it doesn’t change the working directory of current shell. This means when you exit the program, you will be back to the directory you were before running rshell.*

<br />**Can support all connectors such as:**
* ";" = The following command will always be exectued.
* "||" = If the current command fails, the following command will be executed.
* "&&" = If the current command succeeds, the following command will be executed.
* "|" = General purpose process and command chaining tool.
* "<" = Accept input from a file.
* ">" = Redirect stdout to a file, creates the file if not present, otherwise overwrites it.
* ">>" = Redirect stdout to a file, creates the file if not present, otherwise appends to it.
* "#" = Everything after "#" will be a comment.

*Please note that there need to be a space after the semi-colon (;) connector and before and after the and (&&), or (||), pipe (|), input (<) and output (>, >>) connectors when entering commands.*

<br />**Can support precedences operators:** <br /><br />
So instead of
```
echo A && echo B || echo C && echo D which will yield :
A 
B 
D 
```
You can now do
```
(echo A && echo B) || (echo C && echo D) which will yield :
A 
B 
```

<br />**Can executes the test command by using "test" or "[ ]" with flags specified below:**
* if flag == -e it will be tested to see if it is either a directory or a regular file
* if flag == -f it will be tested to see if it is a regular file
* if flag == -d it will be tested to see if it is a directory
* if no flag is provided then -e will be assumed
test command will print out (true) and (false) based on returned boolean value respectively. <br />
Example: test -e main.cpp or [-e main.cpp] will return (true) or (false) based on whether main.cpp is in the current directory. <br />
Lastly the test command can be combined with other connectors discussed above.

<br />**User information:** <br /><br />
Instead of having a boring "$" before each command, the shell can print out your entire user's info.

For example, suppose your username is "Ariel", that you're logged into the machine named "MyPC" and that you are in the directory "src", the shell will prompt "[rshell Ariel@MyPC src]$ " on your terminal.

Test Scripts
--------
To test ***rshell*** I have created multiple unit tests, as well as testing scripts to ensure the program functions as expected.

To run the unit tests, enter the following:
```
./test
```

To run a script, navigate into the integration_tests/ directory and enter the following:
```
./<script_name>
```

List of available scripts:
```
single_command_tests.sh..................tests single commands
multiple_commands_tests.sh...............tests commands with connectors (;, &&, ||)
commented_command_tests.sh...............tests commands containing comments
exit_command_tests.sh....................tests exit and commands with exit
test_literal_tests.sh....................tests the literal test command
test_symbolic_tests.sh...................tests the symbolic test command
precedence_tests.sh......................tests the precedence operator
pipe_operator_tests.sh...................tests commands with pipe operator
input_redirection_tests.sh...............tests commands with input redirection
output_redirection_tests.sh..............tests commands with output redirection
```

Running rshell
--------
In order to run ***rshell***, open up your terminal and type these commands after navigating
to your desired directory.
```
1. git clone --recursive https://github.com/ArielTed/rshell.git
2. cd rshell
3. cmake .
4. make
5. ./rshell
```
Congratulations! ***rshell*** is running and you are now able to run BASH commands.

*To stop, use 'exit' command.*

Author
------------
**Ariel Tedgui** : https://github.com/ArielTed

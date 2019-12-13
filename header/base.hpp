#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <cstddef> 
#include <list>
#include <stack>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>

#include "parser.hpp"

class Base
{
    protected:
        Base* left;
        Base* right;
        std::vector<std::string> commands;
        bool executed;

    public:
        Base() 
        { 
            executed = false;
        }

        virtual ~Base() { }

        void setLeft(Base* left)
        {
            this->left = left;
        }

        void setRight(Base* right)
        {
            this->right = right;
        }

        bool wasExecuted()
        {
            return executed;
        }

        virtual std::vector<std::string> getCommands()
        {
            return commands;
        }

        virtual void Execute() = 0;
};

#endif

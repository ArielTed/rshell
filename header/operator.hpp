#ifndef __OPERATOR_HPP__
#define __OPERATOR_HPP__

#include "base.hpp"

class Operator : public Base
{
    public:
        Operator() : Base()
        {
            left = NULL;
            right = NULL;
        }
        Operator(Base* left, Base* right) : Base()
        {
            this->left = left;
            this->right = right;
        }

        ~Operator() { }
        
        virtual void Execute() = 0;
};

#endif

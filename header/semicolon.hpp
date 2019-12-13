#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include "operator.hpp"

class Semicolon : public Operator
{
    public:
        Semicolon() : Operator() { }
        Semicolon(Base* left, Base* right) : Operator(left, right) { }
        
        ~Semicolon() 
        {
            delete left;
            delete right;
        }

        virtual void Execute()
        {
            left->Execute();
            
            if (right != NULL)
            {
                right->Execute();

                if (right->wasExecuted())
                    executed = true;
            }
        }
};

#endif

#ifndef __AND_HPP__
#define __AND_HPP__

#include "operator.hpp"

class And : public Operator
{
    public:
        And() : Operator() { }
        And(Base* left, Base* right) : Operator(left, right) { }
        
        ~And() 
        {
            delete left;
            delete right;
        }

        virtual void Execute()
        {
            left->Execute();
            
            if (left->wasExecuted())
                right->Execute();

            if (right->wasExecuted())
                executed = true;
        }
};

#endif

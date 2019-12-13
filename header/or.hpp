#ifndef __OR_HPP__
#define __OR_HPP__

#include "operator.hpp"

class Or : public Operator
{
    public:
        Or() : Operator() { }
        Or(Base* left, Base* right) : Operator(left, right) { }
        
        ~Or() 
        {
            delete left;
            delete right;
        }

        virtual void Execute()
        {
            left->Execute();
            
            if (!left->wasExecuted())
                right->Execute();

            if (left->wasExecuted() || right->wasExecuted())
                executed = true;
        }
};

#endif

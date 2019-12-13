#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "operator.hpp"

class Input : public Operator
{
    public:
        Input() : Operator() { }
        Input(Base* left, Base* right) : Operator(left, right) { }
        
        ~Input() 
        {
            delete left;
            delete right;
        }

        virtual void Execute()
        {            
            pid_t pid = fork();

            if (pid == -1)
            {
                perror("Fork failed");
                exit(-1);
            }
            else if (pid == 0)
            {
		        close(0);
                open(right->getCommands()[0].c_str(), O_RDONLY);
		
		        left->Execute();

                if (left->wasExecuted())
			        exit(0);

		        exit(1);
            }
            else if (pid > 0)
            {
                int status;
                if (waitpid(pid, &status, WCONTINUED) == -1)
                {
                    perror("Child failed");
                    exit(-1);
                }
                if (status == 0)
                    executed = true;
            }
        }
};

#endif

#ifndef __OUTPUT_HPP__
#define __OUTPUT_HPP__

#include "operator.hpp"

class Output : public Operator
{
    private:
        std::string type;

    public:
        Output(std::string type) : Operator() 
        { 
            this->type = type;
        }
        Output(std::string type, Base* left, Base* right) : Operator(left, right) 
        { 
            this->type = type;
        }
        
        ~Output() 
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
		        close(1);

		        if (type == ">")
		        {
			        open(right->getCommands()[0].c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0664);
		        }
		        else
		        {
			        open(right->getCommands()[0].c_str(), O_CREAT | O_WRONLY, 0664);
			        lseek(1, 0, SEEK_END);
		        }
                
                left->Execute();

		        if(left->wasExecuted())
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

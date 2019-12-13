#ifndef __PIPE_HPP__
#define __PIPE_HPP__

#include "operator.hpp"

class Pipe : public Operator
{
    public:
        Pipe() : Operator() { }
        Pipe(Base* left, Base* right) : Operator(left, right) { }
        
        ~Pipe() 
        {
            delete left;
            delete right;
        }

        virtual void Execute()
        {
            int fds[2];
	        pipe(fds);
	
            pid_t pid = fork();
            
            if (pid == -1)
            {
                perror("Fork failed");
                exit(-1);
            }
            else if (pid == 0)
            {
		        close(fds[0]);
		        dup2(fds[1], 1);

		        left->Execute();

		        close(1);

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
		        {
			        close(fds[1]);

			        pid_t pid2 = fork();

			        if (pid2 == -1)
			        {
				        perror("Fork failed");
                        exit(-1);
			        }
			        else if (pid2 == 0)
			        {
				        dup2(fds[0], 0);

				        right->Execute();

				        close(0);

				        if(right->wasExecuted())
				            exit(0);
				        
				        exit(1);
			        }
			        else if (pid2 > 0)
			        {
				        if (waitpid(pid2, &status, WCONTINUED) == -1)
				        {
					        perror("Child failed");
                            exit(-1);
				        }
				        if (status == 0)
					        executed = true;
			        }
		        }
            }
        }
};

#endif

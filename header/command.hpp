#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include "base.hpp"

class Command : public Base
{
    private:
        std::string input;

    public:
        Command() : Base() { }
        Command(std::string input) : Base()
        {
            this->input = input;
            split(input, commands);
            for (int i = 0; i < commands.size(); i++)
            {
                if (commands[i].front() == '"')
                    commands[i].erase(commands[i].begin() + 0);
                if (commands[i].back() == '"')
                    commands[i].pop_back();
            }
        }

        ~Command() { }

        virtual void Execute()
        {
            if (commands[0] == "exit")
                exit(0);
            else if (commands[0] == "test" || commands[0] == "[")
            {
                if (commands.size() > 1)
                {
                    bool exist = false;
                    struct stat buf;
                    if (commands.size() > 2)
                    {
                        if (commands[1] == "-e")
                        {
                            if (stat(commands[2].c_str(), &buf) == 0)
                            {
                                exist = true;
                            }
                        }
                        else if (commands[1] == "-f")
                        {
                            if (stat(commands[2].c_str(), &buf) == 0)
                            {
                                if (S_ISREG(buf.st_mode))
                                {
                                    exist = true;
                                }
                            }
                        }
                        else if (commands[1] == "-d")
                        {
                            if (stat(commands[2].c_str(), &buf) == 0)
                            {
                                if (S_ISDIR(buf.st_mode))
                                {
                                    exist = true;
                                }
                            }
                        }
                        else
                        {
                            if (stat(commands[1].c_str(), &buf) == 0 && commands[2] == "]")
                            {
                                exist = true;
                            }
                        }
                    }
                    else
                    {
                        if (stat(commands[1].c_str(), &buf) == 0)
                        {
                            exist = true;
                        }
                    }

                    if (exist)
                    {
                        std::cout << "(True)\n";
                    }
                    else std::cout << "(False)\n";
                }
                else
                {
                    std::cout << "Please specify an argument for the test command.\n";
                }
                executed = true;
            }
            else if (commands[0] == "cd")
            {
                std::string directory;

                for (int i = 1; i < commands.size(); i++)
                {
                    directory += commands[i] + " ";
                }
                while (directory.back() == ' ')
                    directory.pop_back();

                if (chdir(directory.c_str()) == -1)
                    perror("Error");
                else executed = true;
            }
            else
            {
                char* args[commands.size() + 1];
                for (int i = 0; i < commands.size(); i++)
                {
                    args[i] = (char*)commands[i].c_str();
                    args[i] += '\0';
                }
                args[commands.size()] = NULL;

                pid_t pid = fork();  
                                      
                if (pid == -1) 
                {                             
                    perror("Fork failed");
                    exit(-1);                         
                }
                else if (pid == 0) 
                {
                    if (execvp(args[0], args) == -1) 
                    {       
                        perror("Execution failed");
                        exit(1);
                    }
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
        }        
};

#endif

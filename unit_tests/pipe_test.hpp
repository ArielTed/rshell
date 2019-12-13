#ifndef __PIPE_TEST_HPP__
#define __PIPE_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/pipe.hpp"
#include "../header/command.hpp"
#include "../header/parser.hpp"

TEST(PipeClassSet, ExecuteTest)
{
    std::string str = "ls -l | grep -i \"ma\"";

    std::vector<std::string> tokens = Parser(str);

    Command* cmd1 = new Command(tokens[0]);
    Command* cmd2 = new Command(tokens[2]);
    Pipe* pipe = new Pipe(cmd1, cmd2);

    pipe->Execute();

    EXPECT_TRUE(pipe->wasExecuted() == true);

    delete pipe;
}

#endif

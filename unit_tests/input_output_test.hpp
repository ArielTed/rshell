#ifndef __INPUT_OUTPUT_TEST_HPP__
#define __INPUT_OUTPUT_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/input.hpp"
#include "../header/output.hpp"
#include "../header/command.hpp"
#include "../header/parser.hpp"

TEST(InputOutputClassSet, ExecuteTest)
{
    std::string str = "ls -l > testfile.txt";

    std::vector<std::string> tokens = Parser(str);

    Command* cmd1 = new Command(tokens[0]);
    Command* cmd2 = new Command(tokens[2]);
    Output* output = new Output(">", cmd1, cmd2);

    output->Execute();

    EXPECT_TRUE(output->wasExecuted() == true);

    str = "cat < testfile.txt";

    tokens = Parser(str);

    cmd1 = new Command(tokens[0]);
    cmd2 = new Command(tokens[2]);
    Input* input = new Input(cmd1, cmd2);

    input->Execute();

    EXPECT_TRUE(input->wasExecuted() == true);

    str = "rm testfile.txt";

    tokens = Parser(str);

    Command* cmd = new Command(tokens[0]);

    cmd->Execute();

    delete input;
    delete output;
}

#endif

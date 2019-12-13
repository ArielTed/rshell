#ifndef __OR_TEST_HPP__
#define __OR_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/or.hpp"
#include "../header/command.hpp"
#include "../header/parser.hpp"

TEST(OrClassSet, ExecuteTest1)
{
    std::string str = "echo test || echo test";

    std::vector<std::string> tokens = Parser(str);

    Command* cmd1 = new Command(tokens[0]);
    Command* cmd2 = new Command(tokens[2]);
    Or* _or = new Or(cmd1, cmd2);

    _or->Execute();

    EXPECT_TRUE(_or->wasExecuted() == true);

    delete _or;
}

TEST(OrClassSet, ExecuteTest2)
{
    std::string str = "ech test || ech test";

    std::vector<std::string> tokens = Parser(str);

    Command* cmd1 = new Command(tokens[0]);
    Command* cmd2 = new Command(tokens[2]);
    Or* _or = new Or(cmd1, cmd2);

    _or->Execute();

    EXPECT_TRUE(_or->wasExecuted() == false);

    delete _or;
}

#endif

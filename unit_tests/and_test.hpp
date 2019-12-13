#ifndef __AND_TEST_HPP__
#define __AND_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/and.hpp"
#include "../header/command.hpp"
#include "../header/parser.hpp"

TEST(AndClassSet, ExecuteTest1)
{
    std::string str = "echo test && echo test";

    std::vector<std::string> tokens = Parser(str);

    Command* cmd1 = new Command(tokens[0]);
    Command* cmd2 = new Command(tokens[2]);
    And* _and = new And(cmd1, cmd2);

    _and->Execute();
    
    EXPECT_TRUE(_and->wasExecuted() == true);

    delete _and;
}

TEST(AndClassSet, ExecuteTest2)
{
    std::string str = "ech test && echo test";

    std::vector<std::string> tokens = Parser(str);

    Command* cmd1 = new Command(tokens[0]);
    Command* cmd2 = new Command(tokens[2]);
    And* _and = new And(cmd1, cmd2);

    _and->Execute();

    EXPECT_TRUE(_and->wasExecuted() == false);

    delete _and;
}

#endif

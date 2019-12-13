#ifndef __SEMICOLON_TEST_HPP__
#define __SEMICOLON_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/semicolon.hpp"
#include "../header/command.hpp"
#include "../header/parser.hpp"

TEST(SemicolonClassSet, ExecuteTest1)
{
    std::string str = "echo test; echo test";

    std::vector<std::string> tokens = Parser(str);

    Command* cmd1 = new Command(tokens[0]);
    Command* cmd2 = new Command(tokens[2]);
    Semicolon* semicolon = new Semicolon(cmd1, cmd2);

    semicolon->Execute();

    EXPECT_TRUE(semicolon->wasExecuted() == true);

    delete semicolon;
}

TEST(SemicolonClassSet, ExecuteTest2)
{
    std::string str = "echo test; ech test";

    std::vector<std::string> tokens = Parser(str);

    Command* cmd1 = new Command(tokens[0]);
    Command* cmd2 = new Command(tokens[2]);
    Semicolon* semicolon = new Semicolon(cmd1, cmd2);

    semicolon->Execute();

    EXPECT_TRUE(semicolon->wasExecuted() == false);

    delete semicolon;
}

#endif

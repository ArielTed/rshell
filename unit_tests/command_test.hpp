#ifndef __COMMAND_TEST_HPP__
#define __COMMAND_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/command.hpp"

TEST(CommandClassSet, ExecuteTest)
{
    Command* cmd = new Command("echo hello");

    cmd->Execute();

    EXPECT_TRUE(cmd->wasExecuted() == true);

    delete cmd;
}

TEST(CommandClassSet, TestCommandTest)
{
    Command* cmd = new Command("test -e header");

    cmd->Execute();

    EXPECT_TRUE(cmd->wasExecuted() == true);

    delete cmd;
}

#endif

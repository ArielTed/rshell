#ifndef __PARSER_TEST_HPP__
#define __PARSER_TEST_HPP__

#include "gtest/gtest.h"

#include "../header/parser.hpp"

TEST(ParserTestSet, SingleCommandTest) 
{
    std::string str = "ls -a";

    std::vector<std::string> tokens = Parser(str);

    EXPECT_EQ(tokens[0], "ls -a");
}

TEST(ParserTestSet, MultipleCommandsTest) 
{
    std::string str = "ls -a; echo hello; mkdir test";

    std::vector<std::string> tokens = Parser(str);

    EXPECT_EQ(tokens[0], "ls -a");
    EXPECT_EQ(tokens[1], ";");
    EXPECT_EQ(tokens[2], "echo hello");
    EXPECT_EQ(tokens[3], ";");
    EXPECT_EQ(tokens[4], "mkdir test");
}

TEST(ParserTestSet, VariousConnectorsTest) 
{
    std::string str = "ls -a; echo hello && mkdir test || echo world; git status";

    std::vector<std::string> tokens = Parser(str);

    EXPECT_EQ(tokens[0], "ls -a");
    EXPECT_EQ(tokens[1], ";");
    EXPECT_EQ(tokens[2], "echo hello");
    EXPECT_EQ(tokens[3], "&&");
    EXPECT_EQ(tokens[4], "mkdir test");
    EXPECT_EQ(tokens[5], "||");
    EXPECT_EQ(tokens[6], "echo world");
    EXPECT_EQ(tokens[7], ";");
    EXPECT_EQ(tokens[8], "git status");
}

TEST(ParserTestSet, CommentTest) 
{
    std::string str = "ls #-lR /";

    std::vector<std::string> tokens = Parser(str);

    EXPECT_EQ(tokens[0], "ls");
    ASSERT_EQ(tokens.size(), 1);
}

TEST(ParserTestSet, QuotesTest) 
{
    std::string str = "echo \"hello && goodbye\"";

    std::vector<std::string> tokens = Parser(str);

    EXPECT_EQ(tokens[0], "echo \"hello && goodbye\"");
}

TEST(ParserTestSet, ParenthesesTest) 
{
    std::string str = "echo A && (echo B && (echo F || echo G) && echo C && echo E && echo C) && echo D";

    std::vector<std::string> tokens = Parser(str);

    EXPECT_EQ(tokens[0], "echo A");
    EXPECT_EQ(tokens[1], "&&");
    EXPECT_EQ(tokens[2], "(echo B && (echo F || echo G) && echo C && echo E && echo C)");
    EXPECT_EQ(tokens[3], "&&");
    EXPECT_EQ(tokens[4], "echo D");
}

TEST(ParserTestSet, GlobalTest) 
{
    std::string str = "echo \"hello && goodbye\" || (git status && git add *) && mkdir test || echo world; #This is a comment";

    std::vector<std::string> tokens = Parser(str);

    EXPECT_EQ(tokens[0], "echo \"hello && goodbye\"");
    EXPECT_EQ(tokens[1], "||");
    EXPECT_EQ(tokens[2], "(git status && git add *)");
    EXPECT_EQ(tokens[3], "&&");
    EXPECT_EQ(tokens[4], "mkdir test");
    EXPECT_EQ(tokens[5], "||");
    EXPECT_EQ(tokens[6], "echo world");
    EXPECT_EQ(tokens[7], ";");
    ASSERT_EQ(tokens.size(), 8);
}

#endif

#include "gtest/gtest.h"

#include "parser_test.hpp"
#include "semicolon_test.hpp"
#include "and_test.hpp"
#include "or_test.hpp"
#include "pipe_test.hpp"
#include "input_output_test.hpp"
#include "command_test.hpp"

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include "c-echo.h"

#include "gtest/gtest.h"

TEST(EchoTest, HelloWorld) {
    char* test_val[3]; test_val[0] = "./c-echo"; test_val[1] = "hello"; test_val[2] = "world";
    EXPECT_EQ("hello world", echo(3,test_val));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(EchoTest, EmptyString) {
    char* test_val[1]; test_val[0] = "./c-echo";
    EXPECT_EQ("", echo(1,test_val));
}

TEST(EchoTest, LongString) {
  char* test_val[6]; test_val[0] = "./c-echo"; test_val[1] = "This"; test_val[2] = "is"; test_val[3] = "a"; test_val[4] = "long"; test_val[5] = "sentence";

  EXPECT_EQ("This is a long sentence", echo(6, test_val);
}

TEST(EchoTest, OneValue) {
    char* test_val[2]; test_val[0] = "./c-echo"; test_val[1] = "Single";
    EXPECT_EQ("Single", echo(2,test_val));
}

TEST(EchoTest, Number) {
    char* test_val[2]; test_val[0] = "./c-echo"; test_val[1] = "10";
    EXPECT_EQ("10", echo(2,test_val));
}

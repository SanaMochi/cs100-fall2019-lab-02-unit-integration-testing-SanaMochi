#include "c-echo.h"

#include "gtest/gtest.h"

TEST(EchoTest, EmptyString) {
    char* test_val[1]; test_val[0] = "./c-echo";
    EXPECT_EQ("", echo(1,test_val));
}

TEST(EchoTest, LongSentence) {
    char* test_val[3]; test_val[0] = "./c-echo"; test_val[1] = "I'm"; test_val[2] = "done";
    EXPECT_EQ("I'm done", echo(3,test_val));
}

TEST(EchoTest, OneValue) {
    char* test_val[2]; test_val[0] = "./c-echo"; test_val[1] = "Single";
    EXPECT_EQ("Single", echo(2,test_val));
}

TEST(EchoTest, Number) {
    char* test_val[2]; test_val[0] = "./c-echo"; test_val[1] = "10";
    EXPECT_EQ("10", echo(2,test_val));
}


TEST(EchoTest, HelloWorld) {
    char* test_val[3]; test_val[0] = "./c-echo"; test_val[1] = "hello"; test_val[2] = "world";
    EXPECT_EQ("hello world", echo(3,test_val));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

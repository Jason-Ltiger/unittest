#include <gtest/gtest.h>
bool Add(int a, int b)
{
    if (a == 0 || b == 0)
    {
        throw "don't do that";
    }
    int c = a % b;
    if (c == 0)
        return true;
    return false;
}

TEST(ADDTestThrow, HandleNoneZeroInput)
{
    EXPECT_TRUE(Add(4, 2)) << "该文件不是json文件json文件json文件";
    EXPECT_TRUE(Add(0, 0)) << "该文件不是json文件";
}
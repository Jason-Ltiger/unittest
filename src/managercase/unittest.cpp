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
    EXPECT_TRUE(Add(4, 2)) << "���ļ�����json�ļ�json�ļ�json�ļ�";
    EXPECT_TRUE(Add(0, 0)) << "���ļ�����json�ļ�";
}
#include<iostream>
#include<gtest/gtest.h>
#include "managercase/TestManager.h"

bool Foo(int a,int b)
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

TEST(FooTest, HandleNoneZeroInput)
{
    EXPECT_TRUE(Foo(4,2)) << "该文件不是json文件json文件json文件";
    EXPECT_TRUE(Foo(0,0)) << "该文件不是json文件";
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}




#if 0
struct LinkNode
{
    int _data;
    LinkNode* _next;
    LinkNode(const int& data)
        :_data(data)
        , _next(NULL)
    {}
};

class Link
{
public:
    Link()
        :pHead(new LinkNode(0))
    {}
    void PushBack(const int& data)
    {
        if (pHead == NULL)
            return;
        LinkNode* newNode = new LinkNode(data);
        if (pHead->_next == NULL) {  //第一次插入结点
            pHead->_next = newNode;
        }
        else {  //找到最后一个结点直接尾插
            LinkNode* cur = pHead->_next;
            while (cur->_next) {
                cur = cur->_next;
            }
            cur->_next = newNode;
        }
    }

    void PopBack()
    {
        if (pHead == NULL)
            return;
        LinkNode* cur = pHead;
        LinkNode* prev = NULL;
        while (cur->_next)
        {
            prev = cur;
            cur = cur->_next;
        }
        prev->_next = NULL;
        delete cur;
    }

    LinkNode* FindNode(const int& data)
    {
        if (pHead == NULL)
            return NULL;
        LinkNode* cur = pHead->_next;
        while (cur)
        {
            if (cur->_data == data)
                return cur;
            cur = cur->_next;
        }
        return NULL;
    }

    bool Delete(int data)
    {
        LinkNode* pos = FindNode(data);
        if (pos == NULL)
            return false;
        LinkNode* cur = pHead->_next;
        while (cur->_next != pos)
        {
            cur = cur->_next;
        }
        cur->_next = pos->_next;
        delete pos;
        return true;
    }

    void Destroy()
    {
        if (pHead == NULL)
            return;
        LinkNode* cur = pHead->_next;
        while (cur)
        {
            LinkNode* del = cur;
            cur = cur->_next;
            delete del;
            del = NULL;
        }
        delete pHead;  //删除头结点
    }
    LinkNode* pHead;
};

class TestLink :public testing::Test
{
public:
    virtual void SetUp()
    {
        cout << "SetUp" << endl;
        for (int i = 1; i <= 5; i++) {
            link.PushBack(i);
        }
    }
    virtual void TearDown()
    {
        cout << "TearDown" << endl;
        link.Destroy();
    }
    Link link;
};

TEST_F(TestLink, PushBack)
{
    ASSERT_FALSE(link.pHead == NULL);
    link.PushBack(9);
    LinkNode* res = link.FindNode(9);
    ASSERT_FALSE(res == NULL);
}

TEST_F(TestLink, PopBack)
{
    for (int i = 1; i <= 5; i++) {
        link.PopBack();
    }
}

TEST_F(TestLink, FindNode)
{
    ASSERT_TRUE(link.FindNode(3));
    ASSERT_TRUE(link.FindNode(2));
    ASSERT_TRUE(link.FindNode(4));
    ASSERT_TRUE(link.FindNode(5));
    ASSERT_TRUE(link.FindNode(1));
    ASSERT_FALSE(link.FindNode(7));
}

TEST_F(TestLink, Delete)
{
    ASSERT_FALSE(link.pHead == NULL);
    ASSERT_TRUE(link.Delete(3) == true);
    ASSERT_TRUE(link.Delete(9) == false);
}
#endif

//  断言的使用
#if 0
int Add(int a, int b)
{
    return a + b;
}
bool MutuallyPrime(int m, int n)
{
    return Add(m, n) < 1;
}

TEST(PredicateAssertionTest, Demo)
{
    int m = 5, n = 6;
    EXPECT_PRED2(MutuallyPrime, m, n);
}
testing::AssertionResult AssertFoo(const char* m_expr, const char* n_expr, const char* k_expr, int m, int n, int k) {
    if (Add(m, n) == k)
        return testing::AssertionSuccess();
    testing::Message msg;
    msg << m_expr << " 和 " << n_expr << " 的最大公约数应该是：" << Add(m, n) << " 而不是：" << k_expr;
    return testing::AssertionFailure(msg);
}

TEST(AssertFooTest, HandleFail)
{
    EXPECT_PRED_FORMAT3(AssertFoo, 3, 6, 2);
}

#endif


#if 0
template <typename T> class FooType {
public:
    void Bar() {
        testing::StaticAssertTypeEq<bool, T>();
    }
};

TEST(TypeAssertionTest, Demo)
{
    FooType<int> fooType;
    fooType.Bar();
}


bool IsPrime(int n)
{
    if (n <= 1) return false;
    if (n % 2 == 0) return n == 2;
    for (int i = 3; ; i += 2) {
        if (i > n / i) break;

        if (n % i == 0) return false;
    }
    return true;
}

class IsPrimeParamTest : public::testing::TestWithParam<int>
{

};

TEST_P(IsPrimeParamTest, HandleTrueReturn)
{
    int n = GetParam();
    EXPECT_TRUE(IsPrime(n));
}

INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, testing::Values(3, 5, 11, 23, 17));

typedef testing::Types<char, int, unsigned int> MyTypes;

#endif



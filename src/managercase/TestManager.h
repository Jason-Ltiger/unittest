#include "TestCase_Base.h"
#include<iostream>
#include<vector>
class TestManager
{
public:
    // 获取单例
    static TestManager* GetInstance();

    // 注册测试案例
    TestCase_Base* RegisterTestCase(TestCase_Base* testcase);

    // 执行单元测试
    int Run();

    TestCase_Base* CurrentTestCase; // 记录当前执行的测试案例
    int nTestResult; // 总的执行结果
    int nPassed; // 通过案例数
    int nFailed; // 失败案例数
protected:
    std::vector<TestCase_Base*> testcases_; // 案例集合
};

// 框架的调用
#define RUN_ALL_TESTS_CASE() \
    TestManager::GetInstance()->Run();


#include "TestCase_Base.h"
#include<iostream>
#include<vector>
class TestManager
{
public:
    // ��ȡ����
    static TestManager* GetInstance();

    // ע����԰���
    TestCase_Base* RegisterTestCase(TestCase_Base* testcase);

    // ִ�е�Ԫ����
    int Run();

    TestCase_Base* CurrentTestCase; // ��¼��ǰִ�еĲ��԰���
    int nTestResult; // �ܵ�ִ�н��
    int nPassed; // ͨ��������
    int nFailed; // ʧ�ܰ�����
protected:
    std::vector<TestCase_Base*> testcases_; // ��������
};

// ��ܵĵ���
#define RUN_ALL_TESTS_CASE() \
    TestManager::GetInstance()->Run();


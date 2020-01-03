
class TestCase_Base
{
public:
    TestCase_Base(const char* case_name) : testcase_name(case_name) {}
    ~TestCase_Base() {};
    // ִ�в��԰����ķ���
    virtual void Run() = 0;

    int nTestResult; // ���԰�����ִ�н�� 
    const char* testcase_name; // ���԰�������
};


// ���Ժ�
#define TESTCASE_NAME(testcase_name) \
    testcase_name##_TEST

#define NANCY_TEST_(testcase_name) \
class TESTCASE_NAME(testcase_name) : public TestCase_Base \
{ \
    public: \
    TESTCASE_NAME(testcase_name)(const char* case_name) : TestCase_Base(case_name){}; \
    virtual void Run(); \
private: \
    static TestCase_Base* const testcase_; \
}; \
\
TestCase_Base* const TESTCASE_NAME(testcase_name) \
    ::testcase_ = TestManager::GetInstance()->RegisterTestCase( \
        new TESTCASE_NAME(testcase_name)(#testcase_name)); \
void TESTCASE_NAME(testcase_name)::Run()

#define NTEST(testcase_name) \
    NANCY_TEST_(testcase_name)
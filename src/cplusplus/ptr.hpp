
#include <memory>
#include <iostream>

class Foo{

public:
    Foo() = default;
    Foo(int a):_a(a) {}
    ~Foo() {}
    int get_a(){
        return _a;
    }
    void set_a(int a) {
        _a = a;
    }
private:
    int _a;

};

//调用这个函数要std::move 引用过去。
std::unique_ptr<Foo> change_a(std::unique_ptr<Foo> f)
{
    //这段代码在return 时候就做了 转移 转到了std::unique_ptr<food>上。  
    f->set_a(10);
    return f;
}
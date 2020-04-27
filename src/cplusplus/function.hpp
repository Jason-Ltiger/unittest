

#include<string>
#include <iostream>
#include <memory>
#include <functional>

#define print(x)  std::cout<< x << std::endl

struct Food{
    Food(int num):f_num(num){}
    void print_food(int i)const {std::cout << f_num + i <<std::endl;}
    int f_num;  
};


int printing(int value1){
     print(value1);
    return value1;
}

void function(){

    //存储自由函数------------
    //std::function<void(int)>_print(print);
    //存储lamda表达式---------
    std::function<int(void)>l_print([](void){return 20;});
    print(l_print());
    //存储std::binding调用结果
    std::function<int()> b_print = std::bind(printing,12306);
    b_print();
    //存储成员函数的调用
    std::function<void (const Food&,int)> s_print = & Food::print_food;
    Food _food(100);
    s_print(_food,1);
    // 重要的函数使用方法！！！-----------------------------------
    std::function<void(int)> f_add_display2 = std::bind( &Food::print_food, _food, std::placeholders::_1 );
    f_add_display2(2);

}

void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

void bind(){
    using namespace std::placeholders;  
    int n = 7;
    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
    n = 10;
    f1(1, 2, 1001);
}

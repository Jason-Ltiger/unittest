//std:array
#include <iostream>
#include <array>
#include<vector>
#include<algorithm>
void array(){
    
    //声明字符数组std::array<int,128>;
    std::array<int, 10> arr = {1,2,3,4,5,6,7,8,9,0};
    std::for_each(arr.begin(), arr.end(), [](int &i){i++;});
    for(auto& i : arr){std::cout << i << " ";};

    //清空字符数组memset
    std::array<char, 128> result_str { '1' ,'2','3'} ;
    std::cout<<"个数："<<sizeof(result_str)<<std::endl;
    memset(&result_str, '\0', sizeof(result_str));


}
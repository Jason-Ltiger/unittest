#include <iostream>
#include <array>
#include <memory>

static int ExecuteSystemCmd(const char * cmd, std::array<char,128>& result_str) {
	std::unique_ptr<FILE,decltype(&pclose)> pipe(popen(cmd,"r"),pclose);
	if(!pipe){
		throw std::runtime_error("popen failed");
		return -1;
	}
	while(::fgets(result_str.data(),result_str.size(),pipe.get()) != nullptr){
		std::cout << "pipe result :" << result_str.data();
	}
	return 0;
}
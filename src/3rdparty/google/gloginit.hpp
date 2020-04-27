
#include <glog/logging.h>
void InitGlog(char* argv[]) {

    FLAGS_logtostderr = 1;   //调试信息是否全部输出到控制台而非日志文件
    FLAGS_minloglevel = 0;  //设定日志信息输出最小级别
    google::SetStderrLogging(google::FATAL);  //设置级别高于FATAL的输出到控制台
    google::InitGoogleLogging(argv[0]);//初始化glog日志系统

}

int main(int argc, char** argv)  
{	
    InitGlog(argv);
    LOG(INFO) << "本机IP：" ;
    return 0;
}
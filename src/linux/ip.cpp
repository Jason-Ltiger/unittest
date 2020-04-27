
#include <string>
#include <iostream>
#include <vector>
#include <glog/logging.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <json/json.h>

void IP(){
    struct ifaddrs* ifAddrStruct = NULL;
    void* tmpAddrPtr = NULL;
    getifaddrs(&ifAddrStruct);
    std::string local_ip("");
    std::string ipv4_lo("127.0.0.1");
    while (ifAddrStruct != NULL)
    {
        if (ifAddrStruct->ifa_addr->sa_family == AF_INET)
        {
            tmpAddrPtr = &((struct sockaddr_in*)ifAddrStruct->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            LOG(INFO) << ifAddrStruct->ifa_name << " IPV4 Address" << addressBuffer;
            std::string ipv4(addressBuffer);
            if (std::string::npos == ipv4.find(ipv4_lo))
            {
                local_ip = ipv4;
                LOG(INFO) << "本机IP：" << ipv4;
            }
        }
        else if (ifAddrStruct->ifa_addr->sa_family == AF_INET6)
        {
            tmpAddrPtr = &((struct sockaddr_in*)ifAddrStruct->ifa_addr)->sin_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            LOG(INFO) << ifAddrStruct->ifa_name << " IPV6 Address" << addressBuffer;
        }
        ifAddrStruct = ifAddrStruct->ifa_next;
    }
    freeifaddrs(ifAddrStruct);
    Json::Value j_val;
    j_val["reply"] = "welcome";
    j_val["my_name"] = "RC";
    j_val["ip"] = local_ip;
    j_val["port"] = "4567";

}

void InitGlog(char* argv[]) {

    FLAGS_logtostderr = 1;   //调试信息是否全部输出到控制台而非日志文件
    FLAGS_minloglevel = 0;  //设定日志信息输出最小级别
    google::SetStderrLogging(google::FATAL);  //设置级别高于FATAL的输出到控制台
    google::InitGoogleLogging(argv[0]);//初始化glog日志系统

}

int main(int argc, char** argv)  
{	
    InitGlog(argv);
    IP();
    return 0;
}



#include <vector>
#include <net/if.h>
#include <glog/logging.h>
#include<stdio.h>
#include <sys/ioctl.h>
#include <bits/ioctls.h>
// 获取mac 地址：
       int macadress(int argc, char *argv[])
       {
           
        int sock_mac;         
        struct ifreq ifr_mac;  
        char mac_addr[30];     
          
        sock_mac = socket( AF_INET, SOCK_STREAM, 0 );  
        if( sock_mac == -1)  
        {  
            perror("create socket falise...mac/n");  
            return -1;  
        }  
          
        memset(&ifr_mac,0,sizeof(ifr_mac));     
        strncpy(ifr_mac.ifr_name, "ens33", sizeof(ifr_mac.ifr_name)-1);     
      
        if( (ioctl( sock_mac, SIOCGIFHWADDR, &ifr_mac)) < 0)  
        {  
            printf("mac ioctl error/n");  
            return -1;  
        }    
          
        sprintf(mac_addr,"%02x%02x%02x%02x%02x%02x",  
                (unsigned char)ifr_mac.ifr_hwaddr.sa_data[0],  
                (unsigned char)ifr_mac.ifr_hwaddr.sa_data[1],  
                (unsigned char)ifr_mac.ifr_hwaddr.sa_data[2],  
                (unsigned char)ifr_mac.ifr_hwaddr.sa_data[3],  
                (unsigned char)ifr_mac.ifr_hwaddr.sa_data[4],  
                (unsigned char)ifr_mac.ifr_hwaddr.sa_data[5]);  
      
        printf("local mac:%s /n",mac_addr);      
          
        close( sock_mac );  
           exit(EXIT_SUCCESS);
       }
       // 获取ip、mac地址
void DispNetInfo(const char* szDevName)
 {
    // std::cout <<"excess successs" <<std::endl;
    // //读取硬盘序列号
    // struct hd_driveid id;
    // std::string hd_str;
    // int fd = open("/dev/sda", O_RDONLY | O_NONBLOCK);
    // if (fd < 0) {
    //     LOG(WARNING) << "can not open sda file" ;
    //     return;
    // }
    // std::cout <<"open success" <<std::endl;
    // if (ioctl(fd, HDIO_GET_IDENTITY, &id) < 0)  return;
    // std::cout << id.serial_no<<hd_str<<std::endl;
    // std::string tmp_str(std::begin(id.serial_no), std::end(id.serial_no));
    // hd_str = std::move(tmp_str);
    // std::cout << "硬盘的序列号："<<hd_str<<std::endl;
    
 }

// 获取网卡数量
int GetNetCardCount()
{
    int nCount = 0;
    FILE* f = fopen("/proc/net/dev", "r");
    if (!f)
    {
        fprintf(stderr, "Open /proc/net/dev failed!errno:%d\n", errno);
        return nCount;
    }

    char szLine[512];

    fgets(szLine, sizeof(szLine), f);    /* eat line */
    fgets(szLine, sizeof(szLine), f);

    while(fgets(szLine, sizeof(szLine), f))
    {
        char szName[128] = {0};
        sscanf(szLine, "%s", szName);
        int nLen = strlen(szName);
        if (nLen <= 0)continue;
        if (szName[nLen - 1] == ':') szName[nLen - 1] = 0;
        if (strcmp(szName, "lo") == 0)continue;
        nCount++;
    }

    fclose(f);
    f = NULL;
    return nCount;
}

void InitGlog(char* argv[]) {

    FLAGS_logtostderr = 1;   //调试信息是否全部输出到控制台而非日志文件
    FLAGS_minloglevel = 0;  //设定日志信息输出最小级别
    google::SetStderrLogging(google::FATAL);  //设置级别高于FATAL的输出到控制台
    google::InitGoogleLogging(argv[0]);//初始化glog日志系统

}

//获取硬盘序列号
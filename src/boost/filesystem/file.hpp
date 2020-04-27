#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/trim.hpp>

#define print(x)  std::cout<< x << std::endl


//判断文件是否存在及子文件的判定
bool exitfile(const std::string& pathstr){

    constexpr const char* PROJECT_SETTING_FOLDER_PATH = ".settings";
    boost::filesystem::path path(pathstr);
    return  boost::filesystem::is_directory(path);
}


// 非常好的容错型代码
bool creatfile(const std::string &folder_path, bool remove_exist_file)
{
    if (create_folder_path.empty()) {
        LOG(ERROR) << "Create folder failed, empty path";
        return false;
    }

    if(exitfile(folder_path))
       return true;


    // Trim last '/'
    if (create_folder_path.size() != 1
        && *create_folder_path.rbegin() == '/') {
        create_folder_path.erase(create_folder_path.size() - 1);
    }

    try {
        bfs::path path(bfs::absolute(bfs::path(create_folder_path)));
        bool exists_log_folder(bfs::exists(path));

        if (remove_exist_file && exists_log_folder && !bfs::is_directory(path)) {
            // Remove if log folder exists but isn't directory
            bfs::remove(path);
            bfs::create_directories(path);
            LOG(WARNING) << "Create folder success, Removed duplicate name file[" << folder_path << "]";
        } else if (!exists_log_folder) {
            // Create log folder
            if (!bfs::create_directories(path)) {
                // Man, we're screwed!
            }
        }

        // Set folder permissions
        if (bfs::status(path).permissions() != bfs::owner_all) {
            bfs::permissions(path, bfs::owner_all);
        }
        return true;

    } catch (const bfs::filesystem_error &fe) {
        LOG(ERROR) << "Create folder[" << folder_path << "] failed, err:" << fe.what();
    } catch (...) {
        LOG(ERROR) << "Create folder[" << folder_path << "] failed, unknow err";
    }

    return false;
}

std::string GetLastFolderName(const std::string& path) {
    //伪代码如下：
    /*如果传入的path是以 ‘/’结尾，name需要两次trim/
    如果传入的path是以普通字符结尾，则给末尾增加‘ / ’，再处理。*/
    if (path.empty()) return "";
    std::string  lname_str;
    std::string  sla_str = "/";
    //记录倒数第1个"/"出现的位置
    int p_slash = static_cast<int>(path.find_last_of('/'));
    if (p_slash != static_cast<int>(path.length() - 1))
    {
        lname_str = path.substr(p_slash + 1, path.length() - p_slash);
        return lname_str;
    }
    //记录倒数第二次出现"/"的位置
    int index = 0;
    while (static_cast<int>(path.find(sla_str, index)) < p_slash)
    {
        index = static_cast<int>(path.find(sla_str, index));
        index++;
    }
    lname_str = path.substr(index, p_slash - index);
    boost::trim(lname_str);
    return lname_str;
}

//往文件里写数字  libconfig的格式
bool ConfigManager::createDefaultConfig() {
    std::ofstream cfgFile;
    cfgFile.open(m_fileName);
    if (cfgFile.is_open()) {
        cfgFile << cfg::updateAvailable << " = false;" << std::endl;
        cfgFile << cfg::currentFolder << " = \"./\";" << std::endl;
        cfgFile << cfg::targetFolder << " = \"./\";" << std::endl;
        cfgFile << cfg::updateFolder << " = \"./upgrade/\";" << std::endl;
        cfgFile << cfg::port << " = 4567;" << std::endl;
        cfgFile << cfg::version << " = \"3.2.1\";" << std::endl;
        cfgFile << cfg::mainProgramName << " = \"xCore\";" << std::endl;
        cfgFile.close();
        return true;
    } else
        return false;
}



//    libconfig++.a 库和 头文件需要添加
// 读取文件内容libconfig的格式
int ConfigManager::loadConfigFile()
{
    //https://blog.csdn.net/cjf_wei/article/details/55670577
    try {
        config.readFile(m_fileName.c_str()); //尝试读取文件，判断文件格式是否正确
    } catch (const FileIOException& fioex) {
        LOG(ERROR) << "File I/O error" ;
        return (EXIT_FAILURE);
    } catch (const ParseException& pex) {
        LOG(ERROR) << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError();
        return (EXIT_FAILURE);
    }
    return 0;
}


// 文件的hash值

void fileMD5(){

    std::array<char,128> result_str; 
    constexpr const char* linux_cmd = "md5sum -b build/unittest" ;
    ExecuteSystemCmd("pwd",result_str);
    ExecuteSystemCmd(linux_cmd,result_str);
    std::array<char,32> target{'\0'}; 
    std::copy(result_str.begin(),result_str.begin()+31,target.begin());
    std::string resi_str(result_str.data(),32);

    print(resi_str);
}

// 递归遍历文件目录的指针，找到对应合适的目录
void remove(){
    typedef fs::recursive_directory_iterator dir_iter;
    std::list<std::string> dump_file_list;
    try {
        fs::path log_path(LOG_FOLDER);
        if (!fs::is_directory(log_path)) {
            return;
        }

        fs::path absoulte_path(log_path);
        dir_iter cur_iter(absoulte_path), end_iter;
        while (cur_iter != end_iter) {
            const fs::path &filePath(cur_iter->path());

            if (fs::is_regular(filePath)
                && boost::istarts_with(filePath.filename().string(), DUMP_FILE_NAME)) {
                dump_file_list.push_back(filePath.string());
            }

            cur_iter++;
        }
    } catch (const fs::filesystem_error &fe) {
        return;
    }
}
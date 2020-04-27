
// #include <zipper/unzipper.h>  //    libZipper-static.a z
// #include <zipper/zipper.h>

// 对文件的操作尽量加上安全检查
// bool Utility::ExtractFile(std::string path)
// {
//     //未做容错！ 需要优化
//     if ("" == path) path = DEFAULT_FILE;

//     try
//     {
//         zipper::Unzipper unzipper(path);  //支持密码解压缩
//         unzipper.extract();
//         unzipper.close();
//     }
//     catch (...)
//     {
//         LOG(WARNING) << "升级文件不存在";
//     }
// }
//代码规范
#ifndef SRC_USER_LOG_USER_LOG_HPP_
#define SRC_USER_LOG_USER_LOG_HPP_

#include <string>
#include <memory>

class UserLogContext;

namespace user_log {

/**
 * @brief 初始化日志模块
 */
bool InitUserLogModule();

/**
 * @brief 反初始化日志模块
 */
void DeinitUserLogModule();

/**
 * @brief 报告用户日志
 * @param  log_code_NO：日志编号
 * @param  args：参数，用以替换日志产生原因中的$atg
 */
void ReportUserLog(int log_code_NO, std::string args = "");

/**
 * @brief 根据告警号码查询告警详情
 * @param  log_code_NO：告警号码
 * @return 返回UserLogContext的智能指针
 */
std::shared_ptr<UserLogContext> QueryUserLog(int log_code_NO);
} /* namespace user_log */

#endif //SRC_USER_LOG_USER_LOG_HPP_
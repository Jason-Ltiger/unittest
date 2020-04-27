#ifndef SRC_UTILS_LOGGER_LOGGER_HPP_
#define SRC_UTILS_LOGGER_LOGGER_HPP_

namespace logger {

/**
 * @brief Log启动器
 *        构造阶段初始化log配置，析构阶段反初始化log配置
 */
class SingletonBase;
class LogInitiator;
#define DECLARE_SINGLETON(x) x
class LogInitiator final : public SingletonBase<LogInitiator> {
    DECLARE_SINGLETON(LogInitiator);

  private:
    LogInitiator();

    ~LogInitiator();

    /**
     * @brief 初始化
     */
    void Init();

    /**
     * @brief 反初始化
     */
    void Deinit();
};

} /* namespace logger */

#endif /* SRC_UTILS_LOGGER_LOGGER_HPP_ */
#ifndef SRC_UTILS_SINGLETON_HPP_
#define SRC_UTILS_SINGLETON_HPP_
#include "noncopyable.hpp"

/**
 * @brief 单例基类
 *        定义单例时，配合DECLARE_SINGLETON宏一起使用
 * @example
 *      class object : public utils::SingletonBase<object> {
 *          DECLARE_SINGLETON(object);
 *      };
 */
namespace utils {

template <typename T>
class SingletonBase : public utils::noncopyable {
    typedef T* SingletonPtr;
    typedef T  SingletonType;

    public:
        inline static SingletonPtr GetInstance() {
            if (!instance) {
                instance = new SingletonType();
            }
            return instance;
        }

        inline static void ReleaseInstance() {
            if (!instance) return;
            delete instance;
            instance = nullptr;
        }

    protected:
        SingletonBase() {}

        virtual ~SingletonBase() {}

    private:
        static SingletonPtr instance;
};

template <typename T>
T* SingletonBase<T>::instance;

} /* namespace utils */

#define DECLARE_SINGLETON( type ) \
    friend class utils::SingletonBase< type >

#define SINGLETON_INSTANCE( type ) \
    type::GetInstance()

#define INIT_SINGLETON( type ) \
    SINGLETON_INSTANCE(type)

#define DESTROY_INSTANCE( type ) \
    type::ReleaseInstance()

using utils::SingletonBase;

#endif /* SRC_UTILS_SINGLETON_HPP_ */

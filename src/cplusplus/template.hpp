#include "noncopyable.hpp"

template<typename T>
class ValueRetriever : public noncopyable {
 public:
    ValueRetriever(T &dist, const T &source) :
        D(dist), S(source) {
    }

    ~ValueRetriever() {
        D = S;
    }

 private:
    T &D;
    const T &S;
};
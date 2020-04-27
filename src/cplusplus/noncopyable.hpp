#pragma once

namespace utils {

namespace base {
class noncopyable {
  protected:
    noncopyable() = default;

    ~noncopyable() = default;

    noncopyable(const noncopyable &) = delete;

    noncopyable &operator=(const noncopyable &) = delete;

};

class nonmoveable {
  protected:
    nonmoveable() = default;

    ~nonmoveable() = default;

    nonmoveable(nonmoveable&&) = delete;

    nonmoveable& operator=(nonmoveable&&) = delete;
};
}/* namespace utils */
}/* namespace utils */
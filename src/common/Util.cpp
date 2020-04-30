#include "Util.hpp"

template <typename T> bool Util::existsInVector(T str, std::vector<T> vec) {
    return std::find(vec.begin(), vec.end(), str) != vec.end();
}
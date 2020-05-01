#pragma once
#include <vector>
#include <algorithm>

namespace Util{
    template <typename T>
    bool existsInVector(T element, std::vector<T> vec) {
        return std::find(vec.begin(), vec.end(), element) != vec.end();
    }
}

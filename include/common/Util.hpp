#pragma once
#include <vector>
#include <algorithm>

namespace Util{
    template <typename T>
    inline bool existsInVector(T element, std::vector<T> vec) {
        return std::find(vec.begin(), vec.end(), element) != vec.end();
    }

    inline std::string getStringAfterLastDelimiter(std::string str, std::string delimiter) {
        std::string s = str;

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
        }

        return s;
    }
}

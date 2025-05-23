#pragma once
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "types.h"

namespace Util
{
    template <typename T>
    inline bool existsInVector(T element, std::vector<T> vec)
    {
        return std::find(vec.begin(), vec.end(), element) != vec.end();
    }

    template <typename T>
    inline int findIndexOfVectorElement(T element, std::vector<T> vec)
    {
        auto it = find(vec.begin(), vec.end(), element);
        // If element was found
        if (it != vec.end())
        {
            int index = it - vec.begin();
            return index;
        }

        return -1;
    }

    inline std::string getStringAfterLastDelimiter(std::string str, std::string delimiter)
    {
        std::string s = str;

        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
        }

        return s;
    }

    inline glm::vec4 formatRGB(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.0f)
    {
        GLfloat formattedRed = red / 255;
        GLfloat formattedGreen = green / 255;
        GLfloat formattedBlue = blue / 255;

        return glm::vec4(formattedRed, formattedGreen, formattedBlue, alpha);
    }
}

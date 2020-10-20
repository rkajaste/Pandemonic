#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

struct TileLocationInfo {
    glm::vec2 coords;
    int gid;
};

struct TilesetAnimation {
    int frameCount;
    float animationSpeed;
    std::vector<int> tileIds;
};

struct TilesetInfo {
    std::string name;
    int firstGid;
    int columns;
    int tileCount;
    std::vector<TilesetAnimation> animations;
};


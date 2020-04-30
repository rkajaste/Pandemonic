#pragma once
#include "Tmx.h"
#include <experimental/filesystem>
#include <iostream>
#include <vector>
#include "Util.hpp"

class MapManager {
    public:
        MapManager();
    private:
        std::string currentMap;
        std::vector<std::string> maps;
        std::vector<std::string> texturePaths;

        Tmx::Map* loadMap();
};
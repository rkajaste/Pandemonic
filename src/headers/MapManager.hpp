#pragma once
#include "Tmx.h"
#include <experimental/filesystem>
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include "Util.hpp"
#include "ResourceManager.hpp"
#include "MapRenderer.hpp"

class MapManager {
    public:
        MapManager();
        ~MapManager();
        MapRenderer* renderer;
        GLfloat worldHeight;
    private:
        std::string currentMap;
        std::vector<std::string> maps;

        Tmx::Map* loadMap();
};
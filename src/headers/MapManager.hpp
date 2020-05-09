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

typedef std::tuple<int, std::__cxx11::string, int, int> TilesetInfo;
typedef std::pair<glm::vec2, int> TileCoordsAndGid;
class MapManager {
    public:
        static std::vector<std::string> getMaps();
        static std::vector<TilesetInfo> getTilesetInfo();
        static std::vector<TileCoordsAndGid> getTileCoordsAndGids();
        static GLfloat getWorldHeight();
        static std::string getCurrentMap();
        static void loadMap();
    private:
        static std::vector<std::string> maps;
        static std::vector<TilesetInfo> tilesetInfoArray;
        static std::vector<TileCoordsAndGid> tileCoordsAndGidArray;
        static GLfloat worldHeight;
        static std::string currentMap;
};
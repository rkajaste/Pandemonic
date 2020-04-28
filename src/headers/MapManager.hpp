#include "Tmx.h"
#include <experimental/filesystem>
#include <iostream>
#include <vector>

class MapManager {
    public:
        MapManager();
    private:
        std::string currentMap;
        std::vector<std::string> maps;

        Tmx::Map* loadMap();
};
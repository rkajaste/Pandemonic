#pragma once

#include "Tmx.h"
#include <experimental/filesystem>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

#include "types.hpp"
#include "Util.hpp"
#include "ResourceManager.hpp"
#include "MapRenderer.hpp"



typedef std::vector<const Tmx::Object*> MapObjects;

class MapManager {
    public:
        static std::vector<std::string> getMaps();
        static std::vector<TilesetInfo> getTilesetInfoArray();
        static std::vector<TileLocationInfo> getTileLocationInfoArray();
        static GLfloat getWorldHeight();
        static GLfloat getWorldWidth();
        static std::string getCurrentMap();

        static glm::vec2 getPlayerSpawnPoint(std::string name);
        static MapObjects getNpcObjects();
        static MapObjects getSavePointObjects();
        static MapObjects getTerrainObjects();
        static MapObjects getInteractionObjects();
        static MapObjects getLevelTransitionObjects();
        static MapObjects getDeathObjects();
        static void clearMapInfo();
        static void loadMap(std::string mapToLoad);

    private:
        static std::vector<std::string> maps;
        static std::vector<TilesetInfo> tilesetInfoArray;
        static std::vector<TileLocationInfo> tileLocationInfoArray;
        static GLfloat worldHeight;
        static GLfloat worldWidth;
        static std::string currentMap;
        static MapObjects playerObjects;
        static MapObjects npcObjects;
        static MapObjects savePointObjects;
        static MapObjects terrainObjects;
        static MapObjects interactionObjects;
        static MapObjects levelTransitionObjects;
        static MapObjects deathObjects;
};
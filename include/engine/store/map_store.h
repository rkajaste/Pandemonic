#pragma once

#include "Tmx.h"
#include <filesystem>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>

#include "types.h"
#include "util.h"
#include "resource_store.h"
#include "map_renderer.h"
#include "config.h"

typedef std::vector<const Tmx::Object *> MapObjects;

class MapStore {
    public:
        static void preload();
        static std::vector<std::string> getMaps();
        static std::vector<TilesetInfo> getTilesetInfoArray();
        static std::vector<TileLocationInfo> getTileLocationInfoArray();
        static std::vector<std::string> getVisibleLayers();
        static void setLayerVisibility(std::string, bool isVisible);

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
        
        // TODO: this is some strange method, get rid of it
        static void setCollisionContext(std::string interior);
        static std::string getCollisionContext();
    private:
        MapStore(){};
        
        static std::vector<std::string> maps;
        static std::vector<TilesetInfo> tilesetInfoArray;
        static std::vector<TileLocationInfo> tileLocationInfoArray;
        static std::vector<std::string> visibleLayers;

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

        static std::string collisionContext;
};

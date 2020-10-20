#include "MapManager.hpp"

namespace fs = std::experimental::filesystem;
const std::string mapsPath = std::string(PROJECT_SOURCE_DIR) + "/assets/tilemaps/";
const std::string assetsPath = std::string(PROJECT_SOURCE_DIR) + "/assets";

std::vector<std::string> MapManager::maps;
std::vector<TileLocationInfo> MapManager::tileLocationInfoArray;
std::vector<TilesetInfo> MapManager::tilesetInfoArray;
GLfloat MapManager::worldHeight;
GLfloat MapManager::worldWidth;
std::string MapManager::currentMap;
MapObjects MapManager::playerObjects;
MapObjects MapManager::npcObjects;
MapObjects MapManager::savePointObjects;
MapObjects MapManager::terrainObjects;
MapObjects MapManager::interactionObjects;
MapObjects MapManager::levelTransitionObjects;
MapObjects MapManager::deathObjects;

void MapManager::clearMapInfo()
{
    tileLocationInfoArray.clear();
    tilesetInfoArray.clear();
    playerObjects.clear();
    npcObjects.clear();
    savePointObjects.clear();
    terrainObjects.clear();
    interactionObjects.clear();
    levelTransitionObjects.clear();
    deathObjects.clear();
}

void MapManager::loadMap(std::string mapToLoad)
{
    clearMapInfo();

    Tmx::Map *map;
    map = new Tmx::Map();

    for (const auto & entry : fs::directory_iterator(mapsPath)) {
        if (entry.path().filename() != "world.world") {
            maps.push_back(entry.path().filename());
        }
    }

    currentMap = mapToLoad + ".tmx";

    map->ParseFile(mapsPath + currentMap);
    if (map->HasError())
    {
        printf("error code: %d\n", map->GetErrorCode());
        printf("error text: %s\n", map->GetErrorText().c_str());
    }

    worldHeight = map->GetHeight() * map->GetTileHeight();
    worldWidth = map->GetWidth() * map->GetTileWidth();

    const std::vector<Tmx::Tileset*> tilesets = map->GetTilesets();

    for (unsigned int i = 0; i < tilesets.size(); ++i) {
        Tmx::Tileset *tileset = tilesets.at(i);
        std::string imagePath = assetsPath + std::string(tileset->GetImage()->GetSource()).erase(0, 2);
        std::vector<TilesetAnimation> tilesetAnimations;

        if (tileset->GetTiles().size() > 0)
        {
            // Get all animated tiles from tileset
            const std::vector<Tmx::Tile *> &tiles = tileset->GetTiles();
            for (
                std::vector<Tmx::Tile *>::const_iterator currentTile = tiles.begin();
                currentTile != tiles.end();
                currentTile++
            ) 
            {
                if ((*currentTile)->IsAnimated())
                {
                    TilesetAnimation tilesetAnimation;
                    int frameCount = (*currentTile)->GetFrameCount();
                    float animationSpeed = (*currentTile)->GetTotalDuration() / (*currentTile)->GetFrameCount();
                    std::vector<int> tileIds;

                    const std::vector<Tmx::AnimationFrame> &frames = (*currentTile)->GetFrames();
                    for (
                        std::vector<Tmx::AnimationFrame>::const_iterator it = frames.begin();
                        it != frames.end();
                        it++
                    )
                    {
                        tileIds.push_back(it->GetTileID());
                    }
                    tilesetAnimation.frameCount = frameCount;
                    tilesetAnimation.animationSpeed = animationSpeed;
                    tilesetAnimation.tileIds = tileIds;
                    tilesetAnimations.push_back(tilesetAnimation);
                }
            }
        }
        TilesetInfo tilesetInfo;
        tilesetInfo.name = tileset->GetName();
        tilesetInfo.firstGid = tileset->GetFirstGid();
        tilesetInfo.columns = tileset->GetColumns();
        tilesetInfo.tileCount = tileset->GetTileCount();
        tilesetInfo.animations = tilesetAnimations;
        tilesetInfoArray.push_back(tilesetInfo);

        if (tilesetAnimations.empty()) {
            ResourceManager::LoadTexture(
                imagePath,
                tileset->GetName()
            );
        } else {
            ResourceManager::LoadTexture(
                imagePath,
                tileset->GetName(),
                0,
                tilesetAnimations.at(0).animationSpeed
            );
        }
    }

    for (int i = 0; i < map->GetNumTileLayers(); ++i)
    {
        const Tmx::TileLayer *tileLayer = map->GetTileLayer(i);

        for (int y = 0; y < tileLayer->GetHeight(); ++y)
        {
            for (int x = 0; x < tileLayer->GetWidth(); ++x)
            {
                if (tileLayer->GetTileTilesetIndex(x, y) != -1)
                {
                    TileLocationInfo tileLocationInfo;
                    tileLocationInfo.coords = glm::vec2(x, y);
                    tileLocationInfo.gid = tileLayer->GetTileGid(x, y);
                    tileLocationInfoArray.push_back(tileLocationInfo);
                }
            }
        }
    }
    for (int i = 0; i < map->GetNumObjectGroups(); ++i)
    {
        const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);
        const std::string objectLayer = objectGroup->GetName();
        for (int j = 0; j < objectGroup->GetNumObjects(); ++j)
        {

            const Tmx::Object *object = objectGroup->GetObject(j);

            if (objectLayer == "terrain") {
                if (object->GetName() == "blockers") {
                    terrainObjects.push_back(object);
                }
            } else if (objectLayer == "spawn_points") {
                if (object->GetName() == "player") {
                    playerObjects.push_back(object);
                }
            } else if (objectLayer == "level_transitions") {
                if (object->GetName() == "level") {
                    levelTransitionObjects.push_back(object);
                }
            } else if (objectLayer == "triggers") {
                if (object->GetName() == "npc") {
                    npcObjects.push_back(object);
                } else if (object->GetName() == "savepoint") {
                    savePointObjects.push_back(object);
                } else {
                    interactionObjects.push_back(object);
                }
            } else if (objectLayer == "death") {
                if (object->GetName() == "death") {
                    deathObjects.push_back(object);
                }
            }
        }
    }
}

std::vector<std::string> MapManager::getMaps()
{
    return maps;
}

std::vector<TileLocationInfo> MapManager::getTileLocationInfoArray()
{
    return tileLocationInfoArray;
}

std::vector<TilesetInfo> MapManager::getTilesetInfoArray()
{
    return tilesetInfoArray;
}

GLfloat MapManager::getWorldHeight()
{
    return worldHeight;
}

GLfloat MapManager::getWorldWidth()
{
    return worldWidth;
}

std::string MapManager::getCurrentMap()
{
    return currentMap;
}

glm::vec2 MapManager::getPlayerSpawnPoint(std::string name)
{
    glm::vec2 position;
    for(const auto& playerObject: playerObjects) {
        const std::string location = playerObject->GetProperties().GetStringProperty("location");
        if (location == name) {
            position = glm::vec2(playerObject->GetX(), playerObject->GetY() + playerObject->GetHeight());
        }
    };

    return position;
}

MapObjects MapManager::getNpcObjects()
{
    return npcObjects;
}

MapObjects MapManager::getSavePointObjects()
{
    return savePointObjects;
}

MapObjects MapManager::getTerrainObjects()
{
    return terrainObjects;
}

MapObjects MapManager::getInteractionObjects()
{
    return interactionObjects;
}

MapObjects MapManager::getLevelTransitionObjects()
{
    return levelTransitionObjects;
}

MapObjects MapManager::getDeathObjects()
{
    return deathObjects;
}

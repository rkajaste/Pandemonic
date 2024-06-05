#include "engine/store/map_store.h"

// undefine some Windows library functions to avoid name overlap at compile time
#undef GetObject

namespace fs = std::filesystem;
const std::string mapsPath;
const std::string assetsPath;

std::string MapStore::collisionContext = "";
std::vector<std::string> MapStore::maps;
std::vector<TileLocationInfo> MapStore::tileLocationInfoArray;
std::vector<TilesetInfo> MapStore::tilesetInfoArray;
std::vector<std::string> MapStore::visibleLayers;
GLfloat MapStore::worldHeight;
GLfloat MapStore::worldWidth;
std::string MapStore::currentMap;
MapObjects MapStore::playerObjects;
MapObjects MapStore::npcObjects;
MapObjects MapStore::savePointObjects;
MapObjects MapStore::terrainObjects;
MapObjects MapStore::interactionObjects;
MapObjects MapStore::levelTransitionObjects;
MapObjects MapStore::deathObjects;


void MapStore::setCollisionContext(std::string newContext)
{
    collisionContext = newContext;
}

std::string MapStore::getCollisionContext()
{
    return collisionContext;
}

void MapStore::clearMapInfo()
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
    visibleLayers.clear();
}

void MapStore::loadMap(std::string mapToLoad)
{
    const std::string mapsPath = Config::getRootDirectory() + "/assets/tilemaps/";
    const std::string assetsPath = Config::getRootDirectory() + "/assets";
    clearMapInfo();

    Tmx::Map *map;
    map = new Tmx::Map();

    for (const auto &entry : fs::directory_iterator(mapsPath))
    {
        if (entry.path().filename().string() != "world.world")
        {
            maps.push_back(entry.path().filename().string());
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

    const std::vector<Tmx::Tileset *> tilesets = map->GetTilesets();

    for (unsigned int i = 0; i < tilesets.size(); ++i)
    {
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
                currentTile++)
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
                        it++)
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

        if (tilesetAnimations.empty())
        {
            ResourceStore::LoadTexture(
                imagePath,
                tileset->GetName());
        }
        else
        {
            ResourceStore::LoadTexture(
                imagePath,
                tileset->GetName(),
                0,
                tilesetAnimations.at(0).animationSpeed);
        }
    }

    for (int i = 0; i < map->GetNumTileLayers(); ++i)
    {
        const Tmx::TileLayer *tileLayer = map->GetTileLayer(i);

        if (tileLayer->IsVisible())
        {
            visibleLayers.push_back(tileLayer->GetName());
        }

        for (int y = 0; y < tileLayer->GetHeight(); ++y)
        {
            for (int x = 0; x < tileLayer->GetWidth(); ++x)
            {
                if (tileLayer->GetTileTilesetIndex(x, y) != -1)
                {
                    TileLocationInfo tileLocationInfo;
                    tileLocationInfo.coords = glm::vec2(x, y);
                    tileLocationInfo.gid = tileLayer->GetTileGid(x, y);
                    tileLocationInfo.layer = tileLayer->GetName();
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

            if (objectLayer == "terrain")
            {
                if (object->GetName() == "blocker")
                {
                    terrainObjects.push_back(object);
                }
            }
            else if (objectLayer == "spawn_points")
            {
                if (object->GetName() == "player")
                {
                    playerObjects.push_back(object);
                }
            }
            else if (objectLayer == "level_transitions")
            {
                if (object->GetName() == "level")
                {
                    levelTransitionObjects.push_back(object);
                }
            }
            else if (objectLayer == "triggers")
            {
                if (object->GetName() == "npc")
                {
                    npcObjects.push_back(object);
                }
                else if (object->GetName() == "savepoint")
                {
                    savePointObjects.push_back(object);
                }
                else
                {
                    interactionObjects.push_back(object);
                }
            }
            else if (objectLayer == "death")
            {
                if (object->GetName() == "death")
                {
                    deathObjects.push_back(object);
                }
            }
        }
    }
}

std::vector<std::string> MapStore::getMaps()
{
    return maps;
}

std::vector<TileLocationInfo> MapStore::getTileLocationInfoArray()
{
    return tileLocationInfoArray;
}

std::vector<TilesetInfo> MapStore::getTilesetInfoArray()
{
    return tilesetInfoArray;
}

GLfloat MapStore::getWorldHeight()
{
    return worldHeight;
}

GLfloat MapStore::getWorldWidth()
{
    return worldWidth;
}

std::string MapStore::getCurrentMap()
{
    return currentMap;
}

std::vector<std::string> MapStore::getVisibleLayers()
{
    return visibleLayers;
}

void MapStore::setLayerVisibility(std::string layer, bool isVisible)
{
    if (isVisible)
    {
        if (!Util::existsInVector(layer, visibleLayers))
        {
            visibleLayers.push_back(layer);
        }
    }
    else
    {
        if (Util::existsInVector(layer, visibleLayers))
        {
            int index = Util::findIndexOfVectorElement(layer, visibleLayers);
            visibleLayers.erase(visibleLayers.begin() + index);
        }
    }
}

glm::vec2 MapStore::getPlayerSpawnPoint(std::string name)
{
    glm::vec2 position;
    for (const auto &playerObject : playerObjects)
    {
        const std::string location = playerObject->GetProperties().GetStringProperty("location");
        if (location == name)
        {
            position = glm::vec2(playerObject->GetX(), playerObject->GetY() + playerObject->GetHeight());
        }
    };

    return position;
}

MapObjects MapStore::getNpcObjects()
{
    return npcObjects;
}

MapObjects MapStore::getSavePointObjects()
{
    return savePointObjects;
}

MapObjects MapStore::getTerrainObjects()
{
    return terrainObjects;
}

MapObjects MapStore::getInteractionObjects()
{
    return interactionObjects;
}

MapObjects MapStore::getLevelTransitionObjects()
{
    return levelTransitionObjects;
}

MapObjects MapStore::getDeathObjects()
{
    return deathObjects;
}

#include "MapManager.hpp"

namespace fs = std::experimental::filesystem;
const std::string mapsPath = std::string(PROJECT_SOURCE_DIR) + "/assets/tilemaps/";
const std::string assetsPath = std::string(PROJECT_SOURCE_DIR) + "/assets";

std::vector<std::string> MapManager::maps;
std::vector<TileCoordsAndGid> MapManager::tileCoordsAndGidArray;
std::vector<TilesetInfo> MapManager::tilesetInfoArray;
GLfloat MapManager::worldHeight;
GLfloat MapManager::worldWidth;
std::string MapManager::currentMap;
MapObjects MapManager::playerObjects;
MapObjects MapManager::npcObjects;
MapObjects MapManager::savePointObjects;
MapObjects MapManager::terrainObjects;
MapObjects MapManager::interactionObjects;

void MapManager::loadMap()
{
    Tmx::Map *map;
    map = new Tmx::Map();

    // TODO
    for (const auto & entry : fs::directory_iterator(mapsPath)) {
        if (entry.path().filename() != "world.world") {
            maps.push_back(entry.path().filename());
        }
    }

    currentMap = "home_village.tmx";

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

        ResourceManager::LoadTexture(
            imagePath,
            tileset->GetName()
        );

        TilesetInfo tilesetInfo;
        tilesetInfo["firstGid"] = std::to_string(tileset->GetFirstGid());
        tilesetInfo["name"] = tileset->GetName();
        tilesetInfo["columns"] = std::to_string(tileset->GetColumns());
        tilesetInfo["tileCount"] = std::to_string(tileset->GetTileCount());

        tilesetInfoArray.push_back(tilesetInfo);
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
                    std::pair<glm::vec2, int> tileGidCoordsPair (
                        glm::vec2(x, y),
                        tileLayer->GetTileGid(x, y)
                    );
                    tileCoordsAndGidArray.push_back(tileGidCoordsPair);
                            // if (tile->IsAnimated())
                            // {
                            //     printf(
                            //             "Tile is animated: %d frames with total duration of %dms.\n",
                            //             tile->GetFrameCount(), tile->GetTotalDuration());

                            //     const std::vector<Tmx::AnimationFrame> &frames =
                            //             tile->GetFrames();

                            //     int i = 0;
                            //     for (std::vector<Tmx::AnimationFrame>::const_iterator it =
                            //             frames.begin(); it != frames.end(); it++, i++)
                            //     {
                            //         printf("\tFrame %d: Tile ID = %d, Duration = %dms\n", i,
                            //                 it->GetTileID(), it->GetDuration());
                            //     }
                            // }
                }
            }
        }
    }
    for (int i = 0; i < map->GetNumObjectGroups(); ++i)
    {
        const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);

        for (int j = 0; j < objectGroup->GetNumObjects(); ++j)
        {

            const Tmx::Object *object = objectGroup->GetObject(j);

            if (object->GetName() == "player") {
                playerObjects.push_back(object);
            } else if (object->GetName() == "triggers") {
                interactionObjects.push_back(object);
            } else if (object->GetName() == "npc") {
                npcObjects.push_back(object);
            } else if (object->GetName() == "savepoint") {
                savePointObjects.push_back(object);
            } else if (object->GetName() == "blockers") {
                terrainObjects.push_back(object);
            }
        }
    }
}

std::vector<std::string> MapManager::getMaps()
{
    return maps;
}

std::vector<TileCoordsAndGid> MapManager::getTileCoordsAndGidArray()
{
    return tileCoordsAndGidArray;
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

glm::vec2 MapManager::getPlayerSpawnPoint()
{
    glm::vec2 position;
    for(const auto& playerObject: playerObjects) {
        position = glm::vec2(playerObject->GetX(), playerObject->GetY() + playerObject->GetHeight());
    };
    printf("Object Position: (%03f, %03f)\n", position.x, position.y);
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



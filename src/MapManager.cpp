#include "MapManager.hpp"

namespace fs = std::experimental::filesystem;
const std::string mapsPath = std::string(PROJECT_SOURCE_DIR) + "/assets/tilemaps/";
const std::string assetsPath = std::string(PROJECT_SOURCE_DIR) + "/assets";

std::vector<std::string> MapManager::maps;
std::vector<TileCoordsAndGid> MapManager::tileCoordsAndGidArray;
std::vector<TilesetInfo> MapManager::tilesetInfoArray;
GLfloat MapManager::worldHeight;
std::string MapManager::currentMap;


void MapManager::loadMap()
{
    Tmx::Map *map;
    map = new Tmx::Map();

    for (const auto & entry : fs::directory_iterator(mapsPath))
        maps.push_back(entry.path().filename());
    currentMap = "1.tmx";

    map->ParseFile(mapsPath + currentMap);
    if (map->HasError())
    {
        printf("error code: %d\n", map->GetErrorCode());
        printf("error text: %s\n", map->GetErrorText().c_str());
    }

    worldHeight = map->GetHeight() * map->GetTileHeight();

    const std::vector<Tmx::Tileset*> tilesets = map->GetTilesets();
    std::vector<std::tuple<int, std::string, int, int>> tilesetInfoList;
    std::vector<std::pair<glm::vec2, int>> tileGids;
    // pair image source path and first tile gid
    for (unsigned int i = 0; i < tilesets.size(); ++i) {
        Tmx::Tileset *tileset = tilesets.at(i);
        std::string imagePath = assetsPath + std::string(tileset->GetImage()->GetSource()).erase(0, 2);

        ResourceManager::LoadTexture(
            imagePath,
            tileset->GetName()
        );
        std::tuple<int, std::string, int, int> tilesetInfo (
            tileset->GetFirstGid(),
            tileset->GetName(),
            tileset->GetColumns(),
            tileset->GetTileCount()
        );
        tilesetInfoArray.push_back(tilesetInfo);
        delete tileset;
    }

    // Iterate through the tile layers.
    for (int i = 0; i < map->GetNumTileLayers(); ++i)
    {
        // Get a layer.
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
                        // if tileset image not loaded yet, add to list
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
                            // // Iterate through all Collision objects in the tile.
                            // for (int j = 0; j < tile->GetNumObjects(); ++j)
                            // {
                            //     // Get an object.
                            //     const Tmx::Object *object = tile->GetObject(j);

                            //     // Print information about the object.
                            //     printf("Object Name: %s\n", object->GetName().c_str());
                            //     printf("Object Position: (%03d, %03d)\n", object->GetX(),
                            //         object->GetY());
                            //     printf("Object Size: (%03d, %03d)\n", object->GetWidth(),
                            //         object->GetHeight());
                            // }
                }
            }
        }
        delete tileLayer;
        printf("\n");
    }
    // Iterate through all of the object groups.
    for (int i = 0; i < map->GetNumObjectGroups(); ++i)
    {
        printf("                                    \n");
        printf("====================================\n");
        printf("Object group : %02d\n", i);
        printf("====================================\n");

        // Get an object group.
        const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);

        // Iterate through all objects in the object group.
        for (int j = 0; j < objectGroup->GetNumObjects(); ++j)
        {
            // Get an object.
            const Tmx::Object *object = objectGroup->GetObject(j);

            // Print information about the object.
            printf("Object Name: %s\n", object->GetName().c_str());
            printf("Object Position: (%03d, %03d)\n", object->GetX(),
                    object->GetY());
            printf("Object Size: (%03d, %03d)\n", object->GetWidth(),
                    object->GetHeight());

            if(object->GetGid() != 0) {
              printf("Object(tile) gid: %d\n", object->GetGid());
              printf("Object(tile) type: %s\n", object->GetType().c_str());
            }

        }
    }
}

std::vector<std::string> MapManager::getMaps()
{
    return MapManager::maps;
}

std::vector<TileCoordsAndGid> MapManager::getTileCoordsAndGids()
{
    return tileCoordsAndGidArray;
}

std::vector<TilesetInfo> MapManager::getTilesetInfo()
{
    return tilesetInfoArray;
}

GLfloat MapManager::getWorldHeight()
{
    return worldHeight;
}

std::string MapManager::getCurrentMap()
{
    return currentMap;
}

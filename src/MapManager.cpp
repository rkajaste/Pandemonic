#include "MapManager.hpp"

namespace fs = std::experimental::filesystem;
static const std::string mapsPath = std::string(PROJECT_SOURCE_DIR) + "/assets/tilemaps/";
MapManager::MapManager() {
    for (const auto & entry : fs::directory_iterator(mapsPath))
        this->maps.push_back(entry.path().filename());
    this->currentMap = "1.tmx";
    this->loadMap();
}

Tmx::Map* MapManager::loadMap() {
    Tmx::Map *map;
    map = new Tmx::Map();
    map->ParseFile(mapsPath + this->currentMap);

    if (map->HasError())
    {
        printf("error code: %d\n", map->GetErrorCode());
        printf("error text: %s\n", map->GetErrorText().c_str());
    }

    printf("====================================\n");
    printf("Map\n");
    printf("====================================\n");
    printf("Version: %1.1f\n", map->GetVersion());
    printf("Orientation: %d\n", map->GetOrientation());
    printf("Render Order: %d\n", map->GetRenderOrder());
    printf("Width: %d\n", map->GetWidth());
    printf("Height: %d\n", map->GetHeight());
    printf("Tile Width: %d\n", map->GetTileWidth());
    printf("Tile Height: %d\n", map->GetTileHeight());
    // Iterate through the tile layers.
    for (int i = 0; i < map->GetNumTileLayers(); ++i)
    {
        printf("                                    \n");
        printf("====================================\n");
        printf("Layer : %02d/%s \n", i, map->GetTileLayer(i)->GetName().c_str());
        printf("====================================\n");

        // Get a layer.
        const Tmx::TileLayer *tileLayer = map->GetTileLayer(i);

        for (int y = 0; y < tileLayer->GetHeight(); ++y)
        {
            for (int x = 0; x < tileLayer->GetWidth(); ++x)
            {
                if (tileLayer->GetTileTilesetIndex(x, y) != -1)
                {
                    const unsigned int tileGid = tileLayer->GetTileGid(x, y);
                    const Tmx::Tileset *tileset = map->FindTileset(tileGid);
                    //const Tmx::Tile *tile = tileLayer->GetTile(tileLayer->GetTileId(x, y));
                    std::string imagePath = std::string(PROJECT_SOURCE_DIR) +
                                            std::string(tileset->GetImage()->GetSource())
                                            .erase(0, 2);
                    if(tileset != NULL && !Util::existsInVector(imagePath, this->texturePaths)){
                        printf("%s%d\n", "TileCount:", tileset->GetTileCount());
                        // if tileset image not loaded yet, add to list
                        this->texturePaths.push_back(imagePath);
                        printf("%s", imagePath.c_str());
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
            }

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

    return map;
}

#include "MapLoader.hpp"

int MapLoader::loadMap() {
    Tmx::Map *map;
    map = new Tmx::Map();
    map->ParseFile("../assets/tilemaps/1.tmx");

    if (map->HasError())
    {
        printf("error code: %d\n", map->GetErrorCode());
        printf("error text: %s\n", map->GetErrorText().c_str());

        return map->GetErrorCode();
    }

    printf("====================================\n");
    printf("Map\n");
    printf("====================================\n");
    return 1;
}
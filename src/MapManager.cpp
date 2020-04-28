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
    // Iterate through map properties and print the type, name and value of each property.
    const std::unordered_map<std::string, Tmx::Property> &mapProperties = map->GetProperties().GetPropertyMap();
    for (auto &pair : mapProperties)
    {
        const Tmx::Property &property = pair.second;

        std::string type;

        if (property.GetType() == Tmx::TMX_PROPERTY_STRING)
        {
            type = "String";
        }
        else if (property.GetType() == Tmx::TMX_PROPERTY_FLOAT)
        {
            type = "Float";
        }
        else if (property.GetType() == Tmx::TMX_PROPERTY_INT)
        {
            type = "Integer";
        }
        else if (property.GetType() == Tmx::TMX_PROPERTY_BOOL)
        {
            type = "Boolean";
        }
        else if (property.GetType() == Tmx::TMX_PROPERTY_COLOR)
        {
            type = "Color";
        }
        else if (property.GetType() == Tmx::TMX_PROPERTY_FILE)
        {
            type = "File";
        }
        else
        {
            type = "Unknown";
        }

        printf("Map property %s (%s) = %s\n", pair.first.c_str(), type.c_str(),  property.GetValue().c_str());
    }
     for (int i = 0; i < map->GetNumTilesets(); ++i)
    {
        printf("                                    \n");
        printf("====================================\n");
        printf("Tileset : %02d\n", i);
        printf("====================================\n");

        // Get a tileset.
        const Tmx::Tileset *tileset = map->GetTileset(i);

        // Print tileset information.
        printf("Name: %s\n", tileset->GetName().c_str());
        printf("Margin: %d\n", tileset->GetMargin());
        printf("Spacing: %d\n", tileset->GetSpacing());
        printf("First gid: %d\n", tileset->GetFirstGid());
        printf("Image Width: %d\n", tileset->GetImage()->GetWidth());
        printf("Image Height: %d\n", tileset->GetImage()->GetHeight());
        printf("Image Source: %s\n", tileset->GetImage()->GetSource().c_str());
        if (!tileset->GetImage()->GetTransparentColor().IsTransparent())
            printf("Transparent Color (hex): %s\n",
                   tileset->GetImage()->GetTransparentColor().ToString().c_str());

        if (tileset->GetTiles().size() > 0)
        {
            // Get a tile from the tileset.
            const Tmx::Tile *tile = *(tileset->GetTiles().begin());

            // Print the properties of a tile.
            std::map<std::string, std::string> list =
                    tile->GetProperties().GetList();
            std::map<std::string, std::string>::iterator iter;
            for (iter = list.begin(); iter != list.end(); ++iter)
            {
                printf("%s = %s\n", iter->first.c_str(), iter->second.c_str());
            }

            if (tile->IsAnimated())
            {
                printf(
                        "Tile is animated: %d frames with total duration of %dms.\n",
                        tile->GetFrameCount(), tile->GetTotalDuration());

                const std::vector<Tmx::AnimationFrame> &frames =
                        tile->GetFrames();

                int i = 0;
                for (std::vector<Tmx::AnimationFrame>::const_iterator it =
                        frames.begin(); it != frames.end(); it++, i++)
                {
                    printf("\tFrame %d: Tile ID = %d, Duration = %dms\n", i,
                            it->GetTileID(), it->GetDuration());
                }
            }

            if(tile->HasObjects())
            {
                printf(
                        "Tile has objects.\n");

                if(tile->GetType() != "")
                    printf("Tile has type: %s\n", tile->GetType().c_str());

                // Iterate through all Collision objects in the tile.
                for (int j = 0; j < tile->GetNumObjects(); ++j)
                {
                    // Get an object.
                    const Tmx::Object *object = tile->GetObject(j);

                    // Print information about the object.
                    printf("Object Name: %s\n", object->GetName().c_str());
                    printf("Object Position: (%03d, %03d)\n", object->GetX(),
                           object->GetY());
                    printf("Object Size: (%03d, %03d)\n", object->GetWidth(),
                           object->GetHeight());

                    // Print Polygon points.
                    const Tmx::Polygon *polygon = object->GetPolygon();
                    if (polygon != 0)
                    {
                        for (int i = 0; i < polygon->GetNumPoints(); i++)
                        {
                            const Tmx::Point &point = polygon->GetPoint(i);
                            printf("Object Polygon: Point %d: (%f, %f)\n", i, point.x,
                                   point.y);
                        }
                    }

                    // Print Polyline points.
                    const Tmx::Polyline *polyline = object->GetPolyline();
                    if (polyline != 0)
                    {
                        for (int i = 0; i < polyline->GetNumPoints(); i++)
                        {
                            const Tmx::Point &point = polyline->GetPoint(i);
                            printf("Object Polyline: Point %d: (%f, %f)\n", i, point.x,
                                   point.y);
                        }
                    }
                }

            }
        }
    }
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
                    const Tmx::Tileset *tileset = map->GetTileset(tileLayer->GetTileTilesetIndex(x, y));
                    if(tileset != NULL) {
                        const Tmx::Tile *tile = tileset->GetTile(tileLayer->GetTileGid(x, y));
                        if (tile != NULL) {
                            const Tmx::Image *image = tile->GetImage();
                        }
                    }

                }
            }

            printf("\n");
        }
        printf("\n\n");
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

            // Print Polygon points.
            const Tmx::Polygon *polygon = object->GetPolygon();
            if (polygon != 0)
            {
                for (int i = 0; i < polygon->GetNumPoints(); i++)
                {
                    const Tmx::Point &point = polygon->GetPoint(i);
                    printf("Object Polygon: Point %d: (%f, %f)\n", i, point.x,
                            point.y);
                }
            }

            // Print Polyline points.
            const Tmx::Polyline *polyline = object->GetPolyline();
            if (polyline != 0)
            {
                for (int i = 0; i < polyline->GetNumPoints(); i++)
                {
                    const Tmx::Point &point = polyline->GetPoint(i);
                    printf("Object Polyline: Point %d: (%f, %f)\n", i, point.x,
                            point.y);
                }
            }

            // Print Text information
            const Tmx::Text *text = object->GetText();
            if(text != 0)
            {
                printf("--Object Text--\n");
                printf("Text contents: %s\n", text->GetContents().c_str());
                printf("Font family: %s\n", text->GetFontFamily().c_str());
                printf("Pixel size: %d\n", text->GetPixelSize());
                printf("Wraps: %d\n", text->Wraps());
                printf("Bold: %d, Italic: %d, Underline: %d, Strikeout: %d\n", text->IsBold(), text->IsItalic(),
                                                                             text->IsUnderline(), text->IsStrikeout());
                printf("Kerning: %d\n", text->UseKerning());
                printf("Horizontal ALignment: %d\n", text->GetHorizontalAlignment());
                printf("Vertical Alignment: %d\n", text->GetVerticalAlignment());
                printf("Color: %d, %d, %d, %d", text->GetColor()->GetRed(), text->GetColor()->GetGreen(),
                                                text->GetColor()->GetBlue(), text->GetColor()->GetAlpha());
            }
        }
    }
    // Iterate through all of the group layers.
    for(int i = 0; i < map->GetNumGroupLayers(); ++i) {
        printf("                                    \n");
        printf("====================================\n");
        printf("Group Layer : %02d/%s \n", i, map->GetGroupLayer(i)->GetName().c_str());
        printf("====================================\n");
        // Get a group layer.
        const Tmx::GroupLayer *groupLayer = map->GetGroupLayer(i);

        printf("Offset X: %d", groupLayer->GetOffsetX());
        printf("Offset Y: %d", groupLayer->GetOffsetY());
        printf("Number of Children: %d", groupLayer->GetNumChildren());

        for(int j = 0; j < groupLayer->GetNumChildren(); j++) {
          const Tmx::Layer *childLayer = groupLayer->GetChild(j);
          printf("Child Layer Name: %s\n", childLayer->GetName().c_str());
          printf("Child Layer Type: %02d\n", childLayer->GetLayerType());

          if(childLayer->GetLayerType() == Tmx::TMX_LAYERTYPE_GROUP_LAYER) {
            const Tmx::GroupLayer *childGroupLayer = static_cast<const Tmx::GroupLayer*>(childLayer);
            printf("  Child group layer number of children: %d\n", childGroupLayer->GetNumChildren());
            printf("  Child group layer first child name: %s\n", childGroupLayer->GetChild(0)->GetName().c_str());
            printf("  Child group layer first child type: %d\n", childGroupLayer->GetChild(0)->GetLayerType());
          }
        }
    }

    return map;
}

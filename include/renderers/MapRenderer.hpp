#pragma once
#include <vector>
#include <utility>
#include <tuple>
#include "Texture.hpp"
#include "Shader.hpp"
#include "ResourceManager.hpp"
#include "MapManager.hpp"

typedef std::map<std::string, std::string> TilesetInfo;
typedef std::pair<glm::vec2, int> TileCoordsAndGid;

class MapRenderer{
    public:
        MapRenderer(Shader);
        ~MapRenderer();

        void initRenderData();
        void drawMap();
    private:
        Shader shader;
        GLuint quadVAO;

        void drawTile(int index);
        TilesetInfo getTilesetInfoByGid(int gid);
};
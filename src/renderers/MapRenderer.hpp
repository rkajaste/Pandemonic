#pragma once
#include <vector>
#include <utility>
#include <tuple>
#include "texture.hpp"
#include "shader.hpp"
#include "ResourceManager.hpp"
#include "MapManager.hpp"

typedef std::tuple<int, std::__cxx11::string, int, int> TilesetInfo;
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
        TilesetInfo* getTilesetInfoByGid(int gid);
};
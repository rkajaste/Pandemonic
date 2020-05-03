#pragma once
#include <vector>
#include <utility>
#include <tuple>
#include "texture.hpp"
#include "shader.hpp"
#include "ResourceManager.hpp"

typedef std::tuple<int, std::__cxx11::string, int, int> TilesetInfo;
class MapRenderer{
    public:
        MapRenderer(Shader);
        ~MapRenderer();

        void initRenderData(
            std::vector<std::tuple<int, std::string, int, int>> tilesetInfo,
            std::vector<std::pair<glm::vec2, int>> tileCoordsGid);
        void drawMap();
    private:
        Shader shader;
        GLuint quadVAO;

        std::vector<std::pair<glm::vec2, int>> tileCoordsGid;
        std::vector<std::tuple<int, std::string, int, int>> tilesetInfo;

        void drawTile(int index);
        TilesetInfo* getTilesetInfoByGid(int gid);
};
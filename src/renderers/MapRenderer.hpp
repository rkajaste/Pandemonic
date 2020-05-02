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
        GLuint VBOids[2];

        GLfloat texVertices[12] = {
            // Left triangle
            // Pos      // Tex
            0.0f, 1.0f, // Bottom left corner
            1.0f, 0.0f, // Top right corner
            0.0f, 0.0f,  // Upper left corner

            // Right triangle
            0.0f, 1.0f, // Lower left corner
            1.0f, 1.0f, // Bottom right corner
            1.0f, 0.0f  // Top right corner
        };

        std::vector<std::pair<glm::vec2, int>> tileCoordsGid;
        std::vector<std::tuple<int, std::string, int, int>> tilesetInfo;

        void drawTile(int index);
        TilesetInfo* getTilesetInfoByGid(int gid);
};
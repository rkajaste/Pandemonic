#pragma once
#include <vector>
#include <utility>
#include <tuple>
#include "texture.hpp"
#include "shader.hpp"
#include "ResourceManager.hpp"

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
        GLuint vboIds[2];
        GLfloat texCoords[12] = {
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
        };

        std::vector<std::pair<glm::vec2, int>> tileCoordsGid;
        std::vector<std::tuple<int, std::string, int, int>> tilesetInfo;

        std::tuple<int, std::string, int, int>* getTilesetInfoByGid(int);
};
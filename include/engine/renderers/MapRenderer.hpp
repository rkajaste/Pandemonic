#pragma once
#include <vector>
#include <utility>
#include <tuple>
#include "Texture.hpp"
#include "Shader.hpp"
#include "ResourceManager.hpp"
#include "MapManager.hpp"
#include "types.hpp"
#include "Animator.hpp"
#include "Renderer.hpp"

typedef std::pair<glm::vec2, int> TileCoordsAndGid;

class MapRenderer: public Renderer {
    public:
        MapRenderer();
        ~MapRenderer();

        void drawMap();
        void debugMap();
    private:
        Shader hitboxShader;
        Animator* animator;

        void drawTile(int index);
        TilesetInfo getTilesetInfoByGid(int gid);
};
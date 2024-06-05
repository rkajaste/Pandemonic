#pragma once
#include <vector>
#include <utility>
#include <tuple>
#include "texture.h"
#include "shader.h"
#include "engine/store/resource_store.h"
#include "engine/store/map_store.h"
#include "types.h"
#include "animator.h"
#include "renderer.h"

typedef std::pair<glm::vec2, int> TileCoordsAndGid;

class MapRenderer : public Renderer
{
public:
    MapRenderer();
    ~MapRenderer();

    void drawMap();
    void debugMap();

private:
    Shader hitboxShader;
    Animator *animator;

    void drawTile(int index);
    TilesetInfo getTilesetInfoByGid(int gid);
};

#include "map_renderer.h"

MapRenderer::MapRenderer() : Renderer{}
{
    this->shader = ResourceStore::GetShader("tile");
    this->hitboxShader = ResourceStore::GetShader("hitbox");
    animator = new Animator(glm::vec2(64.0f, 64.0f));
}

MapRenderer::~MapRenderer()
{
    delete animator;
}

TilesetInfo MapRenderer::getTilesetInfoByGid(int gid)
{
    std::vector<TilesetInfo> tilesets = MapStore::getTilesetInfoArray();
    for (int i = tilesets.size() - 1; i > -1; --i)
    {
        try
        {
            if (gid >= tilesets.at(i).firstGid)
            {
                return tilesets.at(i);
            }
        }
        catch (const std::out_of_range &err)
        {
            std::cerr << "Out of range error: " << tilesets.at(i).firstGid << '\n';
        }
    }
    return tilesets.front();
}

void MapRenderer::drawTile(int index)
{
    std::vector<TileLocationInfo> TileLocationInfoArray = MapStore::getTileLocationInfoArray();
    glm::vec2 positionCoords = TileLocationInfoArray.at(index).coords;
    int tileGid = TileLocationInfoArray.at(index).gid;

    TilesetInfo tilesetInfo = this->getTilesetInfoByGid(tileGid);

    try
    {
        Texture2D texture;
        glm::vec2 texCoords;
        std::string textureName = tilesetInfo.name;
        int firstGid = tilesetInfo.firstGid;
        int tilesetColumns = tilesetInfo.columns;
        int tilesetTileCount = tilesetInfo.tileCount;
        int tileId = tileGid - firstGid;
        int tilesetRows = tilesetTileCount / tilesetColumns;
        GLfloat tileSize = 64.0f;

        // Initialize model matrix
        glm::mat4 model = glm::mat4(1.0f);

        // Bind tileset texture
        if (tilesetInfo.animations.size() > 0)
        {
            texture = animator->getTexture();
            texCoords = animator->getTextureCoords(textureName);
        }
        else
        {
            texture = ResourceStore::GetTexture(textureName);
            texCoords = glm::vec2(
                (tileId % tilesetColumns) * tileSize,
                (tileId / tilesetColumns) * tileSize);
        }
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        glm::vec2 tilesetDimensions = glm::vec2(tilesetRows * tileSize, tilesetColumns * tileSize);

        // Calculate tile position in world space
        glm::vec2 size = glm::vec2(tileSize);
        positionCoords.x *= tileSize;
        positionCoords.y *= tileSize;

        model = glm::translate(model, glm::vec3(positionCoords, 0.0f));
        model = glm::scale(model, glm::vec3(size, 1.0f));

        this->shader.SetVector2f("offset", texCoords);
        this->shader.SetVector2f("tileSize", glm::vec2(tileSize));
        this->shader.SetVector2f("tilesetDimensions", tilesetDimensions);
        this->shader.SetMatrix4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        if (tilesetInfo.animations.size() > 0)
        {
            animator->animate();
        }
    }
    catch (const std::out_of_range &err)
    {
        std::cerr << "Out of range error: " << err.what() << '\n';
    }
}

void MapRenderer::drawMap()
{
    this->shader.Use();
    glBindVertexArray(this->quadVAO);

    // Iterate over every tile and draw them
    std::vector<TileLocationInfo> tileLocationInfo = MapStore::getTileLocationInfoArray();
    for (unsigned int i = 0; i < tileLocationInfo.size(); ++i)
    {
        bool isLayerVisible = Util::existsInVector(tileLocationInfo.at(i).layer, MapStore::getVisibleLayers());
        if (isLayerVisible)
        {
            this->drawTile(i);
        }
    }
    glBindVertexArray(0);
}

void MapRenderer::debugMap()
{
    this->hitboxShader.Use();
    glBindVertexArray(this->quadVAO);
    for (const auto &terrain : MapStore::getTerrainObjects())
    {
        glm::mat4 hitboxModel = glm::mat4(1.0f);
        glm::vec2 size(terrain->GetWidth(), terrain->GetHeight());
        hitboxModel = glm::translate(hitboxModel, glm::vec3(glm::vec2(terrain->GetX(), terrain->GetY()), 0.0f));
        hitboxModel = glm::scale(hitboxModel, glm::vec3(size, 1.0f));
        this->hitboxShader.SetMatrix4("model", hitboxModel);
        this->hitboxShader.SetVector2f("size", size);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    for (const auto &terrain : MapStore::getLevelTransitionObjects())
    {
        glm::mat4 hitboxModel = glm::mat4(1.0f);
        glm::vec2 size(terrain->GetWidth(), terrain->GetHeight());
        hitboxModel = glm::translate(hitboxModel, glm::vec3(glm::vec2(terrain->GetX(), terrain->GetY()), 0.0f));
        hitboxModel = glm::scale(hitboxModel, glm::vec3(size, 1.0f));
        this->hitboxShader.SetMatrix4("model", hitboxModel);
        this->hitboxShader.SetVector2f("size", size);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);
}

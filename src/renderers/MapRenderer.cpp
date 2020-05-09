#include "MapRenderer.hpp"

MapRenderer::MapRenderer(Shader shader)
{
    this->shader = shader;
}
MapRenderer::~MapRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

TilesetInfo* MapRenderer::getTilesetInfoByGid(int gid) {
    for (int i = MapManager::getTilesetInfo().size() - 1; i > -1; --i)
        {
            if (gid >= std::get<0>(MapManager::getTilesetInfo().at(i)))
            {
                return &MapManager::getTilesetInfo().at(i);
            }
        }

    return NULL;
}

void MapRenderer::drawTile(int index)
{
        glm::vec2 positionCoords = MapManager::getTileCoordsAndGids().at(index).first;
        int tileGid = MapManager::getTileCoordsAndGids().at(index).second;

        TilesetInfo tilesetInfo = *this->getTilesetInfoByGid(tileGid);
        int firstGid = std::get<0>(tilesetInfo);

        std::string textureName = std::get<1>(tilesetInfo);
        int tilesetColumns = std::get<2>(tilesetInfo);
        int tilesetTileCount = std::get<3>(tilesetInfo);

        // Initialize model matrix
        glm::mat4 position = glm::mat4(1.0f);

        // Bind tileset texture
        Texture2D texture = ResourceManager::GetTexture(textureName);
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        int tileId = tileGid - firstGid;
        int tilesetRows = tilesetTileCount / tilesetColumns;
        GLfloat tileSize = 64.0f;

        // Calculate texture coordinates
        glm::vec2 texCoords = glm::vec2(
            (tileId % tilesetColumns) * tileSize,
            (tileId / tilesetColumns) * tileSize
        );
        glm::vec2 tilesetDimensions = glm::vec2(tilesetRows * tileSize, tilesetColumns * tileSize);

        // Calculate tile position in world space
        glm::vec2 size = glm::vec2(tileSize);
        positionCoords.x *= tileSize;
        positionCoords.y *= tileSize;
        position = glm::translate(position, glm::vec3(positionCoords, 0.0f));
        position = glm::scale(position, glm::vec3(size, 1.0f));

        this->shader.SetVector2f("offset", texCoords);
        this->shader.SetVector2f("tileSize", glm::vec2(tileSize));
        this->shader.SetVector2f("tilesetDimensions", tilesetDimensions);
        this->shader.SetMatrix4("position", position);

        glDrawArrays(GL_TRIANGLES, 0, 6);

}

void MapRenderer::drawMap()
{
    this->shader.Use();
    glBindVertexArray(this->quadVAO);
    // Iterate over every tile and draw them
    for(unsigned int i = 0; i < MapManager::getTileCoordsAndGids().size(); ++i) {
        this->drawTile(i);
    }
    glBindVertexArray(0);
}

void MapRenderer::initRenderData()
{
    GLuint VBO;
    GLfloat vertices[24] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f, // Bottom left corner
        1.0f, 0.0f, 1.0f, 0.0f, // Top right corner
        0.0f, 0.0f, 0.0f, 0.0f, // Upper left corner

        0.0f, 1.0f, 0.0f, 1.0f, // Lower left corner
        1.0f, 1.0f, 1.0f, 1.0f, // Bottom right corner
        1.0f, 0.0f, 1.0f, 0.0f  // Top right corner
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
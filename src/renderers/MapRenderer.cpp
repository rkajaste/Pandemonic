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
    for (int i = this->tilesetInfo.size() - 1; i > -1; --i)
        {
            if (gid >= std::get<0>(this->tilesetInfo.at(i)))
            {
                return &this->tilesetInfo.at(i);
            }
        }

    return NULL;
}

void MapRenderer::drawTile(int index)
{
        glm::vec2 positionCoords = this->tileCoordsGid.at(index).first;
        int tileGid = this->tileCoordsGid.at(index).second;

        TilesetInfo tilesetInfo = *this->getTilesetInfoByGid(tileGid);
        int firstGid = std::get<0>(tilesetInfo);

        std::string textureName = std::get<1>(tilesetInfo);
        int tilesetColumns = std::get<2>(tilesetInfo);
        int tilesetTileCount = std::get<3>(tilesetInfo);

        // Initialize model matrixes
        glm::mat4 position = glm::mat4(1.0f);
        glm::mat4 texPosition = glm::mat4(1.0f);

        // bind tileset texture
        Texture2D texture = ResourceManager::GetTexture(textureName);
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        int tileId = tileGid - firstGid;
        int tilesetRows = tilesetTileCount / tilesetColumns;
        GLfloat tileSize = 64.0f;

        // Calculate texture coordinates
        GLfloat tileUnit = tileSize / texture.Width;
        glm::vec2 texCoords = glm::vec2(
            tileId % tilesetColumns * tileUnit,
            tileId / tilesetRows * tileUnit
        );

        // Calculate tile position in world space
        glm::vec2 size = glm::vec2(tileSize);
        positionCoords.x *= tileSize;
        positionCoords.y *= tileSize;

        position = glm::translate(position, glm::vec3(positionCoords, 0.0f));
        position = glm::scale(position, glm::vec3(size, 1.0f));
        //texPosition = glm::translate(texPosition, glm::vec3(texCoords, 0.0f));

        //this->shader.SetMatrix4("texPosition", texPosition);
        this->shader.SetMatrix4("position", position);

        GLfloat texVertices[] = {

            texCoords.x, texCoords.y + tileUnit,// Bottom left corner
            texCoords.x + tileUnit, texCoords.y, // Top right corner
            texCoords.x, texCoords.y, // Upper left corner

            texCoords.x, texCoords.y + tileUnit,// Lower left corner
            texCoords.x + tileUnit, texCoords.y + tileUnit, // Bottom right corner
            texCoords.x + tileUnit, texCoords.y // Top right corner texCoords.x, texCoords.y + tileUnit, // Bottom left corner
        };

        glBindBuffer(GL_ARRAY_BUFFER, this->VBOids[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(texVertices), texVertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
}

void MapRenderer::drawMap()
{
    this->shader.Use();
    glBindVertexArray(this->quadVAO);
    // Iterate over every tile and draw them
    for(unsigned int i = 0; i < this->tileCoordsGid.size(); i++) {
        this->drawTile(i);
    }
    glBindVertexArray(0);
}

void MapRenderer::initRenderData(
    std::vector<std::tuple<int, std::string, int, int>> tilesetInfo,
    std::vector<std::pair<glm::vec2, int>> tileCoordsGid
)
{
    this->tilesetInfo = tilesetInfo;
    this->tileCoordsGid = tileCoordsGid;

    GLfloat vertices[] = {
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


    // GLfloat vertices[] = {
    //     0.0f, 1.0f, 0.0f, 1.0f,
    //     1.0f, 0.0f, 1.0f, 0.0f,
    //     0.0f, 0.0f, 0.0f, 0.0f,

    //     0.0f, 1.0f, 0.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f, 1.0f,
    //     1.0f, 0.0f, 1.0f, 0.0f
    // };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(2, this->VBOids);

    // Load positions.
    glBindBuffer(GL_ARRAY_BUFFER, this->VBOids[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBOids[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->texVertices), this->texVertices, GL_DYNAMIC_DRAW);

    glBindVertexArray(this->quadVAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
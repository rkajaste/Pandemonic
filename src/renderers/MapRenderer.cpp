#include "MapRenderer.hpp"

MapRenderer::MapRenderer(Shader shader)
{
    this->shader = shader;
}
MapRenderer::~MapRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

std::tuple<int, std::string, int, int>* MapRenderer::getTilesetInfoByGid(int gid) {
    for (int i = this->tilesetInfo.size() - 1; i > -1; --i)
        {
            if (gid >= std::get<0>(this->tilesetInfo.at(i)))
            {
                return &this->tilesetInfo.at(i);
            }
        }

    return NULL;
}

void MapRenderer::drawMap()
{
    glm::vec2 size = glm::vec2(64.0f, 64.0f);

    // Iterate over every tile and draw them
    for(unsigned int i = 0; i < this->tileCoordsGid.size(); i++) {
        GLfloat tileSize = 64.0f;
        glm::vec2 position = this->tileCoordsGid.at(i).first;
        int tileGid = this->tileCoordsGid.at(i).second;

        std::tuple<int, std::string, int, int> tilesetInfo =
            *this->getTilesetInfoByGid(tileGid);
        int firstGid = std::get<0>(tilesetInfo);
        std::string textureName = std::get<1>(tilesetInfo);
        int tilesetColumns = std::get<2>(tilesetInfo);
        int tilesetTileCount = std::get<3>(tilesetInfo);

        Texture2D texture = ResourceManager::GetTexture(textureName);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(glm::vec2(position.x * tileSize, position.y * tileSize), 0.0f));
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
        model = glm::scale(model, glm::vec3(size, 1.0f));

        this->shader.Use();
        this->shader.SetMatrix4("model", model);
        // Render textured quad
        this->shader.SetVector3f("spriteColor", glm::vec3(1.0f));

        // bind tileset texture
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
        int tileId = tileGid - firstGid;
        int tilesetRows = tilesetTileCount / tilesetColumns;

        GLfloat tileX = tileId % tilesetColumns + 1.0f;
        GLfloat tileY = tileId / tilesetRows + 1.0f;
        GLfloat texCoordsX = 1.0f - 1.0f / tileX;
        GLfloat texCoordsY = 1.0f - 1.0f / tileY;
        GLfloat tileSizeUV = 1.0f / tilesetColumns;

        // Something fucky going on in here
        this->texCoords[0] = texCoordsX;
        this->texCoords[1] = texCoordsY + tileSizeUV;
        this->texCoords[2] = texCoordsX + tileSizeUV;
        this->texCoords[3] = texCoordsY;
        this->texCoords[4] = texCoordsX;
        this->texCoords[5] = texCoordsY;

        this->texCoords[6] = texCoordsX;
        this->texCoords[7] = texCoordsY + tileSizeUV;
        this->texCoords[8] = texCoordsX + tileSizeUV;
        this->texCoords[9] = texCoordsY + tileSizeUV;
        this->texCoords[10] = texCoordsX + tileSizeUV;
        this->texCoords[11] = texCoordsY;

        glBindBuffer(GL_ARRAY_BUFFER, this->vboIds[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(texCoords), texCoords);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(this->quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}

void MapRenderer::initRenderData(
    std::vector<std::tuple<int, std::string, int, int>> tilesetInfo,
    std::vector<std::pair<glm::vec2, int>> tileCoordsGid
)
{
    this->tilesetInfo = tilesetInfo;
    this->tileCoordsGid = tileCoordsGid;
    // Configure VAO/VBO
    GLfloat positions[] = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(2, this->vboIds);

    // Load positions.
    glBindBuffer(GL_ARRAY_BUFFER, this->vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->texCoords), this->texCoords, GL_DYNAMIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
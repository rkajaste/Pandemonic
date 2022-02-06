#include "engine/renderers/TextRenderer.hpp"

TextRenderer::TextRenderer()
{
    this->processGlyphs();
    this->shader = ResourceManager::GetShader("glyph");
}

void TextRenderer::processGlyphs()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    std::string arcadepiPath = Config::getRootDirectory() + "/assets/fonts/arcadepi.ttf";

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, arcadepiPath.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        std::string textureName = "glyph_" + std::to_string(static_cast<int>(c));
        ResourceManager::LoadGlyphTexture(textureName, face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);
        // now store character for later use
        Character character = {
            textureName,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x >> 6 // since advance is 1/64 pixel, bitshift by 6 to get value in pixels (2^6 = 64)
        };
        characters.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::drawText(std::string text, glm::vec2 position, glm::vec4 color)
{
    this->shader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->quadVAO);
    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        this->shader.SetMatrix4("view", glm::mat4(1.0f));
        this->shader.SetVector4f("textColor", color);
        Character ch = characters[*c];

        Texture2D texture = ResourceManager::GetTexture(ch.textureName);
        texture.Bind();

        GLfloat positionX = position.x + ch.bearing.x;
        GLfloat positionY = position.y - ch.bearing.y;

        model = glm::translate(model, glm::vec3(positionX, positionY, 0.0f));
        model = glm::scale(model, glm::vec3(ch.size, 1.0f));
        this->shader.SetMatrix4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        position.x += ch.advance;
    }

    glBindVertexArray(0);
}

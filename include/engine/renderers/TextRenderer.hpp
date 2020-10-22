#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <iostream>

#include "Renderer.hpp"
#include "ResourceManager.hpp"

struct Character {
    std::string textureName;  // ID handle of the glyph texture
    glm::ivec2   size;       // Size of glyph
    glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
    long int advance;    // Offset to advance to next glyph
};

class TextRenderer: public Renderer
{
    public:
        TextRenderer();
        void drawText(std::string text, glm::vec2 position, glm::vec4 color);
    private:
        std::string fontFamily;
        std::map<char, Character> characters;

        void processGlyphs();
};

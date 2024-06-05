#pragma once

#include <map>
#include <string>

#include <glad/glad.h>
#include "texture.h"
#include "shader.h"

class ResourceStore
{
public:
    // Resource storage
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;
    static std::map<std::string, int> transitionFrames; // Number of animaton frames from start that should only be run once
    static std::map<std::string, GLfloat> animationSpeeds;
    // Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader LoadShader(
        const std::string vShaderFile,
        const std::string fShaderFile,
        const std::string gShaderFile,
        std::string name
    );
    // Retrieves a stored sader
    static Shader GetShader(std::string name);
    // Loads (and generates) a texture from file
    static Texture2D LoadTexture(
        const std::string file,
        std::string name,
        int transitionFrameAmount = 0,
        GLfloat animationSpeed = 20.0f
    );
    static Texture2D LoadGlyphTexture(
        std::string name,
        GLfloat width,
        GLfloat height,
        unsigned char *data
    );
    // Retrieves a stored texture
    static Texture2D GetTexture(std::string name);
    // Properly de-allocates all loaded resources
    static void Clear();

private:
    ResourceStore() {}

    static Shader loadShaderFromFile(
        const std::string vShaderFile,
        const std::string fShaderFile,
        const std::string gShaderFile
    );
    static Texture2D loadTextureFromFile(const std::string file, GLboolean alpha);
};


/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "engine/store/resource_store.h"
#include <iostream>
#include <sstream>
#include <fstream>

#include <stb_image.h>

// Instantiate static variables
std::map<std::string, Texture2D> ResourceStore::Textures;
std::map<std::string, Shader> ResourceStore::Shaders;
std::map<std::string, int> ResourceStore::transitionFrames;
std::map<std::string, GLfloat> ResourceStore::animationSpeeds;

Shader ResourceStore::LoadShader(const std::string vShaderFile, const std::string fShaderFile, const std::string gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceStore::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceStore::LoadTexture(
    const std::string file,
    std::string name,
    int transitionFrameAmount,
    GLfloat animationSpeed)
{
    Textures[name] = loadTextureFromFile(file, true);
    transitionFrames[name] = transitionFrameAmount;
    animationSpeeds[name] = animationSpeed == 0 ? 8.0f : animationSpeed;
    return Textures[name];
}

Texture2D ResourceStore::LoadGlyphTexture(std::string name, GLfloat width, GLfloat height, unsigned char *data)
{
    // Create Texture object
    Texture2D texture;
    texture.Internal_Format = GL_RED;
    texture.Image_Format = GL_RED;
    texture.Generate(width, height, data);
    Textures[name] = texture;
    return Textures[name];
}

Texture2D ResourceStore::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceStore::Clear()
{
    // (Properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceStore::loadShaderFromFile(const std::string vShaderFile, const std::string fShaderFile, const std::string gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (!gShaderFile.empty())
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    if (vertexCode.empty())
        std::cout << "ERROR::SHADER: vertexCode is empty" << std::endl;

    if (fragmentCode.empty())
        std::cout << "ERROR::SHADER: fragmentCode is empty" << std::endl;

    if (!gShaderFile.empty() && geometryCode.size() == 0)
        std::cout << "ERROR::SHADER: geometryCode is empty" << std::endl;

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, !gShaderFile.empty() ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceStore::loadTextureFromFile(const std::string file, GLboolean alpha = GL_TRUE)
{
    // Create Texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // Load image
    int width, height, nrChannels;
    unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
    // Now generate texture
    texture.Generate(width, height, data);
    // And finally free image data
    stbi_image_free(data);
    return texture;
}

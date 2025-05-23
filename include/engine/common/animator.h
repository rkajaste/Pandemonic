#pragma once
#include <glm/glm.hpp>
#include <string>
#include "engine/store/resource_store.h"
#include "texture.h"

class Animator
{
public:
    Animator(glm::vec2 spriteSize);
    ~Animator(){};

    void animate();
    bool hasAnimationFinished(std::string animation);

    glm::vec2 getTextureCoords(std::string textureName);
    Texture2D getTexture();
    int getCurrentFrame();
    std::string getCurrentTextureName();

private:
    GLboolean vertical = false;
    int currentFrame = 0;
    int maxFrames = 0;
    int currentTime = 0;
    int prevTime = 0;
    std::string currentTextureName = "";
    glm::vec2 frameCount;
    glm::vec2 spriteSize;
    glm::vec2 texCoords;
};

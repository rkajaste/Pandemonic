#include "Animator.hpp"

Animator::Animator(glm::vec2 spriteSize)
{
    this->spriteSize = spriteSize;
}

void Animator::animate()
{
    if (this->currentTime - this->prevTime >= ResourceManager::animationSpeeds[this->currentTextureName]) {
        this->currentTime = 0;
        this->prevTime = this->currentTime;
        if (this->currentFrame >= this->maxFrames - 1) {
            this->currentFrame = ResourceManager::transitionFrameAmounts[this->currentTextureName];
            printf("%s\n", this->currentTextureName.c_str());
        } else {
            ++this->currentFrame;
        }
    }
    ++this->currentTime;
}


glm::vec2 Animator::getTextureCoords(std::string textureName)
{
    if (this->currentTextureName != textureName) {
        this->currentTextureName = textureName;
        this->currentFrame = 0;
        Texture2D texture = ResourceManager::GetTexture(textureName);
        this->frameCount.x = glm::round(texture.Width / this->spriteSize.x);
        this->frameCount.y = glm::round(texture.Height / this->spriteSize.y);
        this->vertical = this->frameCount.y > this->frameCount.x;
        this->maxFrames = this->vertical ? this->frameCount.y : this->frameCount.x;
    }

    this->texCoords.x = !this->vertical ? this->spriteSize.x * this->currentFrame : 0.0f;
    this->texCoords.y = this->vertical ? this->spriteSize.y * this->currentFrame : 0.0f;

    //printf("%s, current frame: %d, texCoords: (%02f, %02f)\n", this->currentTextureName.c_str(), this->currentFrame, this->texCoords.x, this->texCoords.y);

    return texCoords;
}

Texture2D Animator::getTexture()
{
    return ResourceManager::GetTexture(this->currentTextureName);
}

int Animator::getCurrentFrame()
{
    return this->currentFrame;
}

std::string Animator::getCurrentTextureName()
{
    return this->currentTextureName;
}

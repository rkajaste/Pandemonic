#include "animator.h"

Animator::Animator(glm::vec2 spriteSize)
{
    this->spriteSize = spriteSize;
}

void Animator::animate()
{
    if (this->currentTime - this->prevTime >= ResourceStore::animationSpeeds[this->currentTextureName])
    {
        this->currentTime = 0;
        this->prevTime = this->currentTime;
        if (this->currentFrame >= this->maxFrames - 1)
        {
            this->currentFrame = ResourceStore::transitionFrames[this->currentTextureName];
        }
        else
        {
            ++this->currentFrame;
        }
    }
    ++this->currentTime;
}

glm::vec2 Animator::getTextureCoords(std::string textureName)
{
    if (this->currentTextureName != textureName)
    {
        this->currentTextureName = textureName;
        this->currentFrame = 0;
        Texture2D texture = ResourceStore::GetTexture(textureName);
        this->frameCount.x = glm::round(texture.Width / this->spriteSize.x);
        this->frameCount.y = glm::round(texture.Height / this->spriteSize.y);
        this->vertical = this->frameCount.y > this->frameCount.x;
        this->maxFrames = this->vertical ? this->frameCount.y : this->frameCount.x;
    }

    this->texCoords.x = !this->vertical ? this->spriteSize.x * this->currentFrame : 0.0f;
    this->texCoords.y = this->vertical ? this->spriteSize.y * this->currentFrame : 0.0f;

    return texCoords;
}

Texture2D Animator::getTexture()
{
    return ResourceStore::GetTexture(this->currentTextureName);
}

int Animator::getCurrentFrame()
{
    return this->currentFrame;
}

bool Animator::hasAnimationFinished(std::string animation)
{
    if (this->currentTextureName == animation)
    {
        return this->currentFrame >= this->maxFrames - 1;
    }
    return false;
}

std::string Animator::getCurrentTextureName()
{
    return this->currentTextureName;
}

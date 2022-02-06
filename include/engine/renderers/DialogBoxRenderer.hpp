#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "Texture.hpp"
#include "ResourceManager.hpp"
#include "Renderer.hpp"
#include "Config.hpp"
#include "engine/common/Constants.hpp"

class DialogBoxRenderer : public Renderer
{
public:
    DialogBoxRenderer();

    void drawDialogBox(glm::vec2 position, glm::vec2 size);
    void drawDialogBoxAvatar(glm::vec2 position, glm::vec2 size, std::string textureName);
};

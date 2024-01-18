#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "texture.h"
#include "resource_manager.h"
#include "renderer.h"
#include "config.h"
#include "engine/common/constants.h"

class DialogBoxRenderer : public Renderer
{
public:
    DialogBoxRenderer();

    void drawDialogBox(glm::vec2 position, glm::vec2 size);
    void drawDialogBoxAvatar(glm::vec2 position, glm::vec2 size, std::string textureName);
};

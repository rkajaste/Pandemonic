#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "texture.h"
#include "shader.h"
#include "engine/store/resource_store.h"
#include "animator.h"
#include "renderer.h"
#include "config.h"
#include "engine/common/constants.h"

class UserInterfaceRenderer : public Renderer
{
public:
    UserInterfaceRenderer();

    void drawComponent(std::string textureName, glm::vec2 position, glm::vec2 size);
    void drawBar(glm::vec2 position, glm::vec2 size, glm::vec4 color, GLint maxValue = 0, GLint currentValue = 0);

private:
    GLfloat calculateBarWidth(GLfloat maxWidth, GLint maxValue, GLint currentValue);
    Shader statusBarShader;
};

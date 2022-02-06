#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "Texture.hpp"
#include "Shader.hpp"
#include "ResourceManager.hpp"
#include "Animator.hpp"
#include "Renderer.hpp"
#include "Config.hpp"
#include "engine/common/Constants.hpp"

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

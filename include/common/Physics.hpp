#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Physics {
    GLfloat calculateHeight(GLfloat height, GLfloat dt);
    GLboolean collides(glm::vec2 selfCoords, glm::vec2 selfSize, glm::vec2 otherCoords, glm::vec2 otherSize);
    GLboolean isGrounded(glm::vec2 self, glm::vec2 floor);
}

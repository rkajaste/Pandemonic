#include "Physics.hpp"

GLfloat Physics::calculateHeight(GLfloat height, GLfloat dt) {
    return height + 100.0f * dt;
}

GLboolean Physics::collides(glm::vec2 self,  glm::vec2 other) {
    return self.x > other.x && self.y > other.y;
}

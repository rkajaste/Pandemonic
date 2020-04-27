#include "Physics.hpp"

GLfloat Physics::calculateHeight(GLfloat height, GLfloat dt) {
    return height + 100.0f * dt;
}

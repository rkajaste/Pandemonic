#include "physics.h"

GLfloat Physics::calculateGravity(GLfloat gravityForce, GLfloat dt)
{
    gravityForce += 3000.0f * dt;
    return gravityForce;
}

GLboolean Physics::collides(glm::vec2 selfCoords, glm::vec2 selfSize, glm::vec2 otherCoords, glm::vec2 otherSize)
{
    GLfloat selfCoordsY = MapManager::getWorldHeight() - selfCoords.y;
    GLfloat otherCoordsY = MapManager::getWorldHeight() - otherCoords.y;
    GLfloat selfTop = selfCoordsY;
    GLfloat selfBottom = selfCoordsY - selfSize.y;
    GLfloat otherTop = otherCoordsY;
    GLfloat otherBottom = otherCoordsY - otherSize.y;

    return (
        selfCoords.x + selfSize.x >= otherCoords.x &&
        selfCoords.x <= otherCoords.x + otherSize.x &&
        selfTop >= otherBottom &&
        selfBottom <= otherTop);
}

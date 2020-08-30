#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "ResourceManager.hpp"
#include "MapManager.hpp"
#include "Config.hpp"

class Camera {
    public:
        glm::mat4 view = glm::mat4(1.0f);
        Camera();

        void setPosition(glm::vec2 playerCoords);
        
    private:
        glm::vec2 offset;
        GLfloat minCameraY;
        glm::vec2 position;

        void contain(glm::vec2 playerCoords);
};
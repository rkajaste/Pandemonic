#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ResourceManager.hpp"
#include "MapManager.hpp"
#include <GLFW/glfw3.h>
#include "config.hpp"

class Camera {
    public:
        glm::mat4 view = glm::mat4(1.0f);
        Camera();

        void setPosition(glm::vec2 coords);
        
    private:
        void contain();
        glm::vec2 position;
};
#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "UserInterfaceRenderer.hpp"

struct InterfaceComponent {
    std::string textureName;
    glm::vec2 coords;
    glm::vec2 size;
};

class UserInterface {
    public:
        UserInterface(UserInterfaceRenderer *renderer);
        ~UserInterface();
        
        UserInterfaceRenderer* renderer;
        void draw();

    private:
        std::vector<InterfaceComponent> interfaceComponents;
};

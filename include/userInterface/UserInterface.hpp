#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "UserInterfaceRenderer.hpp"
#include "Util.hpp"
#include "Store.hpp"

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
        void drawStatusBars();

    private:
        std::vector<InterfaceComponent> interfaceComponents;
};

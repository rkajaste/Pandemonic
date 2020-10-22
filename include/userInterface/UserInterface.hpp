#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "UserInterfaceRenderer.hpp"
#include "TextRenderer.hpp"
#include "Util.hpp"
#include "Store.hpp"
#include "Config.hpp"
#include "types.hpp"

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
        TextRenderer* textRenderer;
        void draw();
        void update();

    private:
        std::vector<InterfaceComponent> interfaceComponents;

        GameState currentGameState;
        void clearUI();
        void drawStatusBars();
        void setupMainMenu();
        void setupInGameUI();
};

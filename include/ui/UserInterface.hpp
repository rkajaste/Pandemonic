#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "engine/renderers/UserInterfaceRenderer.hpp"
#include "engine/renderers/TextRenderer.hpp"
#include "engine/common/Util.hpp"
#include "store/Store.hpp"
#include "store/DialogStore.hpp"
#include "store/PlayerStore.hpp"
#include "Config.hpp"
#include "engine/common/types.hpp"
#include "ui/popups/DialogBox.hpp"

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
        DialogBox* dialogBox;
        GameState currentGameState;

        void clearUI();
        void drawStatusBars();
        void setupMainMenu();
        void setupInGameUI();
};

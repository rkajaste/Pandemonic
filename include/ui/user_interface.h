#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "engine/renderers/user_interface_renderer.h"
#include "engine/renderers/text_renderer.h"
#include "engine/common/util.h"
#include "store/game_store.h"
#include "store/dialog_store.h"
#include "store/player_store.h"
#include "config.h"
#include "engine/common/types.h"
#include "ui/popups/dialog_box.h"

struct InterfaceComponent
{
    std::string textureName;
    glm::vec2 coords;
    glm::vec2 size;
};

class UserInterface
{
public:
    UserInterface(UserInterfaceRenderer *renderer);
    ~UserInterface();

    UserInterfaceRenderer *renderer;
    TextRenderer *textRenderer;
    void update(GLfloat dt);
    void draw();

private:
    std::vector<InterfaceComponent> interfaceComponents;
    DialogBox *dialogBox;
    GameState currentGameState;

    void clearUI();
    void drawStatusBars();
    void setupMainMenu();
    void setupInGameUI();
};

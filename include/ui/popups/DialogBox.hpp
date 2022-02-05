#pragma once

#include <string>
#include "store/DialogStore.hpp"
#include "engine/renderers/TextRenderer.hpp"
#include "engine/renderers/UserInterfaceRenderer.hpp"
#include "engine/renderers/DialogBoxRenderer.hpp"
#include "engine/common/Util.hpp"
#include "engine/common/types.hpp"
#include "engine/managers/CooldownManager.hpp"

// undefine some Windows library functions to avoid name overlap at compile time
#undef DialogBox

class DialogBox
{
public:
    DialogBox(std::string identifier);
    ~DialogBox();

    void update(GLfloat dt);
    void draw();

private:
    CooldownManager *cooldownManager = NULL;
    TextRenderer *textRenderer;
    DialogBoxRenderer *renderer;
    std::vector<Dialog> dialogLines;

    glm::vec2 dialogSize;
    glm::vec2 dialogPosition;

    glm::vec2 avatarSize;
    glm::vec2 avatarPosition;

    glm::vec2 namePosition;

    glm::vec2 dialogTextPosition;

    void debounceDialogText(std::string text);
    void drawName(std::string name);
};

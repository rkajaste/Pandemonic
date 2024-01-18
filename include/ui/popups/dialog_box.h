#pragma once

#include <string>
#include "store/dialog_store.h"
#include "engine/renderers/text_renderer.h"
#include "engine/renderers/user_interface_renderer.h"
#include "engine/renderers/dialog_box_renderer.h"
#include "engine/common/util.h"
#include "engine/common/types.h"
#include "engine/managers/cooldown_manager.h"

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

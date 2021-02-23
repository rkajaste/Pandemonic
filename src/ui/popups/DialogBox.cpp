#include "ui/popups/DialogBox.hpp"

DialogBox::DialogBox(std::string identifier)
{
    this->textRenderer = new TextRenderer();
    this->renderer = new DialogBoxRenderer();
    this->dialogLines = Store::getDialogByIdentifier(identifier);

    this->dialogSize = glm::vec2(Config::getScreenWidth(), Config::getScreenHeight() / 4);
    this->dialogPosition = glm::vec2(0.0f, Config::getScreenHeight() - dialogSize.y);

    this->avatarSize = glm::vec2(dialogSize.y / 2);
    this->avatarPosition = glm::vec2(dialogPosition.x + 80.0f, dialogPosition.y + 80.0f);

    this->namePosition = glm::vec2(avatarPosition.x + avatarSize.x + 80.0f, avatarPosition.y);

    this->dialogTextPosition = glm::vec2(namePosition.x, namePosition.y + 80.0f);
}

DialogBox::~DialogBox()
{
    delete this->textRenderer;
    delete this->renderer;
}

void DialogBox::draw()
{   
    Dialog currentLine = dialogLines.at(0);

    renderer->drawDialogBox(dialogPosition, dialogSize);
    renderer->drawDialogBoxAvatar(
        avatarPosition,
        avatarSize,
        "ui_dialog_avatar_" + currentLine.avatar
    );
    drawName(currentLine.name);
    for (
        std::vector<Dialog>::iterator line = dialogLines.begin();
        line != dialogLines.end();
        ++line
    ) {
        const Dialog &dialogLine = *line;
        debounceDialogText(dialogLine.text);
    }
}

void DialogBox::debounceDialogText(std::string text)
{
    // add debounce later
    textRenderer->drawText(
        text,
        dialogTextPosition,
        Util::formatRGB(100.0f, 100.0f, 100.0f)
    );
}

void DialogBox::drawName(std::string name)
{
    textRenderer->drawText(
        name,
        namePosition,
        Util::formatRGB(100.0f, 100.0f, 100.0f)
    );
}
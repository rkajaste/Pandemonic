#include "ui/popups/DialogBox.hpp"

DialogBox::DialogBox(std::string identifier)
{
    this->textRenderer = new TextRenderer();
    this->renderer = new DialogBoxRenderer();
    this->dialogLines = DialogStore::getDialogByIdentifier(identifier);

    this->dialogSize = glm::vec2(Config::getScreenWidth(), Config::getScreenHeight() / 4);
    if (DialogStore::isDialogPositionedTop()) {
        this->dialogPosition = glm::vec2(0.0f, 0.0f);
    } else {
        this->dialogPosition = glm::vec2(0.0f, Config::getScreenHeight() - dialogSize.y);
    }

    this->avatarSize = glm::vec2(dialogSize.y / 2);
    this->avatarPosition = glm::vec2(dialogPosition.x + 80.0f, dialogPosition.y + 80.0f);

    this->namePosition = glm::vec2(avatarPosition.x + avatarSize.x + 80.0f, avatarPosition.y);

    this->dialogTextPosition = glm::vec2(namePosition.x, namePosition.y + 80.0f);

    Cooldowns cooldowns = {
        {
            "debounce_text", 
            {
                { "timer", 5.0f },
                { "cooldown", 5.0f }
            }
        }
    };
    this->cooldownManager = new CooldownManager(cooldowns);
}

DialogBox::~DialogBox()
{
    delete this->cooldownManager;
    delete this->textRenderer;
    delete this->renderer;
}

void DialogBox::update(GLfloat dt)
{
    this->cooldownManager->advanceCooldowns(dt);
    if (!this->cooldownManager->hasCooldown("debounce_text")) {
        DialogStore::incrementDebounceIndex();
        this->cooldownManager->setCooldown("debounce_text");
    }
}

void DialogBox::draw()
{
    Dialog currentLine = dialogLines.at(DialogStore::getCurrentLine());

    this->renderer->drawDialogBox(dialogPosition, dialogSize);
    this->renderer->drawDialogBoxAvatar(
        avatarPosition,
        avatarSize,
        "ui_dialog_avatar_" + currentLine.avatar
    );
    drawName(currentLine.name);
    debounceDialogText(currentLine.text);
}

void DialogBox::debounceDialogText(std::string text)
{
    std::string substring = text.substr(0, DialogStore::getDebounceIndex());
    this->textRenderer->drawText(
        substring,
        dialogTextPosition,
        Util::formatRGB(100.0f, 100.0f, 100.0f)
    );
}

void DialogBox::drawName(std::string name)
{
    this->textRenderer->drawText(
        name,
        namePosition,
        Util::formatRGB(100.0f, 100.0f, 100.0f)
    );
}
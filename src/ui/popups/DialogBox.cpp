#include "ui/popups/DialogBox.hpp"

DialogBox::DialogBox(std::string identifier)
{
    this->textRenderer = new TextRenderer();
    this->dialogLines = Store::getDialogByIdentifier(identifier);
}

DialogBox::~DialogBox()
{
    delete this->textRenderer;
}

void DialogBox::draw(UserInterfaceRenderer *renderer)
{   
    // render dialog box before loop
    for (
        std::vector<Dialog>::iterator line = dialogLines.begin();
        line != dialogLines.end();
        ++line
    ) {
        const Dialog &dialogLine = *line;
        debounceText(dialogLine.text);
    }
}

void DialogBox::debounceText(std::string text)
{
    // add debounce later
    textRenderer->drawText(
        text,
        glm::vec2(100.0f, 100.0f),
        Util::formatRGB(100.0f, 100.0f, 100.0f)
    );
}
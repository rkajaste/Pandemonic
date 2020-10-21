#include "UserInterface.hpp"

UserInterface::UserInterface(UserInterfaceRenderer* renderer) {

    InterfaceComponent statusBar;
    statusBar.textureName = "status_bar";
    statusBar.coords = glm::vec2(50.0f, 20.0f);
    statusBar.size = glm::vec2(232.0f, 89.0f);

    this->renderer = renderer;
    this->interfaceComponents.push_back(statusBar);
}

UserInterface::~UserInterface() {
    delete this->renderer;
}

void UserInterface::draw()
{
    for(const auto& component: this->interfaceComponents) {
        renderer->drawComponent(component.textureName, component.coords, component.size);
    }
    drawStatusBars();
}

void UserInterface::drawStatusBars()
{
    PlayerStatus playerStatus = Store::getPlayerStatus();

    renderer->drawBar(glm::vec2(108.0f, 53.0f), glm::vec2(149.0f, 16.0f), Util::formatRGB(237.0f, 55.0f, 55.0f, 0.5f));
    renderer->drawBar(glm::vec2(108.0f, 53.0f), glm::vec2(149.0f, 16.0f), Util::formatRGB(237.0f, 55.0f, 55.0f, 0.9f), playerStatus.maxHP, playerStatus.currentHP);

    renderer->drawBar(glm::vec2(108.0f, 73.0f), glm::vec2(110.0f, 12.0f), Util::formatRGB(55.0f, 131.0f, 237.0f, 0.5f));
    renderer->drawBar(glm::vec2(108.0f, 73.0f), glm::vec2(110.0f, 12.0f), Util::formatRGB(55.0f, 131.0f, 237.0f, 0.9f), playerStatus.maxMP, playerStatus.currentMP);
}
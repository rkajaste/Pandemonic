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
    renderer->drawHealthBar(glm::vec2(105.0f, 52.0f), glm::vec2(150.0f, 18.0f));
}
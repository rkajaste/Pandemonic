#include "ui/UserInterface.hpp"

UserInterface::UserInterface(UserInterfaceRenderer* renderer) {
    this->renderer = renderer;
    this->textRenderer = new TextRenderer();
    this->currentGameState = GameState::MAIN_MENU;
    this->dialogBox = NULL;
}

UserInterface::~UserInterface()
{
    delete this->renderer;
    delete this->textRenderer;
    delete this->dialogBox;
}

void UserInterface::update(GLfloat dt)
{
    GameState gameState = Store::getGameState();
    
    if (DialogStore::isDialogOpen() && this->dialogBox == NULL) {
        this->dialogBox = new DialogBox(DialogStore::getDialogIdentifier());
    } else if (!DialogStore::isDialogOpen()) {
        delete this->dialogBox;
        this->dialogBox = NULL;
    }

    if (this->dialogBox != NULL) {
        this->dialogBox->update(dt);
    }

    if (gameState != currentGameState) {
        currentGameState = gameState;
        clearUI();
        if (gameState == MAIN_MENU) {
            setupMainMenu();
        } else if (gameState == GAME_START) {
            setupInGameUI();
        }  
    }
}


void UserInterface::draw()
{
    for(const auto& component: this->interfaceComponents) {
        renderer->drawComponent(component.textureName, component.coords, component.size);
    }
    if (currentGameState == GAME_START) {
        drawStatusBars();
    }
    if (DialogStore::isDialogOpen() && dialogBox != NULL) {
        dialogBox->draw();
    }
}

void UserInterface::setupInGameUI()
{
    InterfaceComponent statusBar;
    statusBar.textureName = "status_bar";
    statusBar.coords = glm::vec2(50.0f, 20.0f);
    statusBar.size = glm::vec2(232.0f, 89.0f);
    this->interfaceComponents.push_back(statusBar);
}

void UserInterface::setupMainMenu()
{
    InterfaceComponent menuFrame;
    menuFrame.textureName = "menu_frame";
    menuFrame.size = glm::vec2(240.0f, 277.0f);
    menuFrame.coords = glm::vec2(
        Config::getScreenWidth() / 2 - menuFrame.size.x / 2,
        Config::getScreenHeight() / 2 - menuFrame.size.y / 2
    );

    this->interfaceComponents.push_back(menuFrame);

    InterfaceComponent menuButton;
    menuButton.textureName = "inactive";
    menuButton.size = glm::vec2(198.0f, 177.0f);
    menuButton.coords = glm::vec2(
        Config::getScreenWidth() / 2 - menuButton.size.x / 2,
        Config::getScreenHeight() / 2 - menuButton.size.y / 2
    );

    this->interfaceComponents.push_back(menuButton);
}

void UserInterface::clearUI() {
    this->interfaceComponents.clear();
}

void UserInterface::drawStatusBars()
{
    PlayerStats playerStats = PlayerStore::getPlayerStats();

    renderer->drawBar(glm::vec2(108.0f, 53.0f), glm::vec2(149.0f, 16.0f), Util::formatRGB(237.0f, 55.0f, 55.0f, 0.5f));
    renderer->drawBar(glm::vec2(108.0f, 53.0f), glm::vec2(149.0f, 16.0f), Util::formatRGB(237.0f, 55.0f, 55.0f, 0.9f), playerStats.maxHP, playerStats.currentHP);

    renderer->drawBar(glm::vec2(108.0f, 73.0f), glm::vec2(110.0f, 12.0f), Util::formatRGB(55.0f, 131.0f, 237.0f, 0.5f));
    renderer->drawBar(glm::vec2(108.0f, 73.0f), glm::vec2(110.0f, 12.0f), Util::formatRGB(55.0f, 131.0f, 237.0f, 0.9f), playerStats.maxMP, playerStats.currentMP);
}

#include "Game.hpp"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

UserInterfaceRenderer *uiRenderer;
SpriteRenderer *spriteRenderer;
MapRenderer *mapRenderer;
Camera *camera;

Game::Game(GLuint width, GLuint height)
    : state(Store::getGameState()), keys(), width(width), height(height)
{
    this->player = NULL;
}

Game::~Game()
{
    delete uiRenderer;
    delete spriteRenderer;
    delete mapRenderer;
    delete camera;
    delete this->player;
    delete this->userInterface;
}

void Game::loadShaders()
{
    glm::mat4 projection = glm::ortho(
        0.0f, static_cast<GLfloat>(this->width),
        static_cast<GLfloat>(this->height), 0.0f,
        0.0f, 1.0f);

    const std::string shadersPath = Config::getRootDirectory() + "/shaders/";

    for (const auto &entry : recursive_directory_iterator(shadersPath))
    {
        if (entry.path().filename().extension().string() == ".vs")
        {
            std::string shaderName = entry.path().stem().string();
            std::string path = entry.path().parent_path().string() + "/" + shaderName;
            ResourceManager::LoadShader(
                path + ".vs",
                path + ".fs",
                "",
                shaderName);
            ResourceManager::GetShader(shaderName).Use();
            ResourceManager::GetShader(shaderName).SetInteger("image", 0);
            ResourceManager::GetShader(shaderName).SetMatrix4("projection", projection);
        }
    }
}

void Game::loadTextures()
{
    const std::string spritesPath = Config::getRootDirectory() + "/assets/graphics/sprites/";
    const std::string uiPath = Config::getRootDirectory() + "/assets/graphics/ui/";
    const std::string animationConfigPath = Config::getRootDirectory() + "/assets/graphics/sprites/animations.json";
    Json::Value animationOptions;
    std::ifstream stream(animationConfigPath, std::ifstream::binary);
    stream >> animationOptions;
    for (const auto &entry : recursive_directory_iterator(spritesPath))
    {
        if (entry.path().filename().extension().string() == ".png")
        {
            std::string spriteName = Util::getStringAfterLastDelimiter(entry.path().parent_path().string(), std::string("/"));
            std::string animationName = entry.path().stem().string();
            const int transitionFrames = animationOptions[spriteName][animationName]["transitionFrames"].asInt();
            const GLfloat animationSpeed = animationOptions[spriteName][animationName]["animationSpeed"].asFloat();

            ResourceManager::LoadTexture(
                entry.path().string(),
                spriteName + "_" + animationName,
                transitionFrames,
                animationSpeed);
        }
    }

    ResourceManager::LoadTexture(
        uiPath + "hud/status_bar.png",
        "ui_status_bar");
    ResourceManager::LoadTexture(
        uiPath + "main_menu/menu_frame.png",
        "ui_menu_frame");
    ResourceManager::LoadTexture(
        uiPath + "main_menu/inactive.png",
        "ui_inactive");
    ResourceManager::LoadTexture(
        uiPath + "dialog/avatars/player.png",
        "ui_dialog_avatar_player");
    ResourceManager::LoadTexture(
        uiPath + "dialog/box.png",
        "ui_dialog_box");
}

void Game::initRenderers()
{
    spriteRenderer = new SpriteRenderer();
    mapRenderer = new MapRenderer();
    uiRenderer = new UserInterfaceRenderer();
}

void Game::preload()
{
    DialogStore::preload();
    this->loadShaders();
    this->loadTextures();
}

void Game::init()
{
    this->preload();
    Store::setGameState(this->state);

    this->initRenderers();
    this->userInterface = new UserInterface(uiRenderer);

    if (this->state == GAME_START)
    {
        MapManager::loadMap("home_village");

        this->player = new Player(
            MapManager::getPlayerSpawnPoint("loadgame"),
            spriteRenderer);

        camera = new Camera();
    }
}

void Game::update(GLfloat dt)
{
    this->userInterface->update(dt);
    if (this->state == GAME_START)
    {
        this->player->update(dt);
        camera->setPosition(this->player->coords);
    }
}

void Game::processInput(GLfloat dt)
{
    if (this->state == GAME_START)
    {
        this->player->handleInput(this->keys);
    }
}

void Game::render()
{
    this->userInterface->draw();
    if (this->state == GAME_START)
    {
        mapRenderer->drawMap();
        this->player->draw(Config::isDebugMode());

        if (Config::isDebugMode())
        {
            mapRenderer->debugMap();
        }
    }
}

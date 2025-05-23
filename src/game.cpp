#include "game.h"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "user_interface_renderer.h"
#include "sprite_renderer.h"
#include "map_renderer.h"
#include "engine/store/map_store.h"
#include "engine/store/resource_store.h"
#include "engine/common/util.h"
#include "store/game_store.h"
#include "store/dialog_store.h"
#include "config.h"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

UserInterfaceRenderer *uiRenderer;
SpriteRenderer *spriteRenderer;
MapRenderer *mapRenderer;
Camera *camera;

Game::Game(GLuint width, GLuint height)
    : state(GameStore::getGameState()), keys(), width(width), height(height)
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
            ResourceStore::LoadShader(
                path + ".vs",
                path + ".fs",
                "",
                shaderName);
            ResourceStore::GetShader(shaderName).Use();
            ResourceStore::GetShader(shaderName).SetInteger("image", 0);
            ResourceStore::GetShader(shaderName).SetMatrix4("projection", projection);
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

            ResourceStore::LoadTexture(
                entry.path().string(),
                spriteName + "_" + animationName,
                transitionFrames,
                animationSpeed);
        }
    }

    ResourceStore::LoadTexture(
        uiPath + "hud/status_bar.png",
        "ui_status_bar");
    ResourceStore::LoadTexture(
        uiPath + "main_menu/menu_frame.png",
        "ui_menu_frame");
    ResourceStore::LoadTexture(
        uiPath + "main_menu/inactive.png",
        "ui_inactive");
    ResourceStore::LoadTexture(
        uiPath + "dialog/avatars/player.png",
        "ui_dialog_avatar_player");
    ResourceStore::LoadTexture(
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
    MapStore::preload();
    DialogStore::preload();
    this->loadShaders();
    this->loadTextures();
}

void Game::init()
{
    this->preload();
    GameStore::setGameState(this->state);

    this->initRenderers();
    this->userInterface = new UserInterface(uiRenderer);

    if (this->state == GAME_START)
    {
        MapStore::loadMap("home_village");

        this->player = new Player(
            MapStore::getPlayerSpawnPoint("loadgame"),
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

void Game::processInput()
{
    if (this->state == GAME_START)
    {
        this->player->handleInput(Config::setupKeys(this->keys));
    }
}

void Game::render()
{
    this->userInterface->draw();
    if (this->state == GAME_START)
    {
        mapRenderer->drawMap();
        this->player->draw(Config::isDebugMode);

        if (Config::isDebugMode)
        {
            mapRenderer->debugMap();
        }
    }
}

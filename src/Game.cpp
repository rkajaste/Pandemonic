#include "Game.hpp"
#include <iostream>

SpriteRenderer *renderer;
MapManager *mapManager;

Game::Game(GLuint width, GLuint height)
	: state(GAME_START), keys(), width(width), height(height)
{
    this->player = NULL;
}

Game::~Game()
{
    delete renderer;
    delete mapManager;
    delete this->player;
}

void Game::init()
{

    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
        static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

    // Load shaders
    ResourceManager::LoadShader(
        std::string(PROJECT_SOURCE_DIR) + "/shaders/sprite.vs.glsl",
        std::string(PROJECT_SOURCE_DIR) + "/shaders/sprite.fs.glsl",
        "",
        "sprite"
    );
    ResourceManager::LoadShader(
        std::string(PROJECT_SOURCE_DIR) + "/shaders/tile.vs.glsl",
        std::string(PROJECT_SOURCE_DIR) + "/shaders/tile.fs.glsl",
        "",
        "tile"
    );
    ResourceManager::GetShader("sprite").Use();
    ResourceManager::GetShader("sprite").SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("tile").Use();
    ResourceManager::GetShader("tile").SetInteger("image", 0);
    ResourceManager::GetShader("tile").SetMatrix4("projection", projection);
    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    mapManager = new MapManager();
    // Load textures
    ResourceManager::LoadTexture(
        std::string(PROJECT_SOURCE_DIR) + "/assets/graphics/sprites/player/idle.png",
        "player"
    );

    this->player = new Player(
        glm::vec2(400.0f, 300.0f),
        ResourceManager::GetTexture("player"),
        renderer
    );
}

void Game::update(GLfloat dt)
{
    this->player->update(dt);
}


void Game::processInput(GLfloat dt)
{
    this->player->handleInput(this->keys);
}

void Game::render()
{
    this->player->draw();
    mapManager->renderer->drawMap();
}

#include "Game.hpp"
#include <iostream>

SpriteRenderer *renderer;
MapManager *mapManager;
Camera *camera;

Game::Game(GLuint width, GLuint height)
	: state(GAME_START), keys(), width(width), height(height)
{
    this->player = NULL;
}

Game::~Game()
{
    delete renderer;
    delete mapManager;
    delete camera;
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

    // Load textures
    ResourceManager::LoadTexture(
        std::string(PROJECT_SOURCE_DIR) + "/assets/graphics/sprites/player/idle.png",
        "player"
    );

    // Initialize renderers/map
    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    mapManager = new MapManager();

    // Create sprites
    this->player = new Player(
        glm::vec2(200.0f, 812.0f),
        ResourceManager::GetTexture("player"),
        renderer
    );

    camera = new Camera();
}

void Game::update(GLfloat dt)
{
    this->player->update(dt);
    camera->setPosition(glm::vec2(this->player->coords.x, mapManager->worldHeight - this->player->coords.y));
}



void Game::processInput(GLfloat dt)
{
    this->player->handleInput(this->keys);
}

void Game::render()
{
    mapManager->renderer->drawMap();
    this->player->draw();
}

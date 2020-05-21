#include "Game.hpp"
#include <iostream>

SpriteRenderer *spriteRenderer;
MapRenderer *mapRenderer;
Camera *camera;

Game::Game(GLuint width, GLuint height)
	: state(GAME_START), keys(), width(width), height(height)
{
    this->player = NULL;
}

Game::~Game()
{
    delete spriteRenderer;
    delete mapRenderer;
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
        std::string(PROJECT_SOURCE_DIR) + "/shaders/sprite.vs",
        std::string(PROJECT_SOURCE_DIR) + "/shaders/sprite.fs",
        "",
        "sprite"
    );
    ResourceManager::LoadShader(
        std::string(PROJECT_SOURCE_DIR) + "/shaders/tile.vs",
        std::string(PROJECT_SOURCE_DIR) + "/shaders/tile.fs",
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
    MapManager::loadMap();
    spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    mapRenderer = new MapRenderer(ResourceManager::GetShader("tile"));


    // Create sprites
    this->player = new Player(
        glm::vec2(200.0f, 200.0f),
        ResourceManager::GetTexture("player"),
        spriteRenderer
    );

    camera = new Camera();
}

void Game::update(GLfloat dt)
{
    this->player->update(dt);
    camera->setPosition(this->player->coords);
}



void Game::processInput(GLfloat dt)
{
    this->player->handleInput(this->keys);
}

void Game::render()
{
    mapRenderer->drawMap();
    this->player->draw();
}

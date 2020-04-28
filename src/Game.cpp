#include "ResourceManager.hpp"
#include "Game.hpp"
#include <iostream>

SpriteRenderer *renderer;

Game::Game(GLuint width, GLuint height)
	: state(GAME_START), keys(), width(width), height(height)
{
    this->player = NULL;
}

Game::~Game()
{
    delete renderer;
    delete this->player;
}

void Game::init()
{
    MapLoader::loadMap();
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
        static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

    // Load shaders
    ResourceManager::LoadShader(
        std::string(PROJECT_SOURCE_DIR) + "/shaders/VertexShader.glsl",
        std::string(PROJECT_SOURCE_DIR) + "/shaders/FragmentShader.glsl",
        "",
        "sprite"
    );
    ResourceManager::GetShader("sprite").Use();
    ResourceManager::GetShader("sprite").SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    // Load textures
    ResourceManager::LoadTexture(
        std::string(PROJECT_SOURCE_DIR) + "/assets/graphics/sprites/player/idle.png",
        GL_TRUE,
        "player"
    );

    this->player = new Player(
        glm::vec2(100.0f, 0.0f),
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
}

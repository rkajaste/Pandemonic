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
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
        static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // Load shaders
    ResourceManager::LoadShader(
        std::string(PROJECT_SOURCE_DIR) + "/shaders/VertexShader.glsl",
        std::string(PROJECT_SOURCE_DIR) + "/shaders/FragmentShader.glsl",
        "",
        "sprite"
    );

    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    // Load textures
    ResourceManager::LoadTexture(
        std::string(PROJECT_SOURCE_DIR) + "/assets/graphics/avatar.png",
        GL_TRUE,
        "player"
    );

    this->player = new Player(
        glm::vec2(500.0f, 600.0f),
        ResourceManager::GetTexture("player"),
        renderer
    );
}

void Game::update(GLfloat dt)
{

}


void Game::processInput(GLfloat dt)
{

}

void Game::render()
{
    this->player->draw();
}

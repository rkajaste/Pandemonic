#include "Game.hpp"
#include <common/ResourceManager.hpp>
#include <src/SpriteRenderer.hpp>
#include <src/GameState.hpp>

SpriteRenderer *renderer;

Game::Game(GLuint width, GLuint height) 
	: state(GAME_START), keys(), width(width), height(height) 
{ 

}

Game::~Game()
{
    delete renderer;
}

void Game::init()
{
    // Load shaders
    ResourceManager::LoadShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), 
        static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Set render-specific controls
    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // Load textures
    ResourceManager::LoadTexture("assets/graphics/sprites/player/idle.png", GL_TRUE, "player");
}

void Game::update(GLfloat dt)
{

}


void Game::processInput(GLfloat dt)
{

}

void Game::render()
{
    renderer->DrawSprite(ResourceManager::GetTexture("player"), 
        glm::vec2(200, 0), glm::vec2(255, 170), 0.0f);
}

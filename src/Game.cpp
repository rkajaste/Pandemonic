#include "Game.hpp"
#include <common/ResourceManager.hpp>
#include <src/SpriteRenderer.hpp>
#include <src/GameState.hpp>

SpriteRenderer  *Renderer;

Game::Game(GLuint width, GLuint height) 
	: state(GAME_START), keys(), width(width), height(height) 
{ 

}

Game::~Game()
{
    delete Renderer;
}

void Game::init()
{
    // Load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), 
        static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // Load textures
    ResourceManager::LoadTexture("textures/awesomeface.png", GL_TRUE, "face");
}

void Game::update(GLfloat dt)
{

}


void Game::processInput(GLfloat dt)
{

}

void Game::render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"), 
        glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
} 
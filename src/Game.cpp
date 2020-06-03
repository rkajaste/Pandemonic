#include "Game.hpp"

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

void Game::loadShaders()
{
    glm::mat4 projection = glm::ortho(
        0.0f, static_cast<GLfloat>(this->width),
        static_cast<GLfloat>(this->height), 0.0f,
        0.0f, 1.0f);

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
    ResourceManager::LoadShader(
        std::string(PROJECT_SOURCE_DIR) + "/shaders/hitbox.vs",
        std::string(PROJECT_SOURCE_DIR) + "/shaders/hitbox.fs",
        "",
        "hitbox"
    );

    ResourceManager::GetShader("sprite").Use();
    ResourceManager::GetShader("sprite").SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("tile").Use();
    ResourceManager::GetShader("tile").SetInteger("image", 0);
    ResourceManager::GetShader("tile").SetMatrix4("projection", projection);
    ResourceManager::GetShader("hitbox").Use();
    ResourceManager::GetShader("hitbox").SetInteger("image", 0);
    ResourceManager::GetShader("hitbox").SetMatrix4("projection", projection);
}

void Game::loadTextures()
{
    ResourceManager::LoadTexture(
        std::string(PROJECT_SOURCE_DIR) + "/assets/graphics/sprites/player/idle.png",
        "player_idle"
    );
    ResourceManager::LoadTexture(
        std::string(PROJECT_SOURCE_DIR) + "/assets/graphics/sprites/player/run.png",
        "player_run",
        true,
        2
    );
}

void Game::initRenderers()
{
    spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    mapRenderer = new MapRenderer(ResourceManager::GetShader("tile"));
}

void Game::init()
{
    this->loadShaders();
    this->loadTextures();
    MapManager::loadMap();
    this->initRenderers();

    this->player = new Player(
        MapManager::getPlayerSpawnPoint(),
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
    this->player->draw(DEBUG);

    if(DEBUG){
        mapRenderer->debugMap();
    }
}

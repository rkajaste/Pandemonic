#include "Game.hpp"

using recursive_directory_iterator = std::experimental::filesystem::recursive_directory_iterator;

UserInterfaceRenderer *uiRenderer;
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

    const std::string shadersPath = std::string(PROJECT_SOURCE_DIR) + "/shaders/";

    for (const auto & entry : recursive_directory_iterator(shadersPath)) {
        if (entry.path().filename().extension() == ".vs") {
            std::string shaderName = entry.path().stem();
            std::string path = std::string(entry.path().parent_path()) + "/" + shaderName;
            ResourceManager::LoadShader(
                path + ".vs",
                path + ".fs",
                "",
                shaderName
            );
            ResourceManager::GetShader(shaderName).Use();
            ResourceManager::GetShader(shaderName).SetInteger("image", 0);
            ResourceManager::GetShader(shaderName).SetMatrix4("projection", projection);
        }
    }

}

void Game::loadTextures()
{
    const std::string spritesPath = std::string(PROJECT_SOURCE_DIR) + "/assets/graphics/sprites/";
    const std::string uiPath = std::string(PROJECT_SOURCE_DIR) + "/assets/graphics/ui/";
    const std::string animationConfigPath = std::string(PROJECT_SOURCE_DIR) + "/assets/graphics/sprites/animations.json";
    Json::Value animationOptions;
    std::ifstream stream(animationConfigPath, std::ifstream::binary);
    stream >> animationOptions;
    for (const auto & entry : recursive_directory_iterator(spritesPath)) {
        if (entry.path().filename().extension() == ".png") {
            std::string spriteName = Util::getStringAfterLastDelimiter(entry.path().parent_path(), std::string("/"));
            std::string animationName = entry.path().stem();
            const int transitionFrames = animationOptions[spriteName][animationName]["transitionFrames"].asInt();
            const GLfloat animationSpeed = animationOptions[spriteName][animationName]["animationSpeed"].asFloat();
            
            ResourceManager::LoadTexture(
                entry.path(),
                spriteName + "_" + animationName,
                transitionFrames,
                animationSpeed
            );
        }
    }

    ResourceManager::LoadTexture(
        uiPath + "hud/status_bar.png",
        "ui_status_bar"
    );
}

void Game::initRenderers()
{
    spriteRenderer = new SpriteRenderer();
    mapRenderer = new MapRenderer();
    uiRenderer = new UserInterfaceRenderer();
}

void Game::init()
{
    this->loadShaders();
    this->loadTextures();
    MapManager::loadMap("forest_west");
    this->initRenderers();

    this->player = new Player(
        MapManager::getPlayerSpawnPoint("loadgame"),
        spriteRenderer
    );

    this->userInterface = new UserInterface(uiRenderer);
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
    this->player->draw(Config::isDebugMode());
    this->userInterface->draw();

    if(Config::isDebugMode()){
        mapRenderer->debugMap();
    }
}

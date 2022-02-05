#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <filesystem>
#include <regex>
#include <json/json.h>
#include <fstream>

#include "UserInterfaceRenderer.hpp"
#include "SpriteRenderer.hpp"
#include "MapRenderer.hpp"
#include "Player.hpp"
#include "ui/UserInterface.hpp"
#include "engine/managers/MapManager.hpp"
#include "engine/managers/ResourceManager.hpp"
#include "engine/camera/Camera.hpp"
#include "engine/common/Util.hpp"
#include "store/Store.hpp"
#include "store/DialogStore.hpp"
#include "types.hpp"

class Game
{
public:
    GameState state;
    GLboolean keys[1024];
    GLuint width, height;
    Player *player;
    UserInterface *userInterface;
    // Constructor/Destructor
    Game(GLuint width, GLuint height);
    ~Game();
    // Initialize game state (load all shaders/textures/levels)
    void init();
    // GameLoop
    void processInput(GLfloat dt);
    void update(GLfloat dt);
    void render();

private:
    void preload();
    void loadShaders();
    void loadTextures();
    void initRenderers();
};
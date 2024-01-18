#pragma once

#include <iostream>
#include <filesystem>
#include <regex>
#include <json/json.h>
#include <fstream>
#include <glad/glad.h>

#include "user_interface_renderer.h"
#include "sprite_renderer.h"
#include "map_renderer.h"
#include "player.h"
#include "ui/user_interface.h"
#include "engine/managers/map_manager.h"
#include "engine/managers/resource_manager.h"
#include "engine/camera/camera.h"
#include "engine/common/util.h"
#include "store/game_store.h"
#include "store/dialog_store.h"
#include "types.h"
#include "config.h"

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
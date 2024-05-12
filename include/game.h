#pragma once

#include <json/json.h>
#include <glad/glad.h>
#include "player.h"
#include "ui/user_interface.h"
#include "engine/camera/camera.h"
#include "types.h"

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
    void processInput();
    void update(GLfloat dt);
    void render();

private:
    void preload();
    void loadShaders();
    void loadTextures();
    void initRenderers();
};

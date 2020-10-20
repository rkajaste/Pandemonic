#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <experimental/filesystem>
#include <regex>
#include <json/json.h>
#include <fstream>

#include "UserInterfaceRenderer.hpp"
#include "SpriteRenderer.hpp"
#include "MapRenderer.hpp"
#include "Player.hpp"
#include "UserInterface.hpp"
#include "MapManager.hpp"
#include "ResourceManager.hpp"
#include "Camera.hpp"
#include "Util.hpp"

enum GameState {GAME_START, MAIN_MENU};
class Game
{
    public:
        GameState  state;
        GLboolean  keys[1024];
        GLuint	   width, height;
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
        void loadShaders();
        void loadTextures();
        void initRenderers();
};
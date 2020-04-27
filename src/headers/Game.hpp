#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "SpriteRenderer.hpp"
#include "Player.hpp"

enum GameState {GAME_START, MAIN_MENU};
class Game
{
    public:
        GameState  state;
        GLboolean  keys[1024];
        GLuint	   width, height;
        Player *player;
        // Constructor/Destructor
        Game(GLuint width, GLuint height);
        ~Game();
        // Initialize game state (load all shaders/textures/levels)
        void init();
        // GameLoop
        void processInput(GLfloat dt);
        void update(GLfloat dt);
        void render();
};
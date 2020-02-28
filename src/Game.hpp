#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <src/GameState.hpp>
#include <src/SpriteRenderer.hpp>
#include <src/sprites/Player/Player.hpp>

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
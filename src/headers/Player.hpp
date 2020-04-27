#pragma once
#include "Sprite.hpp"
#include <vector>

enum PlayerState { IDLE, MOVING, JUMPING };
class Player: public Sprite {
    public:
        using Sprite::Sprite;
        void update(GLfloat);
        void handleInput(GLboolean keys[2048]);
    private:
        std::vector<PlayerState> states;
        GLfloat speed = 1100.0f;
        GLfloat jumpForce = 2000.0f;
        GLboolean hasState(PlayerState);
        void move(GLfloat);
        void jump(GLfloat);

};
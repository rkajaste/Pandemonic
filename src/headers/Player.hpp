#pragma once
#include "Sprite.hpp"
#include "Util.hpp"
#include "Physics.hpp"
#include <vector>

enum PlayerState { IDLE, MOVING, JUMPING };
class Player: public Sprite {
    public:
        using Sprite::Sprite;
        void update(GLfloat);
        void handleInput(GLboolean keys[2048]);
    private:
        int noClipDirection = 1;
        std::vector<PlayerState> states;
        GLfloat speed = 1100.0f;
        GLfloat jumpForce = 2000.0f;
        void move(GLfloat);
        void jump(GLfloat);

};
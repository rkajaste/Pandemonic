#pragma once
#include "Sprite.hpp"
#include "Util.hpp"
#include "Physics.hpp"
#include <vector>
#include <map>

class Player: public Sprite {
    public:
        using Sprite::Sprite;

        void update(GLfloat);
        void handleInput(GLboolean keys[2048]);
};

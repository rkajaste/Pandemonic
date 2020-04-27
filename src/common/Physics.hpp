#pragma once
#include <glad/glad.h>

class Physics {
    public:
        static GLfloat calculateHeight(GLfloat height, GLfloat dt);
    private:
        Physics() { }
};

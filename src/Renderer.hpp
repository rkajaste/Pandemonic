#pragma once
#include <GL/glew.h>

class Renderer {
    public:
        Renderer();
        void draw();
    private:
        GLfloat vertex_data;
};
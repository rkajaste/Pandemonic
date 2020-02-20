#pragma once
#include <GL/glew.h>

class Renderer {
    public:
        Renderer();
        void draw();
    private:
        GLuint programID;
        GLuint vertexbuffer;
        GLuint VertexArrayID;
        static const GLfloat vertex_data[];
};
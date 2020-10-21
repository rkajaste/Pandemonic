#pragma once

#include "Shader.hpp"

class Renderer {
    public:
        Renderer();
        ~Renderer();
    protected:
        Shader shader;
        GLuint quadVAO;
        GLfloat defaultVertices[24] = {
            // Pos      // Tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        void initRenderData(GLfloat vertices[24], size_t size);
};

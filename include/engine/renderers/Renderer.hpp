#pragma once

#include "Shader.hpp"

class Renderer {
    public:
        Renderer();
        ~Renderer();
    protected:
        Shader shader;
        GLuint quadVAO;
    private:
        void initRenderData();
};

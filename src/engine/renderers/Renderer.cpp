#include "renderer.h"

Renderer::Renderer()
{
    this->initRenderData(this->defaultVertices, sizeof(this->defaultVertices));
}

Renderer::~Renderer()
{
    // glDeleteVertexArrays(1, &this->quadVAO);
}

void Renderer::initRenderData(GLfloat vertices[24], size_t size)
{
    // Configure VAO/VBO
    GLuint VBO;

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
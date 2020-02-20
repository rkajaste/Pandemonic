#include "Renderer.hpp"
#include <GL/glew.h>
#include <common/shader.hpp>

class Renderer {
    public:
        Renderer() {
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);
            
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), g_vba_data, GL_STATIC_DRAW);

            GLuint programID = LoadShaders(
                "../shaders/VertexShader.glsl",
                "../shaders/FragmentShader.glsl"
            );
        }
        void draw() {
            glUseProgram(programID);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                6,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glDisableVertexAttribArray(0);
        }
    private:
        GLuint programID;
        GLuint vertexbuffer;
        GLuint VertexArrayID;
        static const GLfloat vertex_data = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  1.0f, 0.0f,

            0.5f, 0.5f, 0.0f,
            0.0f, 0.0f, 0.5f,
            0.0f,  0.5f, 0.0f,    
        };
};
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>
out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    texCoord = vertex.zw;
    gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}

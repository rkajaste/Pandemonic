#version 330 core
layout (location = 0) in vec2 position; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = texCoords.xy;
    gl_Position = projection * model * vec4(position.xy, 0.0, 1.0);
}

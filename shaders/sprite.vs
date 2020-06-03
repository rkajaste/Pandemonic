#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 texCoords;
out vec2 textureCoordOffset;
out vec2 zoom;

uniform vec2 spritesheetSize;
uniform vec2 spriteSize;
uniform vec2 offset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{

    float u = offset.x / spritesheetSize.x;
    float v = offset.y / spritesheetSize.y;

    textureCoordOffset = vec2(u, v);
    texCoords = vertex.zw;
    zoom = vec2(spriteSize.x / spritesheetSize.x, spriteSize.y / spritesheetSize.y);
    gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}

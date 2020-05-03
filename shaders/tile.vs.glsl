#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;
out vec2 vTextureCoordOffset;
out vec2 vZoom;

uniform vec2 tilesetDimensions;
uniform vec2 tileSize;
uniform vec2 offset;
uniform mat4 position;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    float u = offset.x / tilesetDimensions.y;
    float v = offset.y / tilesetDimensions.x;
    vTextureCoordOffset = vec2(u, v);
    vZoom = vec2(tileSize.x / tilesetDimensions.y, tileSize.y / tilesetDimensions.x);
    TexCoords = vertex.zw;
    gl_Position = projection * view * position * vec4(vertex.xy, 0.0, 1.0);
}

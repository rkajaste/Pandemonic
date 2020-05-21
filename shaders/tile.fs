#version 330 core
in vec2 texCoords;
in vec2 textureCoordOffset;
in vec2 zoom;

out vec4 color;

uniform sampler2D image;

void main()
{
    color = texture(image, texCoords.xy * zoom + textureCoordOffset);
}

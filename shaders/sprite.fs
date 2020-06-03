#version 330 core
in vec2 texCoords;
in vec2 textureCoordOffset;
in vec2 zoom;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform bool flipX;
uniform vec2 spriteSize;
uniform vec2 spritesheetSize;


void main()
{   
    vec2 flip = vec2(flipX ? -1.0 : 1.0, 1.0);
    float offsetX = textureCoordOffset.x; 
    vec2 offset = vec2(offsetX, textureCoordOffset.y); // flip animation too here
    color = vec4(spriteColor, 1.0) * texture(image, texCoords * zoom * flip + offset);
}

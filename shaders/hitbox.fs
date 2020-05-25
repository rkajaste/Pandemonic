#version 330 core
in vec2 texCoord;
out vec4 color;

uniform vec2 size;

void main()
{   
    float border_width = 0.02;
    float aspect = size.x / size.y;
    float maxX = 1.0 - border_width;
    float minX = border_width;
    float maxY = maxX;
    float minY = minX;

    if (texCoord.x < maxX && texCoord.x > minX &&
        texCoord.y < maxY && texCoord.y > minY) {
        color = vec4(0.0, 1.0, 0.0, 0.0); // inside of the rect
    } else {
        color = vec4(0.0, 1.0, 0.0, 1.0); // border 
    }
    
}

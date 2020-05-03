#version 330 core
in vec2 TexCoords;
in vec2 vTextureCoordOffset;
in vec2 vZoom;

uniform sampler2D image;

void main()
{
    gl_FragColor = texture(image, TexCoords.xy * vZoom + vTextureCoordOffset);
}

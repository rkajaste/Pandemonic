#version 330 core
layout (location = 0) in vec2 vertex; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec2 texVertex;
out vec2 TexCoords;

//uniform mat4 texPosition;
uniform mat4 position;
uniform mat4 projection;

void main()
{
    TexCoords = texVertex.xy;
    gl_Position = projection * position * vec4(vertex.xy, 0.0, 1.0);
}

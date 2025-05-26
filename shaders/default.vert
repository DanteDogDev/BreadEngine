#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color; // R, G, B, A
layout(location = 2) in vec2 texCoord;

out vec4 frag_color;
out vec2 frag_texCoord;

void main()
{
    gl_Position = position;
    frag_color = color;
    frag_texCoord = texCoord;
}



#version 330 core
in vec4 frag_color;
in vec2 frag_texCoord;

out vec4 color;

// uniform vec4 u_Color;

void main()
{
    color = vec4(frag_texCoord.r, 0.0, frag_texCoord.g, 1.0);
  // color = vec4(frag_texCoord.r, 0.0, frag_texCoord.b);
}

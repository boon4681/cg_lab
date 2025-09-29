#version 330 core

in vec4 vCol;
out vec4 colour;
in vec2 TexCoord;

uniform sampler2D texture1;

void main() {
    colour = vCol;
    colour = texture(texture1, TexCoord);
}
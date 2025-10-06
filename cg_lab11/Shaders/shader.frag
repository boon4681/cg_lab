#version 330 core

in vec4 vCol;
out vec4 colour;
in vec2 TexCoord;
uniform vec3 lightColour;

uniform sampler2D texture1;

void main() {
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColour;
    colour = texture(texture1, TexCoord) * vec4(ambient, 1.0);
}
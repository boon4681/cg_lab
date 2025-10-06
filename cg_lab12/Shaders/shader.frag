#version 330 core 

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 colour;

uniform vec3 lightColour;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D texture1;

vec3 diffuseLight() {
    float diffuseStrength = 0.5;
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColour * diff * diffuseStrength;

    return diffuse;
}

vec3 ambientLight() {
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColour;

    return ambient;
}

vec3 specularLight() {
    float specularStrength = 0.8;
    float shininess = 64.0;
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 norm = normalize(Normal);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 viewDir = normalize(viewPos - FragPos);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = lightColour * spec * specularStrength;

    return specular;
}

void main() {
    colour = texture(texture1, TexCoord) * vec4(ambientLight() + diffuseLight() + specularLight(), 1.0);
}
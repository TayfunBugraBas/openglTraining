#version 330 core

in vec3 ourColor;
in vec2 ourTexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visibility;

void main() {
    FragColor =mix(texture(texture1, ourTexCoord), texture(texture2, vec2(1.0 - ourTexCoord.x, ourTexCoord.y)), visibility);
}
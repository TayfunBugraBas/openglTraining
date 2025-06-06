#version 330 core

in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main(){

	FragColor = mix(texture(texture1,ourTexCoord), texture(texture2, ourTexCoord),0.3);

}
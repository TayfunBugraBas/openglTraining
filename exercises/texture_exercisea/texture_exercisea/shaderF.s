#version 330 core

in vec2 ourTexCoord;
in vec3 ourColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 Fragment;

void main(){

	Fragment = mix(texture(texture1, ourTexCoord), texture(texture2, ourTexCoord), 0.2);

}

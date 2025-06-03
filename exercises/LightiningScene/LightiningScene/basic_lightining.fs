#version 330 core

in vec2 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 ourFrag;

void main(){
	ourFrag = vec4(lightColor * objectColor, 1.0);
}
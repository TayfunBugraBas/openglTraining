#version 330 core

in vec3 ourColor;

out vec4 fragment;

void main(){

	fragment = vec4(ourColor, 1.0);
}